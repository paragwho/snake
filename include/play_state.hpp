#pragma once
#include "apple.hpp"
#include "base_state.hpp"
#include "snake.hpp"
#include "timer.hpp"

class PlayState : public BaseState {
public:
  PlayState();

  void HandleInput(Game &game) override;
  void Update(Game &game) override;
  void Draw() const override;

private:
  Snake m_Snake;
  Apple m_Apple;
  Timer m_MoveSnakeTimer;

  int m_Score = 0;

  bool IsAppleEaten(Apple &apple, Snake &snake);
};
