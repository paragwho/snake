#include "apple.h"
#include "config.h"

Apple::Apple(Vector2 position) : m_Position(position) {}

void Apple::Draw() const {
  DrawRectangle(CELL_SIZE * m_Position.x, CELL_SIZE * m_Position.y, CELL_SIZE,
                CELL_SIZE, RED);
}

Vector2 Apple::GetPosition() const { return m_Position; }

void Apple::SetPosition(Vector2 position) { m_Position = position; }
