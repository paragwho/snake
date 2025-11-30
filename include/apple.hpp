#pragma once
#include "raylib.h"

class Apple {
public:
  Apple(Vector2 position);

  void Draw() const;

  Vector2 GetPosition() const;
  void SetPosition(Vector2 position);

private:
  Vector2 m_Position;
};
