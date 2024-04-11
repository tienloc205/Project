#include "function.h"

SDL_Window* window = SDL_CreateWindow(SCREEN_NAME.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

void LoadImage(string path, SDL_Renderer* renderer, SDL_Rect* rect)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* LoadSurface = IMG_Load(path.c_str());
    if (LoadSurface == NULL)
    {
        cout << "Enable to load image :" << path.c_str() << IMG_GetError();
    }
    else
    {
        SDL_SetColorKey(LoadSurface,SDL_TRUE, SDL_MapRGB(LoadSurface->format, 244,244,244));


        texture = SDL_CreateTextureFromSurface(renderer, LoadSurface);
        SDL_RenderCopy(renderer, texture, NULL, rect);
        SDL_FreeSurface(LoadSurface);
        SDL_DestroyTexture(texture);
    }

}

void Set_Rect(SDL_Rect &rect, int x, int y, int h, int w)
{
    rect.x = x;
    rect.y = y;
    rect.h = h;
    rect.w = w;
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

bool Is_Alive(int &health, SDL_Rect object1, SDL_Rect object2)
{
    if (Check_Collision(object1,object2) == true) health--;
    if (health == 0) return false;
    return true;
}

void Quit(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

