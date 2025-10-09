#include "apple.h"
#include "config.h"

Apple::Apple(Vector2 Position) : position(Position) {}

void Apple::draw() const {
  DrawRectangle(CELL_SIZE * position.x, CELL_SIZE * position.y, CELL_SIZE,
                CELL_SIZE, RED);
}

Vector2 Apple::getPosition() const { return position; }

void Apple::setPosition(Vector2 Position) { position = Position; }
