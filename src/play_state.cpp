#include "play_state.hpp"
#include "config.hpp"
#include "game.hpp"
#include "game_over_state.hpp"
#include "raylib.h"
#include "raymath.h"
#include "spawner.hpp"
#include <memory>

PlayState::PlayState()
    : m_Snake(), m_Apple(Spawner::GenerateValidPosition(m_Snake)),
      m_MoveSnakeTimer() {}

void PlayState::HandleInput(Game &game) { m_Snake.HandleInput(); }

void PlayState::Update(Game &game) {
  HideCursor();

  if (m_MoveSnakeTimer.IsTriggered(MOVE_INTERVAL)) {
    m_Snake.Move();

    if (m_Snake.CheckSelfCollision() || m_Snake.CheckBoundaryCollision()) {
      game.ChangeState(std::make_unique<GameOverState>(m_Score));
    }

    if (IsAppleEaten(m_Apple, m_Snake)) {
      m_Score++;
      m_Snake.Grow();
      m_Apple.SetPosition(Spawner::GenerateValidPosition(m_Snake));
    }
  }
}

void PlayState::Draw() const {
  ClearBackground(MY_GREEN);

  Rectangle border = {BORDER_GAP_PIXELS, BORDER_GAP_PIXELS,
                      SCREEN_WIDTH - 2 * BORDER_GAP_PIXELS,
                      SCREEN_HEIGHT - 2 * BORDER_GAP_PIXELS};
  DrawRectangleRoundedLinesEx(border, 0.01f, 8, BORDER_THICKNESS,
                              MY_DARK_GREEN);

  m_Apple.Draw();
  m_Snake.Draw();

  const char *text = "SNAKE";
  DrawText(text, CELL_SIZE, (BORDER_GAP_PIXELS - CELL_SIZE) / 2,
           FONT_SIZE_MEDIUM, MY_DARK_GREEN);

  text = TextFormat("%i", m_Score);
  DrawText(text, SCREEN_WIDTH - CELL_SIZE - MeasureText(text, FONT_SIZE_MEDIUM),
           (BORDER_GAP_PIXELS - CELL_SIZE) / 2, FONT_SIZE_MEDIUM,
           MY_DARK_GREEN);
}

bool PlayState::IsAppleEaten(Apple &apple, Snake &snake) {
  return Vector2Equals(apple.GetPosition(), snake.GetHeadPosition());
}
