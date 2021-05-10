#include <cstdlib>
#include <iostream>

#include <emscripten.h>

using namespace std;

enum eDirection { STOP = 0, UP, DOWN, LEFT, RIGHT };

class SnakePart
{
public:
    int X,
    int Y
    SnakePart( int x, int y )
    {
        X = x;
        Y = y
    }
};

int gameOver = false;
int speed = 10;

int canvasWidth = 400;
int canvasHeight = 400;
int tileCount = 20;
int tileSize = 400 / tileCount - 2;

int headX = 10;
int headY = 10;
int prevX;
int prevY;

int length = 0;
int tail[];

int xVelocity = 0;
int yVelocity = 0;

int score = 0;

void drawGame( void * _guess )
{
    if(!isGameOver(gameOver))
    {
        clearScreen();
        changeSnakePosition();
        logic();
        drawFruit();
        drawSnake();
        drawTail();
        drawScore();
        setTimeout( drawGame, 1000 / speed );
    }
    if(isGameOver(gameOver))
    {
        ctx.fillStyle = "white";
        ctx.font = "50px Verdana";
        ctx.fillText("Game Over!", canvasWidth / 6.5, canvasHeight / 2);
    }
}


int main()
{
    if(!isGameOver(gameOver))
    {
        drawGame();
    } else if(isGameOver(gameOver))
    {
        ctx.fillStyle = "white";
        ctx.font = "50px Verdana";
        ctx.fillText("Game Over!", canvasWidth / 6.5, canvasHeight / 2);
    }
    emscripten_set_main_loop_arg(drawGame, guess, 0, false)
}