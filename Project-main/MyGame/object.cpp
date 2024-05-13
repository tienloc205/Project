#include "function.h"
#include "object.h"


void Object::HandleKey(SDL_Event event, Mix_Chunk* bul_sound)
{
  if (event.type == SDL_KEYDOWN and event.key.keysym.sym != SDLK_SPACE)
  {
      switch (event.key.keysym.sym)
      {
      case SDLK_UP: dy-=17; break;
      case SDLK_DOWN: dy+=17; break;
      case SDLK_RIGHT: dx+=21;break;
      case SDLK_LEFT: dx-=21;break;
      }
  }
  else if (event.type == SDL_KEYUP)
  {
      switch (event.key.keysym.sym)
      {
      case SDLK_UP: dy=0; break;
      case SDLK_DOWN: dy=0; break;
      case SDLK_RIGHT: dx=0;break;
      case SDLK_LEFT: dx=0;break;
      }
  }
  else if (event.type == SDL_KEYDOWN and event.key.keysym.sym == SDLK_SPACE)
  {
      if (SHOOTER_HEALTH>0)
      {
          Bullet* bullet = new Bullet;
          SDL_Rect bullet_rect;
          bullet_rect.x = rect.x + rect.w/2;
          bullet_rect.y = rect.y;
          bullet_rect.w = BULLET_WIDTH;
          bullet_rect.h = BULLET_HEIGTH;
          bullet->Set_Rect(bullet_rect);
          bullet->Set_Active(true);
          bullet_list.push_back(bullet);
          Mix_PlayChannel(-1, bul_sound, 0);
      }
  }
}


void Object::Move(const int& x_des, const int y_des)
{
    rect.x += dx;
    if (rect.x < 0 || rect.x+rect.w > SCREEN_WIDTH)
    {
        rect.x -= dx;
    }
    rect.y += dy;
    if (rect.y < 0 || rect.y+rect.h > SCREEN_HEIGHT)
    {
        rect.y -= dy;
    }
}


void Bullet::Move(const int& x_des, const int& y_des, int y)
{
  if (active == true)
  {
    dy = y;
    rect.y += dy;
    if (rect.y < y_des or )
    {
      active = false;
    }
  }
}

void Bullet::Enemy_Move(const int& x_des, const int& y_des, int y)
{
    dy = y;
    rect.y += dy;
    if (rect.y > SCREEN_HEIGHT)
    {
        active = false;
    }
}

void Enemy::Move(const int& x_des, const int& y_des, int y)
{
    dy = y;
    rect.y += dy;
    if (rect.y > SCREEN_HEIGHT)
    {
        rect.y = -rand()%SCREEN_HEIGHT;
        rect.x = rand()%SCREEN_WIDTH;
        if (rect.x + ENEMY_WIDTH > SCREEN_WIDTH) rect.x = SCREEN_WIDTH - ENEMY_WIDTH;
    }
}

void Enemy::Init_Bullet(Bullet* enemy_bullet)
{
    if (enemy_bullet != NULL)
    {
        enemy_bullet->Set_Active(true);
        SDL_Rect enemy_bullet_rect = {rect.x + ENEMY_WIDTH/2, rect.y + ENEMY_HEIGHT, BULLET_WIDTH, BULLET_HEIGTH};
        enemy_bullet->Set_Rect(enemy_bullet_rect);
        bullet_list.push_back(enemy_bullet);
    }
}

void Enemy::Make_Bullet_Move(const int& x_des, const int& y_des, SDL_Rect player)
{
    for (unsigned int i=0;i<bullet_list.size();i++)
    {
        Bullet* enemy_bullet= bullet_list.at(i);
        if (enemy_bullet != NULL)
        {
            if (enemy_bullet->Get_Active() == true and rect.x>=0 and rect.y>=0)
            {
                enemy_bullet->Enemy_Move(SCREEN_WIDTH, SCREEN_HEIGHT, 10);
                SDL_Rect enemy_bullet_rect = {enemy_bullet->Get_Rect().x, enemy_bullet->Get_Rect().y, BULLET_WIDTH, BULLET_HEIGTH};
                enemy_bullet->Set_Rect(enemy_bullet_rect);
                LoadImage("bul_enemy.png", renderer, &enemy_bullet_rect);
                if (Check_Collision(enemy_bullet_rect, player) == true)
                {
                    enemy_bullet->Set_Active(false);
                    SHOOTER_HEALTH--;
                }
            }
            else
            {
                enemy_bullet->Set_Active(true);
                SDL_Rect enemy_bullet_rect = {rect.x + ENEMY_WIDTH/2, rect.y + ENEMY_HEIGHT, BULLET_WIDTH, BULLET_HEIGTH};
                enemy_bullet->Set_Rect(enemy_bullet_rect);
            }
        }
    }
}


void Enemy::Reset()
{
    rect.y = -rand()%SCREEN_HEIGHT;
    rect.x = rand()%SCREEN_WIDTH;
    if (rect.x + ENEMY_WIDTH > SCREEN_WIDTH) rect.x = SCREEN_WIDTH - ENEMY_WIDTH;
}


Enemy::~Enemy()
{
    if (bullet_list.size()>0)
    {
        for (unsigned int i=0;i<bullet_list.size();i++)
        {
            delete bullet_list.at(i);
            bullet_list.at(i) = NULL;
        }
    }
    bullet_list.clear();

}


int TextObject::Check_Digit(string text)
{
    int digit;
    for (unsigned int i = 0; i < text.size(); ++i)
    {
        if (isdigit(text[i]))
        {
            string number;
            while (isdigit(text[i]))
            {
                number += text[i];
                ++i;
            }
            digit = stoi(number);
        }
    }
    return digit;
}


string TextObject::Change_Score(string text)
{
    int score = Check_Digit(text);
    score++;
    string Score_Checked ="Score: " + to_string(score);
    return Score_Checked;
}

