#pragma once
#include "base_state.h"

class GameOverState : public BaseState {
public:
  GameOverState(int score);

  void HandleInput(Game &game) override;
  void Update(Game &game) override;
  void Draw() const override;

private:
  int m_Score;
};
