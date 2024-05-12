#include "function.h"
int state = 0;
int SHOOTER_HEALTH = 5;
int ENEMY_NUMS = 0;
Mix_Music* background_sound = NULL;
Mix_Chunk* bullet_sound = NULL;
SDL_Window* window = SDL_CreateWindow(SCREEN_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

void LoadImage(string path, SDL_Renderer* renderer, SDL_Rect* rect)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* LoadSurface = IMG_Load(path.c_str());
    texture = SDL_CreateTextureFromSurface(renderer, LoadSurface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_FreeSurface(LoadSurface);
    SDL_DestroyTexture(texture);
}

void LoadText(string text, TTF_Font* font, SDL_Rect* messageRect)
{
    SDL_Color textColor = { 255, 165, 0 }; // Màu cam
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font,text.c_str(), textColor);
    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    SDL_RenderCopy(renderer, messageTexture, NULL, messageRect);
    SDL_DestroyTexture(messageTexture);
}


bool Check_Collision(SDL_Rect object1, SDL_Rect object2)
{
    int left_a = object1.x;
  int right_a = object1.x + object1.w;
  int top_a = object1.y;
  int bottom_a = object1.y + object1.h;

  int left_b = object2.x;
  int right_b = object2.x + object2.w;
  int top_b = object2.y;
  int bottom_b = object2.y + object2.h;

  // Case 1: size object 1 < size object 2
  if (left_a > left_b && left_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (left_a > left_b && left_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (top_a > top_b && top_a < bottom_b)
    {
      return true;
    }
  }

  if (right_a > left_b && right_a < right_b)
  {
    if (bottom_a > top_b && bottom_a < bottom_b)
    {
      return true;
    }
  }

  // Case 2: size object 1 < size object 2
  if (left_b > left_a && left_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (left_b > left_a && left_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (top_b > top_a && top_b < bottom_a)
    {
      return true;
    }
  }

  if (right_b > left_a && right_b < right_a)
  {
    if (bottom_b > top_a && bottom_b < bottom_a)
    {
      return true;
    }
  }

   // Case 3: size object 1 = size object 2
  if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
  {
    return true;
  }

  return false;
}

void Hp_Bar(string path)
{
    int x = 0;
    for (int i=0;i<SHOOTER_HEALTH;i++)
    {
        SDL_Rect heart_rect = {x, 0, HEART_WIDTH, HEART_HEIGHT};
        LoadImage(path,renderer,&heart_rect);
        x += HEART_WIDTH;
    }
}

void Quit()
{
    TTF_Quit();
    Mix_FreeChunk(bullet_sound);
    Mix_FreeMusic(background_sound);
    Mix_CloseAudio();
    Mix_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
