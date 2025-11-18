#include "game_over_state.h"
#include "config.h"
#include "game.h"
#include "play_state.h"
#include <memory>

GameOverState::GameOverState(int score) : m_Score(score) {}

void GameOverState::HandleInput(Game &game) {
  if (IsKeyPressed(KEY_ENTER)) {
    game.ChangeState(std::make_unique<PlayState>());
  }
}

void GameOverState::Update(Game &game) {}

void GameOverState::Draw() const {
  ClearBackground(MY_GREEN);

  const char *text = "GAME OVER";
  DrawText(text, (SCREEN_WIDTH - MeasureText(text, TITLE_FONT_SIZE)) / 2,
           (SCREEN_HEIGHT - TITLE_FONT_SIZE) / 2 - CELL_SIZE, TITLE_FONT_SIZE,
           MY_DARK_GREEN);

  text = "Press Enter to play again";
  DrawText(text, (SCREEN_WIDTH - MeasureText(text, INSTRUCTION_FONT_SIZE)) / 2,
           (SCREEN_HEIGHT - INSTRUCTION_FONT_SIZE) / 2 + CELL_SIZE,
           INSTRUCTION_FONT_SIZE, MY_DARK_GREEN);

  text = TextFormat("Score: %i", m_Score);
  DrawText(text, SCREEN_WIDTH - CELL_SIZE - SCORE_FONT_SIZE, CELL_SIZE,
           SCORE_FONT_SIZE, MY_DARK_GREEN);
}
