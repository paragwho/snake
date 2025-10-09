#pragma once
#include "raylib.h"
#include <deque>

class Snake {
public:
  Snake();
  void draw() const;
  void move();
  void grow();
  void reset();
  void handleInput();
  Vector2 getHeadPosition() const;
  bool checkSelfCollision() const;
  bool checkBoundaryCollision() const;
  bool checkCollisionAt(Vector2 position) const;

private:
  std::deque<Vector2> body;
  Vector2 direction;
  bool directionChanged;

  void initializeBody();
};
