#pragma once
#include "base_state.h"
#include <memory>
#include <stack>

class BaseState;

class StateManager {
public:
  void PushState(std::unique_ptr<BaseState> state);
  void PopState();
  void ChangeState(std::unique_ptr<BaseState> state);

  BaseState *GetCurrentState() const;

private:
  std::stack<std::unique_ptr<BaseState>> m_States;
};
