#pragma once
#include "raylib.h"

// Window config
inline const char *WINDOW_NAME = "Snake";
constexpr int TARGET_FPS = 60;

constexpr int CELL_SIZE = 30;
constexpr int CELL_COUNT = 25;

constexpr int SCREEN_WIDTH = CELL_SIZE * CELL_COUNT;
constexpr int SCREEN_HEIGHT = CELL_SIZE * CELL_COUNT;

// Colors
constexpr Color MY_GREEN = {173, 204, 96, 255};
constexpr Color MY_DARK_GREEN = {43, 51, 24, 255};

// Text rendering
constexpr int GAP_TO_BORDER = 1;
constexpr int TITLE_FONT_SIZE = 80;
constexpr int SCORE_FONT_SIZE = 40;
constexpr int INSTRUCTION_FONT_SIZE = 40;
constexpr int SPACING = 10;

// Snake config
constexpr Vector2 SNAKE_INITIAL_POSITION = {12, 11};
constexpr Vector2 SNAKE_INITIAL_DIRECTION = {0, -1};
constexpr int SNAKE_INITIAL_LENGTH = 3;
constexpr double MOVE_INTERVAL = 0.12;
