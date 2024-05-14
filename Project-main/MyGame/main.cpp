#include "function.h"
#include "object.h"
#include "init.h"

bool lose_message_written = false;
Object shooter;
Enemy* enemies = new Enemy[ENEMY_NUMS];
TextObject text;
int x_mouse, y_mouse;
bool isMute = false;
bool quit = false;

void Reset_Object()
{
    for(int i=0;i<ENEMY_NUMS;i++)
    {
        Enemy* enemy = (enemies+i);
        for (int t=0;t<enemy->Get_Bullet_List().size();t++)
        {
            Bullet* enemy_ammo = enemy->Get_Bullet_List().at(t);
            enemy_ammo->Set_Active(false);
        }
        enemy->Reset();
    }
    SDL_Rect shooter_rect = {SCREEN_WIDTH/2, SCREEN_HEIGHT - SHOOTER_HEIGHT, SHOOTER_WIDTH, SHOOTER_HEIGHT};
    shooter.Set_Rect(shooter_rect);
    text.Inf = "Score : 00";
}

void Handle_Menu(SDL_Event event)
{
    if (state == start )
    {

        if (isMute)
        {
            LoadImage("start2.jpg", renderer, NULL);
        }
        else
        {
            LoadImage("start1.jpg", renderer, NULL);
        }
        if (345 <= x_mouse && x_mouse <= SCREEN_WIDTH && 655 <= y_mouse && y_mouse <= SCREEN_HEIGHT && event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (isMute)
            {
                isMute = false;
                Mix_ResumeMusic();
            }
            else
            {
                isMute = true;
                Mix_PauseMusic();
            }
        }
        if (80 <= x_mouse && x_mouse <= 80+240 && 270 <= y_mouse && y_mouse <= 270+50 && event.type == SDL_MOUSEBUTTONDOWN)
        {
//            //Init_Enemy(enemies);
//            LoadImage("difficulty.png", renderer, NULL);
//            //showingDifficultyMenu = false;
//            state = difficulty;
              state = play;
        }

        if (80 <= x_mouse && x_mouse <= 80+240 && 390 <= y_mouse && y_mouse <= 390+50 && event.type == SDL_MOUSEBUTTONDOWN)
        {
            quit = true;
        }
    }
//    if (state == difficulty)
//    {
//        cout<<1;
//        LoadImage("difficulty.png", renderer, NULL);
//        if (event.key.keysym.sym == SDLK_d) ENEMY_NUMS = 6;
//        Init_Enemy(enemies);
//        state = play;
//    }

    if (state == play and event.key.keysym.sym == SDLK_RETURN)
    {
        state = pause;
        SDL_Rect pause_game_rect = {SCREEN_WIDTH/2-200, SCREEN_HEIGHT/2-200, 400, 300};
        LoadImage("pause.png", renderer, &pause_game_rect);
    }

    if (state == pause)
    {
        if (event.key.keysym.sym == SDLK_o)
        {
            state = retry;
        }
        if (event.key.keysym.sym == SDLK_e)
        {
            state = start;
        }
    }

    if(state == play and SHOOTER_HEALTH<=0)
    {
        if (120 <= x_mouse && x_mouse <= 120+75 && 380 <= y_mouse && y_mouse <= 380+75 && event.type == SDL_MOUSEBUTTONDOWN)
        {
            state = start;
            SHOOTER_HEALTH = 5;
            Reset_Object();
        }
        if (205 <= x_mouse && x_mouse <= 205+75 && 380 <= y_mouse && y_mouse <= 380+75 && event.type == SDL_MOUSEBUTTONDOWN)
        {
            state = retry;
            SHOOTER_HEALTH = 5;
            Reset_Object();
            Init_Enemy(enemies);
        }
    }
}

int main(int argc, char* argv[])
{
    if (Init() == false) return 0;

    SDL_Rect shooter_rect = {SCREEN_WIDTH/2, SCREEN_HEIGHT - SHOOTER_HEIGHT, SHOOTER_WIDTH, SHOOTER_HEIGHT};
    shooter.Set_Rect(shooter_rect);

    TTF_Font* font = TTF_OpenFont("Roboto-Regular.ttf", 25);
    text.Inf = "Score : 00";

    Mix_PlayMusic(background_sound, -1);
    SDL_Point point = {x_mouse, y_mouse};

    SDL_Event event;
    while (!quit)
    {
        SDL_GetMouseState(&x_mouse, &y_mouse);
        cout << x_mouse << " " << y_mouse << endl;
        while (SDL_PollEvent(&event)!=0)
        {
            if (event.type == SDL_QUIT) {quit = true;}
            shooter.HandleKey(event, bullet_sound);
            Handle_Menu(event);

        }

        if (state == play or state == retry){
        state = play;
        LoadImage("background.png", renderer, NULL);
        shooter.Move(SCREEN_WIDTH, SCREEN_HEIGHT);
        shooter_rect = shooter.Get_Rect();
        if (SHOOTER_HEALTH>0)LoadImage("plane.png", renderer, &shooter_rect);

        for (int i=0;i<ENEMY_NUMS;i++)
        {
            Enemy* enemy = (enemies + i);
            enemy->Move(SCREEN_WIDTH, SCREEN_HEIGHT, 3);
            SDL_Rect enemy_rect = enemy->Get_Rect();
            LoadImage("enemy.png", renderer, &enemy_rect);
            enemy->Make_Bullet_Move(SCREEN_WIDTH, SCREEN_HEIGHT, shooter_rect);


            if (Check_Collision(shooter_rect, enemy_rect) == true)
            {
                SHOOTER_HEALTH--;
                enemy->Reset();
            }
        }

        vector <Bullet*> ammo_list = shooter.Get_Bullet_List();
        for (unsigned int i=0;i<ammo_list.size();i++)
        {
            Bullet* ammo = ammo_list.at(i);
            if (ammo != NULL)
            {
                if (ammo->Get_Active() == true)
                {
                    ammo->Move(SCREEN_WIDTH, 0, -20);
                    SDL_Rect ammo_rect = ammo->Get_Rect();
                    LoadImage("bul_laser.png", renderer,&ammo_rect);


                    for (int t=0;t<ENEMY_NUMS;t++)
                    {
                        Enemy* enemy = (enemies+t);
                        SDL_Rect enemy_rect = enemy->Get_Rect();
                        if (Check_Collision(ammo_rect, enemy_rect) == true)
                        {
                            enemy->Reset();
                            ammo->Set_Active(false);
                            text.Inf = text.Change_Score(text.Inf);
                        }
                    }
                    if (SHOOTER_HEALTH<=0) ammo->Set_Active(false);
                }
                else
                {
                    if (ammo !=NULL)
                    {
                        ammo_list.erase(ammo_list.begin()+i);
                        shooter.Set_Bullet_List(ammo_list);
                        delete ammo;
                        ammo = NULL;
                    }
                }
            }
        }

        Hp_Bar("hp.png");
        SDL_Rect scoring_text_rect;
        scoring_text_rect.x = SCREEN_WIDTH/2 - text.Inf.length()/2;
        scoring_text_rect.y = 0;
        scoring_text_rect.w = 100;
        scoring_text_rect.h = 30;
        LoadText(text.Inf, font, &scoring_text_rect);

        if (SHOOTER_HEALTH <= 0)
        {
            Set_Menu_End_Game(text, font);
        }
        }
        SDL_RenderPresent(renderer);
    }

    delete [] enemies;
    TTF_CloseFont(font);
    Quit();
    return 0;
}
