#include "game_over_state.hpp"
#include "config.hpp"
#include "game.hpp"
#include "play_state.hpp"
#include "raylib.h"
#include <memory>

GameOverState::GameOverState(int score) : m_Score(score) {}

void GameOverState::HandleInput(Game &game) {
  if (IsKeyPressed(KEY_ENTER)) {
    game.ChangeState(std::make_unique<PlayState>());
  }
}

void GameOverState::Update(Game &game) { HideCursor(); }

void GameOverState::Draw() const {
  ClearBackground(MY_GREEN);

  const char *text = "GAME OVER";
  DrawText(text, (SCREEN_WIDTH - MeasureText(text, FONT_SIZE_LARGE)) / 2,
           (SCREEN_HEIGHT - FONT_SIZE_LARGE) / 2 - CELL_SIZE, FONT_SIZE_LARGE,
           MY_DARK_GREEN);

  text = "PRESS ENTER TO PLAY AGAIN";
  DrawText(text, (SCREEN_WIDTH - MeasureText(text, FONT_SIZE_MEDIUM)) / 2,
           (SCREEN_HEIGHT - FONT_SIZE_MEDIUM) / 2 + CELL_SIZE, FONT_SIZE_MEDIUM,
           MY_DARK_GREEN);

  text = TextFormat("SCORE: %i", m_Score);
  DrawText(text, SCREEN_WIDTH - CELL_SIZE - MeasureText(text, FONT_SIZE_MEDIUM),
           (BORDER_GAP_PIXELS - CELL_SIZE) / 2, FONT_SIZE_MEDIUM,
           MY_DARK_GREEN);
}
