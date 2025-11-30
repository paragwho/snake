#pragma once
#include "raylib.h"

class Timer {
public:
  bool IsTriggered(double interval) {
    double currentTime = GetTime();

    if (currentTime - m_LastTime >= interval) {
      m_LastTime = currentTime;
      return true;
    }

    return false;
  }

private:
  double m_LastTime = 0;
};
