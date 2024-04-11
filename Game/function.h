#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SCREEN_HEIGHT = 700;
const int SCREEN_WIDTH  = 400;
const string SCREEN_NAME = "Space Shooting";
const int ENEMY_NUMS = 8;
const int SHOOTER_WIDTH = 53;
const int SHOOTER_HEIGHT = 70;
const int ENEMY_WIDTH = 76;
const int ENEMY_HEIGHT = 50;
const int BULLET_WIDTH = 5;
const int BULLET_HEIGTH = 20;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

void LoadImage(string path, SDL_Renderer* renderer, SDL_Rect* rect);
void Set_Rect(SDL_Rect &rect, int x, int y, int h, int w);
void Quit(SDL_Window* window, SDL_Renderer* renderer);
bool Check_Collision(SDL_Rect object1, SDL_Rect object2);
bool Is_Alive(int &health, SDL_Rect object1, SDL_Rect object2);
#endif // FUNCTION_H_
