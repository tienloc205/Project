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

    MainObject shooter;
    shooter.setX(SCREEN_WIDTH/2-26);
    shooter.setY(SCREEN_HEIGHT-67);
    Enemy enemy;

    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event)!=0)
        {
            if (event.type == SDL_QUIT) {quit = true;}
            shooter.HandleKey(event);

            SDL_RenderClear(renderer);

            SDL_Rect rect_shooter = {shooter.getX(),shooter.getY(), 53, 67};
            LoadImage("background.png", renderer, NULL);
            LoadImage("plane.jpg", renderer, &rect_shooter);

            shooter.Move();
            SDL_Rect rect_enemy = {enemy.getX(),enemy.getY(), 76, 50};
            LoadImage("enemy.png", renderer, &rect_enemy);
            enemy.Move();

            for (unsigned int i=0;i<shooter.getAmmoList().size();i++)
            {
                vector <Bullet*> _ammo_list = shooter.getAmmoList();
                Bullet* ammo = _ammo_list.at(i);
                if (ammo != NULL)
                {
                    if (ammo->getActive() == true)
                    {
                        ammo->Move(SCREEN_WIDTH, 0);
                        SDL_Rect bul_rect = {ammo->getX(), ammo->getY(), 5, 20};
                        LoadImage("bul_laser.png", renderer, &bul_rect);
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

    return 0;
}
