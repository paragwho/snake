#include "game_over_state.h"
#include "config.h"
#include "game.h"
#include "play_state.h"

GameOverState::GameOverState(int score) : m_Score(score) {}

void GameOverState::HandleInput(Game &game) {
  if (IsKeyPressed(KEY_ENTER)) {
    game.ChangeState(std::make_unique<PlayState>());
  }
}

void GameOverState::Update(Game &game) {}

void GameOverState::Draw() const {
  ClearBackground(MY_GREEN);

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
