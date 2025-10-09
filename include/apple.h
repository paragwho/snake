#pragma once
#include "raylib.h"

class Apple {
public:
  Apple(Vector2 Position);
  void draw() const;
  Vector2 getPosition() const;
  void setPosition(Vector2 Position);

private:
  Vector2 position;
};
