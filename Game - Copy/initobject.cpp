#include "function.h"
#include "object.h"
#include "enemy.h"

MainObject shooter;
    shooter.setX(SCREEN_WIDTH/2 - 26);
    shooter.setY(SCREEN_HEIGHT - 67);

    Enemy* enemies = new Enemy[ENEMY_NUMS];
    for (int i=0;i<ENEMY_NUMS;i++)
    {
        Enemy* enemy = (enemies + i);
        enemy->setX(rand()%SCREEN_WIDTH);
        if (enemy->getX() + ENEMY_WIDTH > SCREEN_WIDTH) enemy->setX(SCREEN_WIDTH);
        enemy->setY(-(rand()%SCREEN_HEIGHT));

        Bullet* enemy_bullet = new Bullet;
        enemy->Init_Bullet(enemy_bullet);
    }
