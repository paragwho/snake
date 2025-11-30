#pragma once
#include "state_manager.hpp"

class BaseState;

class Game {
public:
  void Run();
  void ChangeState(std::unique_ptr<BaseState> state);

private:
  StateManager m_Manager;

  void HandleInput();
  void Update();
  void Draw();
};
