#include "game.h"
#include "raymath.h"
#include "spawner.h"

Game::Game()
    : score(0), gameState(PLAY), snake(),
      apple(Spawner::generateValidPosition(snake)), moveSnake() {}

void Game::update() {
  if (gameState == PLAY) {
    snake.handleInput();

    if (moveSnake.isTriggered(MOVE_INTERVAL)) {
      snake.move();

      if (snake.checkSelfCollision() || snake.checkBoundaryCollision()) {
        gameState = GAMEOVER;
      }

      if (isAppleEaten(apple, snake)) {
        score++;
        snake.grow();
        apple.setPosition(Spawner::generateValidPosition(snake));
      }
    }
  } else if (gameState == GAMEOVER) {
    if (IsKeyPressed(KEY_ENTER)) {
      reset();
    }
  }
}

void Game::draw() const {
  const char *scoreText;

  if (gameState == PLAY) {
    apple.draw();
    snake.draw();

    scoreText = TextFormat("%i", score);
    DrawText(scoreText, CELL_SIZE, CELL_SIZE * (CELL_COUNT - 2),
             SCORE_FONT_SIZE, MY_DARK_GREEN);
  } else if (gameState == GAMEOVER) {

    DrawText("GAME OVER",
             (SCREEN_WIDTH - MeasureText("GAME OVER", TITLE_FONT_SIZE)) / 2,
             (SCREEN_WIDTH - TITLE_FONT_SIZE) / 2 - SPACING * 4,
             TITLE_FONT_SIZE, MY_DARK_GREEN);

    DrawText("Press Enter to play again",
             (SCREEN_WIDTH -
              MeasureText("Press Enter to play again", INSTRUCTION_FONT_SIZE)) /
                 2,
             (SCREEN_WIDTH - INSTRUCTION_FONT_SIZE) / 2 + SPACING * 4,
             INSTRUCTION_FONT_SIZE, MY_DARK_GREEN);

    scoreText = TextFormat("Score: %i", score);
    DrawText(scoreText, CELL_SIZE, CELL_SIZE * (CELL_COUNT - 2),
             SCORE_FONT_SIZE, MY_DARK_GREEN);
  }
}

void Game::reset() {
  snake.reset();
  apple.setPosition(Spawner::generateValidPosition(snake));
  score = 0;
  gameState = PLAY;
}

int Game::getScore() const { return score; }

GameState Game::getState() const { return gameState; }

bool Game::isAppleEaten(Apple &apple, Snake &snake) {
  return Vector2Equals(apple.getPosition(), snake.getHeadPosition());
}
