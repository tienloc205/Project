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
    }

}

void Set_Rect(SDL_Rect &rect, int x, int y, int h, int w)
{
    rect.x = x;
    rect.y = y;
    rect.h = h;
    rect.w = w;
}

