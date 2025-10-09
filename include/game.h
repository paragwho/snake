#pragma once
#include "apple.h"
#include "config.h"
#include "snake.h"
#include "timer.h"

class Game {
public:
  Game();
  void draw() const;
  void update();
  int getScore() const;
  GameState getState() const;

private:
  int score;
  GameState gameState;
  Snake snake;
  Apple apple;
  Timer moveSnake;

  bool isAppleEaten(Apple &apple, Snake &snake);
  void reset();
};
