#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>

using namespace std;

const int SCREEN_HEIGHT = 700;
const int SCREEN_WIDTH  = 400;
const string SCREEN_NAME = "Space Shooting";

extern SDL_Window* window;
extern SDL_Renderer* renderer;

void LoadImage(string path, SDL_Renderer* renderer, SDL_Rect* rect);
void Set_Rect(SDL_Rect &rect, int x, int y, int h, int w);

#endif // FUNCTION_H_
