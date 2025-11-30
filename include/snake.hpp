#pragma once
#include "raylib.h"
#include <deque>

class Snake {
public:
  Snake();

  void HandleInput();
  void Move();
  void Grow();
  void Draw() const;

  Vector2 GetHeadPosition() const;
  bool CheckSelfCollision() const;
  bool CheckBoundaryCollision() const;
  bool CheckCollisionAt(Vector2 position) const;

private:
  std::deque<Vector2> m_Body;
  Vector2 m_Direction;

  bool m_DirectionChanged = false;
};
