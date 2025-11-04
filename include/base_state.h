#pragma once

class BaseState {
public:
  virtual ~BaseState() = default;

  virtual void HandleInput() = 0;
  virtual void Update() = 0;
  virtual void Draw() const = 0;
};
