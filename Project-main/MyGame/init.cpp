#include "function.h"
#include "object.h"
#include "init.h"

bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING)!=0)
    {
        return false;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
    {
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
    {
        return false;
    }
    bullet_sound = Mix_LoadWAV("shooting.wav");
    background_sound = Mix_LoadMUS("bkg_music.mp3");
    if (bullet_sound == NULL)
    {
            return false;
    }

    TTF_Init();
    return true;
}

void Init_Enemy(Enemy* enemies)
{
    for (int i=0;i<ENEMY_NUMS;i++)
    {
        Enemy* enemy = (enemies + i);
        SDL_Rect enemy_rect;
        enemy_rect.x = rand()%SCREEN_WIDTH;
        if (enemy_rect.x + ENEMY_WIDTH > SCREEN_WIDTH) enemy_rect.x = SCREEN_WIDTH - ENEMY_WIDTH;
        enemy_rect.y = -(rand()%SCREEN_HEIGHT);
        enemy_rect.w = ENEMY_WIDTH;
        enemy_rect.h = ENEMY_HEIGHT;
        enemy->Set_Rect(enemy_rect);
        Bullet* enemy_ammo = new Bullet;
        enemy->Init_Bullet(enemy_ammo);
    }
    for (int i=0;i<ENEMY_NUMS;i++)
    {
        for (int j=i+1;j<ENEMY_NUMS;j++)
        {
            Enemy* enemy1 = (enemies+i);
            Enemy* enemy2 = (enemies+j);
            if (Check_Collision(enemy1->Get_Rect(), enemy2->Get_Rect()) == true)
            {
                SDL_Rect tmp_rect = enemy2->Get_Rect();
                tmp_rect.y -= ENEMY_HEIGHT;
                enemy2->Set_Rect(tmp_rect);
            }
        }
    }
}


void Set_Menu_End_Game(TextObject text, TTF_Font* font)
{
    SDL_Rect end_game_rect = {SCREEN_WIDTH/2-200, SCREEN_HEIGHT/2-200, 400, 300};
    LoadImage("end_game.png", renderer, &end_game_rect);

    text.Score = text.Check_Digit(text.Inf);
    ifstream file("highScore.txt");
    file>>text.High_Score;
    file.close();
    if (text.Score >  text.High_Score)
    {
        text.High_Score = text.Score;
        ofstream file("highScore.txt");
        file << text.High_Score;
        file.close();
    }
    string score = to_string(text.Score);
    SDL_Rect score_rect ;
    score_rect.x = 254;
    score_rect.y = 280;
    score_rect.w = 30;
    score_rect.h = 30;
    LoadText(score, font, &score_rect);
    ifstream file1("highScore.txt");
    string high_score;
    file1 >> high_score;
    file1.close();
    SDL_Rect high_score_rect ;
    high_score_rect.x = 254;
    high_score_rect.y = 330;
    high_score_rect.w = 30;
    high_score_rect.h = 30;
    LoadText(high_score, font, &high_score_rect);

}
