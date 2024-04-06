#include "function.h"
#include "object.h"
#include "enemy.h"
Enemy::Enemy()
{
    x = SCREEN_WIDTH/2+100;
    y = 0;
    dy = 3;
}

void Enemy::Move()
{
    y += dy;
    if (y>SCREEN_HEIGHT)
    {
        y = 0;
    }

}

