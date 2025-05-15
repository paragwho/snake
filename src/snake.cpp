#include <raylib.h>
#include <raymath.h>
#include <string>
#include <deque>

using namespace std;

const int CELL_SIZE = 30;
const int CELL_COUNT = 25;
const int OFFSET = 75;

Color myGreen = {173, 204, 96, 255};
Color myDarkGreen = {43, 51, 24, 255};

string gameState = "playing";
int appleCount = 0;

struct Timer
{
    double lastTime = 0;

    bool isTriggered(double interval)
    {
        double currentTime = GetTime();
        if (currentTime - lastTime >= interval)
        {
            lastTime = currentTime;
            return true;
        }
        return false;
    }
};

class Food
{
public:
    Vector2 position = {12, 6};

    void reset()
    {
        position = {12, 6};
    }

    void draw()
    {
        DrawRectangle(OFFSET + CELL_SIZE * position.x, OFFSET + CELL_SIZE * position.y, CELL_SIZE, CELL_SIZE, RED);
    }

    void update(Vector2 newPosition)
    {
        position = newPosition;
    }
};

class Snake
{
public:
    Vector2 direction = {1, 0};
    deque<Vector2> body = {{12, 12}, {11, 12}, {10, 12}};
    Timer moveSnake;

    void grow()
    {
        body.push_back(Vector2Add(body.back(), direction));
    }

    void reset()
    {
        direction = {1, 0};
        body = {{12, 12}, {11, 12}, {10, 12}};
    }

    void draw()
    {
        for (int i = 0; i < body.size(); i++)
        {
            DrawRectangle(OFFSET + body[i].x * CELL_SIZE, OFFSET + body[i].y * CELL_SIZE, CELL_SIZE, CELL_SIZE, myDarkGreen);
        }
    }

    void update()
    {
        if (moveSnake.isTriggered(0.12))
        {
            body.pop_back();
            body.push_front(Vector2Add(body.front(), direction));
        }
    }
};

class Game
{
public:
    Food food = Food();
    Snake snake = Snake();

    bool isFoodEaten()
    {
        if (Vector2Equals(food.position, snake.body.front()))
        {
            return true;
        }
        return false;
    }

    Vector2 randomPosition()
    {
        return {(float)GetRandomValue(2, 22), (float)GetRandomValue(2, 22)};
    }

    bool isValidPosition(Vector2 position)
    {
        for (int i = 0; i < snake.body.size(); i++)
        {
            if (Vector2Equals(position, snake.body[i]))
            {
                return false;
            }
        }
        return true;
    }

    Vector2 generateValidPosition()
    {
        Vector2 position = randomPosition();
        do
        {
            position = randomPosition();
        } while (!isValidPosition(position));

        return position;
    }

    bool collideSelf()
    {
        for (int i = 1; i < snake.body.size(); i++)
        {
            if (Vector2Equals(snake.body.front(), snake.body[i]))
            {
                return true;
            }
        }
        return false;
    }

    bool collideBoundary()
    {
        Vector2 snakeHead = snake.body.front();
        if (snakeHead.x < 0 || snakeHead.x > 24 || snakeHead.y < 0 || snakeHead.y > 24)
        {
            return true;
        }
        return false;
    }

    void reset()
    {
        food.reset();
        snake.reset();
        appleCount = 0;
        gameState = "playing";
    }

    void gameover()
    {
        drawTitle();
        drawBoundary();
        DrawText("GAME OVER", OFFSET + 6 * CELL_SIZE, OFFSET + 7 * CELL_SIZE, 72, myDarkGreen);
        DrawText(TextFormat("SCORE : %i", appleCount), OFFSET + 8 * CELL_SIZE, OFFSET + 12 * CELL_SIZE, 54, myDarkGreen);
        DrawText("PRESS ENTER TO RESTART", OFFSET + 4 * CELL_SIZE, OFFSET + 16 * CELL_SIZE, 36, myDarkGreen);
    }

    void drawTitle()
    {
        DrawText("SNAKE", 20, 16, 50, myDarkGreen);
    }

    void drawScore()
    {
        DrawText(TextFormat("SCORE : %i", appleCount), 20, CELL_SIZE * CELL_COUNT + 100, 36, myDarkGreen);
    }

    void drawBoundary()
    {
        DrawRectangleLinesEx(Rectangle{OFFSET - 5, OFFSET - 5, CELL_SIZE * CELL_COUNT + 10, CELL_SIZE * CELL_COUNT + 10}, 5, myDarkGreen);
    }

    void draw()
    {
        food.draw();
        snake.draw();
        drawTitle();
        drawScore();
        drawBoundary();
    }

    void update()
    {
        if (isFoodEaten())
        {
            snake.grow();
            food.update(generateValidPosition());
            appleCount++;
        }

        if (collideSelf() || collideBoundary())
        {
            gameState = "gameover";
        }

        else
        {
            snake.update();
        }
    }
};

int main()
{
    InitWindow(CELL_SIZE * CELL_COUNT + 2 * OFFSET, CELL_SIZE * CELL_COUNT + 2 * OFFSET, "Snake");
    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1)
        {
            game.snake.direction = {0, -1};
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1)
        {
            game.snake.direction = {0, 1};
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1)
        {
            game.snake.direction = {-1, 0};
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1)
        {
            game.snake.direction = {1, 0};
        }

        ClearBackground(myGreen);

        if (gameState == "playing")
        {
            game.update();
            game.draw();
        }
        else if (gameState == "gameover")
        {
            game.gameover();
            if (IsKeyPressed(KEY_ENTER))
            {
                game.reset();
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
