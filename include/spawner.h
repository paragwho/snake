#pragma once
#include "config.h"
#include "raylib.h"
#include "snake.h"

namespace Spawner {
inline Vector2 randomPosition() {
  return {(float)GetRandomValue(0, CELL_COUNT - 1),
          (float)GetRandomValue(0, CELL_COUNT - 1)};
}

inline Vector2 generateValidPosition(Snake &snake) {
  Vector2 position = randomPosition();
  do {
    position = randomPosition();
  } while (snake.checkCollisionAt(position));

  return position;
}
}; // namespace Spawner
