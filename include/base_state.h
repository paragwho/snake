#pragma once

class Game;

class BaseState {
public:
  virtual ~BaseState() = default;

  virtual void HandleInput(Game &game) = 0;
  virtual void Update(Game &game) = 0;
  virtual void Draw() const = 0;
};
