#include "game.h"
#include "config.h"
#include "play_state.h"

void Game::Run() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_NAME);
  SetTargetFPS(TARGET_FPS);

  m_Manager.PushState(std::make_unique<PlayState>());

  while (!WindowShouldClose()) {
    HandleInput();
    Update();

    BeginDrawing();
    Draw();
    EndDrawing();
  }

  CloseWindow();
}

void Game::ChangeState(std::unique_ptr<BaseState> state) {
  m_Manager.ChangeState(std::move(state));
}

void Game::HandleInput() {
  if (BaseState *state = m_Manager.GetCurrentState()) {
    state->HandleInput(*this);
  }
}

void Game::Update() {
  if (BaseState *state = m_Manager.GetCurrentState()) {
    state->Update(*this);
  }
}

void Game::Draw() {
  if (BaseState *state = m_Manager.GetCurrentState()) {
    state->Draw();
  }
}
