#include "function.h"
#include "object.h"
#include "enemy.h"

void Enemy::Move()
{
    y += 3;
    if (y>SCREEN_HEIGHT)
    {
        y = 0;
        int x_rand = rand()%400;
        x = x_rand;
    }

}


void Enemy::Init_Bullet(Bullet* enemy_bullet)
{
    if (enemy_bullet != NULL)
    {
        enemy_bullet->setX(x+30);
        enemy_bullet->setY(y+50);
        enemy_bullet_list.push_back(enemy_bullet);
    }
}

void Enemy::Enemy_Bullet_Move(const int& x_des, const int& y_des)
{
    for (unsigned int i=0;i<enemy_bullet_list.size();i++)
    {
        Bullet* enemy_ammo = enemy_bullet_list.at(i);
        if (enemy_ammo != NULL)
        {
            if (enemy_ammo->getActive() == true)
            {
                enemy_ammo->Enemy_Move(SCREEN_WIDTH, SCREEN_HEIGHT);
                SDL_Rect rect_enemy_bullet = {enemy_ammo->getX(), enemy_ammo->getY(), BULLET_WIDTH, BULLET_HEIGTH};
                enemy_ammo->setRect(rect_enemy_bullet);
                LoadImage("bul_enemy.png", renderer,&rect_enemy_bullet);
            }
            else
            {
                enemy_ammo->setActive(true);
                enemy_ammo->setX(x+30);
                enemy_ammo->setY(y+45);
            }
        }
    }
}

void Bullet::Enemy_Move(const int& x_des, const int& y_des)
{
    dy = 8;
    y += dy;
    if (y > SCREEN_HEIGHT)
    {
        active =false;
    }
}
Enemy::~Enemy()
{
    if (enemy_bullet_list.size()>0)
    {
        for (unsigned int i=0;i<enemy_bullet_list.size();i++)
        {
            delete enemy_bullet_list.at(i);
            enemy_bullet_list.at(i) = NULL;
        }
    }
    enemy_bullet_list.clear();

}
