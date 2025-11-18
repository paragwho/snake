#include "play_state.h"
#include "config.h"
#include "game.h"
#include "game_over_state.h"
#include "raylib.h"
#include "raymath.h"
#include "spawner.h"
#include <memory>

PlayState::PlayState()
    : m_Snake(), m_Apple(Spawner::GenerateValidPosition(m_Snake)),
      m_MoveSnakeTimer() {}

void PlayState::HandleInput(Game &game) { m_Snake.HandleInput(); }

void PlayState::Update(Game &game) {
  if (m_GameOver) {
    game.ChangeState(std::make_unique<GameOverState>(m_Score));
  }

  if (m_MoveSnakeTimer.IsTriggered(MOVE_INTERVAL)) {
    m_Snake.Move();

    if (m_Snake.CheckSelfCollision() || m_Snake.CheckBoundaryCollision()) {
      m_GameOver = true;
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

  m_Apple.Draw();
  m_Snake.Draw();

  const char *text = TextFormat("%i", m_Score);
  DrawText(text, SCREEN_WIDTH - CELL_SIZE - SCORE_FONT_SIZE, CELL_SIZE,
           SCORE_FONT_SIZE, MY_DARK_GREEN);
}

bool PlayState::IsAppleEaten(Apple &apple, Snake &snake) {
  return Vector2Equals(apple.GetPosition(), snake.GetHeadPosition());
}
