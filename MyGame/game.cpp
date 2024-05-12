//#include "init.h"
//#include "function.h"
//#include "object.h"
//#include "game.h"
//
//static bool lose_message_written = false;
//
//void GameLoop()
//{
//    Object shooter;
//    SDL_Rect shooter_rect = {SCREEN_WIDTH/2, SCREEN_HEIGHT - SHOOTER_HEIGHT, SHOOTER_WIDTH, SHOOTER_HEIGHT};
//    shooter.Set_Rect(shooter_rect);
//
//    Enemy* enemies = new Enemy[ENEMY_NUMS];
//    Init_Enemy(enemies);
//
//    bool quit = false;
//    SDL_Event event;
//    while (!quit)
//    {
//        while (SDL_PollEvent(&event)!=0)
//        {
//            if (event.type == SDL_QUIT) {quit = true;}
//            shooter.HandleKey(event, bullet_sound);
//        }
//
//        shooter.Move(SCREEN_WIDTH, SCREEN_HEIGHT);
//        shooter_rect = shooter.Get_Rect();
//        LoadImage("background.png", renderer, NULL);
//        LoadImage("plane.png", renderer, &shooter_rect);
//
//        for (int i=0;i<ENEMY_NUMS;i++)
//        {
//            Enemy* enemy = (enemies + i);
//            enemy->Move(SCREEN_WIDTH, SCREEN_HEIGHT, 3);
//            SDL_Rect enemy_rect = enemy->Get_Rect();
//            LoadImage("enemy.png", renderer, &enemy_rect);
//            enemy->Make_Bullet_Move(SCREEN_WIDTH, SCREEN_HEIGHT, shooter_rect);
//
//
//            if (Check_Collision(shooter_rect, enemy_rect) == true)
//            {
//                SHOOTER_HEALTH--;
//                enemy->Reset();
//            }
//        }
//        if (SHOOTER_HEALTH <= 0)
//        {
//            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "you lose");
//            lose_message_written = true;
//            quit = true;
//        }
//
//
//        vector <Bullet*> ammo_list = shooter.Get_Bullet_List();
//        for (unsigned int i=0;i<shooter.Get_Bullet_List().size();i++)
//        {
//            Bullet* ammo = ammo_list.at(i);
//            if (ammo != NULL)
//            {
//                if (ammo->Get_Active() == true)
//                {
//                    ammo->Move(SCREEN_WIDTH, 0, -20);
//                    SDL_Rect ammo_rect = ammo->Get_Rect();
//                    LoadImage("bul_laser.png", renderer,&ammo_rect);
//
//
//                    for (int t=0;t<ENEMY_NUMS;t++)
//                    {
//                        Enemy* enemy = (enemies+t);
//                        SDL_Rect enemy_rect = enemy->Get_Rect();
//                        if (Check_Collision(ammo_rect, enemy_rect) == true)
//                        {
//                            enemy->Reset();
//                            ammo->Set_Active(false);
//                            break;
//                        }
//                    }
//                }
//                else
//                {
//                    if (ammo !=NULL)
//                    {
//                        ammo_list.erase(ammo_list.begin()+i);
//                        shooter.Set_Bullet_List(ammo_list);
//                        delete ammo;
//                        ammo = NULL;
//                    }
//                }
//            }
//        }
//        Hp_Bar("hp.png");
//        SDL_RenderPresent(renderer);
//    }
//    delete [] enemies;
//}
