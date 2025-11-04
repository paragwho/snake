#pragma once
#include "config.h"
#include "raylib.h"
#include "snake.h"

namespace Spawner {
inline Vector2 RandomPosition() {
  return {(float)GetRandomValue(0, CELL_COUNT - 1),
          (float)GetRandomValue(0, CELL_COUNT - 1)};
}

inline Vector2 GenerateValidPosition(Snake &snake) {
  Vector2 position = RandomPosition();
  do {
    position = RandomPosition();
  } while (snake.CheckCollisionAt(position));

  return position;
}
}; // namespace Spawner
