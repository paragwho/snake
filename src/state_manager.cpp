#include "state_manager.h"
#include "base_state.h"

void StateManager::HandleInput() {
  if (BaseState *state = GetCurrentState())
    state->HandleInput();
}

void StateManager::Update() {
  if (BaseState *state = GetCurrentState())
    state->Update();
}

void StateManager::Draw() {
  if (BaseState *state = GetCurrentState())
    state->Draw();
}

void StateManager::PushState(std::unique_ptr<BaseState> state) {
  m_States.push_back(std::move(state));
}

void StateManager::PopState() {
  if (!m_States.empty())
    m_States.pop_back();
}

void StateManager::ChangeState(std::unique_ptr<BaseState> state) {
  m_States.clear();
  m_States.push_back(std::move(state));
}

BaseState *StateManager::GetCurrentState() const {
  return m_States.empty() ? nullptr : m_States.back().get();
}
