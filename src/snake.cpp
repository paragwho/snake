#include "snake.hpp"
#include "config.hpp"
#include "raylib.h"
#include "raymath.h"

Snake::Snake() : m_Direction(SNAKE_INITIAL_DIRECTION) {
  for (int i = 0; i < SNAKE_INITIAL_LENGTH; i++) {
    m_Body.push_back(
        Vector2Add(SNAKE_INITIAL_POSITION,
                   Vector2Scale(Vector2Negate(SNAKE_INITIAL_DIRECTION), i)));
  }
}

void Snake::HandleInput() {
  if (m_DirectionChanged) {
    return;
  }

  if (IsKeyPressed(KEY_UP) && m_Direction.y != 1) {
    m_Direction = {0, -1};
    m_DirectionChanged = true;
  }
  if (IsKeyPressed(KEY_DOWN) && m_Direction.y != -1) {
    m_Direction = {0, 1};
    m_DirectionChanged = true;
  }
  if (IsKeyPressed(KEY_LEFT) && m_Direction.x != 1) {
    m_Direction = {-1, 0};
    m_DirectionChanged = true;
  }
  if (IsKeyPressed(KEY_RIGHT) && m_Direction.x != -1) {
    m_Direction = {1, 0};
    m_DirectionChanged = true;
  }
}

void Snake::Move() {
  m_Body.push_front(Vector2Add(m_Body.front(), m_Direction));
  m_Body.pop_back();
  m_DirectionChanged = false;
}

void Snake::Grow() { m_Body.push_back(m_Body.back()); }

void Snake::Draw() const {
  for (int i = 0; i < m_Body.size(); i++) {
    Rectangle bodySegment = {m_Body[i].x * CELL_SIZE, m_Body[i].y * CELL_SIZE,
                             CELL_SIZE, CELL_SIZE};
    DrawRectangleRounded(bodySegment, 0.5f, 8, MY_DARK_GREEN);
  }
}

Vector2 Snake::GetHeadPosition() const { return m_Body.front(); }

bool Snake::CheckSelfCollision() const {
  for (int i = 1; i < m_Body.size(); i++) {
    if (Vector2Equals(m_Body.front(), m_Body[i])) {
      return true;
    }
  }
  return false;
}

bool Snake::CheckBoundaryCollision() const {
  return (GetHeadPosition().x < BORDER_GAP_CELLS ||
          GetHeadPosition().x > CELL_COUNT - BORDER_GAP_CELLS - 1 ||
          GetHeadPosition().y < BORDER_GAP_CELLS ||
          GetHeadPosition().y > CELL_COUNT - BORDER_GAP_CELLS - 1);
}

bool Snake::CheckCollisionAt(Vector2 position) const {
  for (int i = 0; i < m_Body.size(); i++) {
    if (Vector2Equals(position, m_Body[i])) {
      return true;
    }
  }
  return false;
}
