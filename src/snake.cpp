#include "snake.h"
#include "config.h"
#include "raymath.h"

Snake::Snake() : direction(SNAKE_INITIAL_DIRECTION), directionChanged(false) {
  initializeBody();
}

void Snake::initializeBody() {
  body.clear();
  for (int i = 0; i < SNAKE_INITIAL_LENGTH; i++) {
    body.push_back(
        Vector2Add(SNAKE_INITIAL_POSITION,
                   Vector2Scale(Vector2Negate(SNAKE_INITIAL_DIRECTION), i)));
  }
}

void Snake::move() {
  body.push_front(Vector2Add(body.front(), direction));
  body.pop_back();
  directionChanged = false;
}

void Snake::grow() { body.push_back(body.back()); }

void Snake::draw() const {
  for (int i = 0; i < body.size(); i++) {
    DrawRectangle(body[i].x * CELL_SIZE, body[i].y * CELL_SIZE, CELL_SIZE,
                  CELL_SIZE, MY_DARK_GREEN);
  }
}

void Snake::reset() {
  direction = SNAKE_INITIAL_DIRECTION;
  initializeBody();
}

Vector2 Snake::getHeadPosition() const { return body.front(); }

void Snake::handleInput() {
  if (directionChanged) {
    return;
  }

  if (IsKeyPressed(KEY_UP) && direction.y != 1) {
    direction = {0, -1};
    directionChanged = true;
  }
  if (IsKeyPressed(KEY_DOWN) && direction.y != -1) {
    direction = {0, 1};
    directionChanged = true;
  }
  if (IsKeyPressed(KEY_LEFT) && direction.x != 1) {
    direction = {-1, 0};
    directionChanged = true;
  }
  if (IsKeyPressed(KEY_RIGHT) && direction.x != -1) {
    direction = {1, 0};
    directionChanged = true;
  }
}

bool Snake::checkSelfCollision() const {
  for (int i = 1; i < body.size(); i++) {
    if (Vector2Equals(body.front(), body[i])) {
      return true;
    }
  }
  return false;
}

bool Snake::checkBoundaryCollision() const {
  return (getHeadPosition().x < 0 || getHeadPosition().x > CELL_COUNT - 1 ||
          getHeadPosition().y < 0 || getHeadPosition().y > CELL_COUNT - 1);
}

bool Snake::checkCollisionAt(Vector2 position) const {
  for (int i = 0; i < body.size(); i++) {
    if (Vector2Equals(position, body[i])) {
      return true;
    }
  }
  return false;
}
