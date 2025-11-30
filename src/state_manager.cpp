#include "state_manager.hpp"
#include <utility>

void StateManager::PushState(std::unique_ptr<BaseState> state) {
  m_States.push(std::move(state));
}

void StateManager::PopState() {
  if (!m_States.empty())
    m_States.pop();
}

void StateManager::ChangeState(std::unique_ptr<BaseState> state) {
  if (!m_States.empty()) {
    m_States.pop();
  }
  m_States.push(std::move(state));
}

BaseState *StateManager::GetCurrentState() const {
  if (!m_States.empty()) {
    return m_States.top().get();
  }
  return nullptr;
}
