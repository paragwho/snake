#include "game_over_state.h"
#include "config.h"

GameOverState::GameOverState(int score) : m_Score(score) {}

void GameOverState::HandleInput() {
  if (IsKeyPressed(KEY_ENTER)) {
    // Change state to PlayState
  }
}

void GameOverState::Update() {}

void GameOverState::Draw() const {
  DrawText("GAME OVER",
           (SCREEN_WIDTH - MeasureText("Game Over", TITLE_FONT_SIZE)) / 2,
           (SCREEN_HEIGHT - TITLE_FONT_SIZE) / 2 - SPACING * 4, TITLE_FONT_SIZE,
           MY_DARK_GREEN);

  DrawText("Press Enter to play again",
           (SCREEN_WIDTH -
            MeasureText("Press Enter to play again", INSTRUCTION_FONT_SIZE)) /
               2,
           (SCREEN_HEIGHT - INSTRUCTION_FONT_SIZE) / 2 + SPACING * 4,
           INSTRUCTION_FONT_SIZE, MY_DARK_GREEN);

  const char *scoreText = TextFormat("Score: %i", m_Score);
  DrawText(scoreText, CELL_SIZE, CELL_SIZE * (CELL_COUNT - 2), SCORE_FONT_SIZE,
           MY_DARK_GREEN);
}
