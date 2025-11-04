#include "config.h"
#include "play_state.h"
#include "state_manager.h"

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");
  SetTargetFPS(60);

  StateManager manager;
  manager.PushState(std::make_unique<PlayState>());

  while (!WindowShouldClose()) {
    manager.Update();

    BeginDrawing();
    ClearBackground(MY_GREEN);

    manager.Draw();

    EndDrawing();
  }

  CloseWindow();
}
