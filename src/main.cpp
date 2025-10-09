#include "game.h"

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");
  SetTargetFPS(60);

  Game game;

  while (!WindowShouldClose()) {
    game.update();

    BeginDrawing();
    ClearBackground(MY_GREEN);

    game.draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
