#pragma once
#include "base_state.h"

class GameOverState : public BaseState {
public:
  GameOverState(int score);

  void HandleInput() override;
  void Update() override;

  void Draw() const override;

private:
  int m_Score;
};
