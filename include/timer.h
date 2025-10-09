#pragma once
#include "raylib.h"

struct Timer {
  double lastTime = 0;

  bool isTriggered(double interval) {
    double currentTime = GetTime();

    if (currentTime - lastTime >= interval) {
      lastTime = currentTime;
      return true;
    }

    return false;
  }
};
