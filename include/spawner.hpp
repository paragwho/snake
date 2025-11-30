#pragma once
#include "config.hpp"
#include "raylib.h"
#include "snake.hpp"

namespace Spawner {
inline Vector2 RandomPosition() {
  return {(float)GetRandomValue(BORDER_GAP_CELLS,
                                CELL_COUNT - BORDER_GAP_CELLS - 1),
          (float)GetRandomValue(BORDER_GAP_CELLS,
                                CELL_COUNT - BORDER_GAP_CELLS - 1)};
}

inline Vector2 GenerateValidPosition(Snake &snake) {
  Vector2 position = RandomPosition();
  do {
    position = RandomPosition();
  } while (snake.CheckCollisionAt(position));

  return position;
}
}; // namespace Spawner
