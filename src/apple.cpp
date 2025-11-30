#include "apple.hpp"
#include "config.hpp"
#include "raylib.h"

Apple::Apple(Vector2 position) : m_Position(position) {}

void Apple::Draw() const {
  Vector2 appleCenter = {CELL_SIZE * m_Position.x + CELL_SIZE / 2,
                         CELL_SIZE * m_Position.y + CELL_SIZE / 2};
  DrawCircleV(appleCenter, CELL_SIZE / 2, RED);
}

Vector2 Apple::GetPosition() const { return m_Position; }

void Apple::SetPosition(Vector2 position) { m_Position = position; }
