#pragma once
#include <memory>
#include <vector>

class BaseState;

class StateManager {
public:
  void HandleInput();
  void Update();

  void Draw();

  void PushState(std::unique_ptr<BaseState> state);
  void PopState();
  void ChangeState(std::unique_ptr<BaseState> state);

  BaseState *GetCurrentState() const;

private:
  std::vector<std::unique_ptr<BaseState>> m_States;
};
