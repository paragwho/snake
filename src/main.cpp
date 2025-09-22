#include "raylib.h"
#include "raymath.h"
#include <deque>

using namespace std;

const int CELL_SIZE = 30;
const int CELL_COUNT = 25;
const double MOVE_INTERVAL = 0.12;

const int GAP_TO_BORDER = 1;
const int TITLE_FONT_SIZE = 80;
const int SCORE_FONT_SIZE = 40;
const int INSTRUCTION_FONT_SIZE = 40;
const int SPACING = 10;

const Vector2 SNAKE_INITIAL_POSITION = {12, 11};
const Vector2 SNAKE_INITIAL_DIRECTION = {0, -1};
const int SNAKE_INITIAL_LENGTH = 3;

enum GameState { PLAY, GAMEOVER };

Color myGreen = {173, 204, 96, 255};
Color myDarkGreen = {43, 51, 24, 255};

struct Timer {
  double lastTime = 0;

  bool isTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastTime >= interval) {
      lastTime = currentTime;
      return true;
    }
    return false;
  }
};

class Apple {
  Vector2 position;

public:
  Apple(Vector2 Position) : position(Position) {}

  void draw() const {
    DrawRectangle(CELL_SIZE * position.x, CELL_SIZE * position.y, CELL_SIZE,
                  CELL_SIZE, RED);
  }

  Vector2 getPosition() const { return position; }

  void setPosition(Vector2 Position) { position = Position; }
};

class Snake {
  Vector2 direction = SNAKE_INITIAL_DIRECTION;
  deque<Vector2> body;
  bool directionChanged = false;

  void initializeBody() {
    body.clear();
    for (int i = 0; i < SNAKE_INITIAL_LENGTH; i++) {
      body.push_back(
          Vector2Add(SNAKE_INITIAL_POSITION,
                     Vector2Scale(Vector2Negate(SNAKE_INITIAL_DIRECTION), i)));
    }
  }

public:
  Snake() { initializeBody(); }

  void move() {
    body.push_front(Vector2Add(body.front(), direction));
    body.pop_back();
    directionChanged = false;
  }

  void grow() { body.push_back(body.back()); }

  void draw() const {
    for (int i = 0; i < body.size(); i++) {
      DrawRectangle(body[i].x * CELL_SIZE, body[i].y * CELL_SIZE, CELL_SIZE,
                    CELL_SIZE, myDarkGreen);
    }
  }

  void reset() {
    direction = SNAKE_INITIAL_DIRECTION;
    initializeBody();
  }

  Vector2 getHeadPosition() const { return body.front(); }

  void handleInput() {
    if (directionChanged) {
      return;
    }

    if (IsKeyPressed(KEY_UP) && direction.y != 1) {
      direction = {0, -1};
      directionChanged = true;
    }
    if (IsKeyPressed(KEY_DOWN) && direction.y != -1) {
      direction = {0, 1};
      directionChanged = true;
    }
    if (IsKeyPressed(KEY_LEFT) && direction.x != 1) {
      direction = {-1, 0};
      directionChanged = true;
    }
    if (IsKeyPressed(KEY_RIGHT) && direction.x != -1) {
      direction = {1, 0};
      directionChanged = true;
    }
  }

  bool checkSelfCollision() const {
    for (int i = 1; i < body.size(); i++) {
      if (Vector2Equals(body.front(), body[i])) {
        return true;
      }
    }
    return false;
  }

  bool checkBoundaryCollision() const {
    return (getHeadPosition().x < 0 || getHeadPosition().x > CELL_COUNT - 1 ||
            getHeadPosition().y < 0 || getHeadPosition().y > CELL_COUNT - 1);
  }

  bool checkCollisionAt(Vector2 position) const {
    for (int i = 0; i < body.size(); i++) {
      if (Vector2Equals(position, body[i])) {
        return true;
      }
    }
    return false;
  }
};

namespace Spawner {
Vector2 randomPosition() {
  return {(float)GetRandomValue(0, CELL_COUNT - 1),
          (float)GetRandomValue(0, CELL_COUNT - 1)};
}

Vector2 generateValidPosition(Snake &snake) {
  Vector2 position = randomPosition();
  do {
    position = randomPosition();
  } while (snake.checkCollisionAt(position));

  return position;
}
}; // namespace Spawner

class Game {
  Snake snake;
  Apple apple{Spawner::generateValidPosition(snake)};
  Timer moveSnake;

  bool isAppleEaten(Apple &apple, Snake &snake) {
    return Vector2Equals(apple.getPosition(), snake.getHeadPosition());
  }

public:
  int appleCount = 0;
  GameState gameState = PLAY;

  void update() {
    snake.handleInput();

    if (moveSnake.isTriggered(MOVE_INTERVAL)) {
      snake.move();

      if (snake.checkSelfCollision() || snake.checkBoundaryCollision()) {
        gameState = GAMEOVER;
      }

      if (isAppleEaten(apple, snake)) {
        appleCount++;
        snake.grow();
        apple.setPosition(Spawner::generateValidPosition(snake));
      }
    }
  }

  void draw() const {
    apple.draw();
    snake.draw();
  }

  void reset() {
    snake.reset();
    apple.setPosition(Spawner::generateValidPosition(snake));
    appleCount = 0;
    gameState = PLAY;
  }
};

int main() {
  InitWindow(CELL_SIZE * CELL_COUNT, CELL_SIZE * CELL_COUNT, "Snake");
  SetTargetFPS(60);

  Game game;

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(myGreen);

    if (game.gameState == PLAY) {
      game.update();
      game.draw();
    } else if (game.gameState == GAMEOVER) {
      DrawText(
          "GAME OVER",
          (CELL_SIZE * CELL_COUNT - MeasureText("GAME OVER", TITLE_FONT_SIZE)) /
              2,
          (CELL_SIZE * CELL_COUNT - TITLE_FONT_SIZE) / 2 - SPACING * 4,
          TITLE_FONT_SIZE, myDarkGreen);

      DrawText(
          "Press Enter to play again",
          (CELL_SIZE * CELL_COUNT -
           MeasureText("Press Enter to play again", INSTRUCTION_FONT_SIZE)) /
              2,
          (CELL_SIZE * CELL_COUNT - INSTRUCTION_FONT_SIZE) / 2 + SPACING * 4,
          INSTRUCTION_FONT_SIZE, myDarkGreen);

      if (IsKeyPressed(KEY_ENTER)) {
        game.reset();
      }
    }

    const char *scoreText;

    if (game.gameState == PLAY) {
      scoreText = TextFormat("%i", game.appleCount);
    } else {
      scoreText = TextFormat("Score: %i", game.appleCount);
    }

    DrawText(scoreText, CELL_SIZE * GAP_TO_BORDER,
             CELL_SIZE * (CELL_COUNT - GAP_TO_BORDER * 2), SCORE_FONT_SIZE,
             myDarkGreen);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
