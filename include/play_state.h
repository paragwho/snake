#pragma once
#include "apple.h"
#include "base_state.h"
#include "snake.h"
#include "timer.h"

class PlayState : public BaseState {
public:
  PlayState();

  void HandleInput() override;
  void Update() override;

  void Draw() const override;

private:
  Snake m_Snake;
  Apple m_Apple;
  Timer m_MoveSnakeTimer;

  int m_Score = 0;
  bool m_GameOver = false;

  bool IsAppleEaten(Apple &apple, Snake &snake);
};
