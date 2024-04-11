#include "function.h"
#include "object.h"
#include "enemy.h"

bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
        return false;
    }
    return true;
}


int main(int arg, char* argv[])
{
    if (Init() == false) return 0;
    srand(time(0));

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

    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event)!=0)
        {
            if (event.type == SDL_QUIT) {quit = true;}

            shooter.HandleKey(event);
            SDL_RenderClear(renderer);


            LoadImage("background.png", renderer, NULL);

            int health = 2;
            SDL_Rect rect_shooter = {shooter.getX(), shooter.getY(), 53, 67};
            shooter.setRect(rect_shooter);
            LoadImage("plane.jpg", renderer, &rect_shooter);
            shooter.Move();

            for (int i=0;i<ENEMY_NUMS;i++)
            {
                Enemy* enemy = (enemies + i);
                enemy->Move();
                SDL_Rect rect_enemy = {enemy->getX(), enemy->getY(), ENEMY_WIDTH, ENEMY_HEIGHT};
                enemy->setRect(rect_enemy);
                LoadImage("enemy.png", renderer, &rect_enemy);
                enemy->Enemy_Bullet_Move(SCREEN_WIDTH, SCREEN_HEIGHT);

                // va cham main va dich
                if (Is_Alive(health, shooter.getRect(), enemy->getRect()) == false)
                {
                    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "thua");
                }

                // va cham main va dan dich
                vector <Bullet*> enemy_ammo_list = enemy->Get_Enemy_Bullet();
                for (unsigned int i=0;i<enemy_ammo_list.size();i++)
                {
                    Bullet* enemy_ammo = enemy_ammo_list.at(i);
                    if (enemy_ammo != NULL)
                    {
                        if (Is_Alive(health, shooter.getRect(),enemy_ammo->getRect()) == false)
                        {
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "thua");
                        }
                    }
                }

                // va cham dan main va dich
                vector <Bullet*> ammo_list = shooter.getAmmoList();
                for (unsigned int i=0;i<ammo_list.size();i++)
                {
                    Bullet* ammo = ammo_list.at(i);
                    if (ammo != NULL)
                    {
                        if (Is_Alive(health, ammo->getRect(),enemy->getRect()) == false)
                        {
                            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "thua");
                        }
                    }
                }
            }

            for (unsigned int i=0;i<shooter.getAmmoList().size();i++)
            {
                vector <Bullet*> _ammo_list = shooter.getAmmoList();
                Bullet* ammo = _ammo_list.at(i);
                if (ammo != NULL)
                {
                    if (ammo->getActive() == true)
                    {
                        ammo->Move(SCREEN_WIDTH, 0);
                        SDL_Rect bullet_rect = {ammo->getX(), ammo->getY(), BULLET_WIDTH, BULLET_HEIGTH};
                        ammo->setRect(bullet_rect);
                        LoadImage("bul_laser.png", renderer, &bullet_rect);
                        SDL_RenderPresent(renderer);

                    }
                    else
                    {
                        if (ammo !=NULL)
                        {
                            _ammo_list.erase(_ammo_list.begin()+i);
                            shooter.SetAmmoList(_ammo_list);
                            delete ammo;
                            ammo = NULL;
                        }
                    }
                }
            }

            SDL_RenderPresent(renderer);
        }
    }
    delete [] enemies;
    Quit(window, renderer);
    return 0;
}
