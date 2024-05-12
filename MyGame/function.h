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
#include <string>
#include <SDL_messagebox.h>
#include <fstream>
#define start 0
#define play 1
#define exit 2
#define retry 3
#define pause 4
#define difficulty 5

using namespace std;

const int SCREEN_HEIGHT = 700;
const int SCREEN_WIDTH  = 400;
const string SCREEN_NAME = "Space Shooting";
const int SHOOTER_WIDTH = 53;
const int SHOOTER_HEIGHT = 70;
const int ENEMY_WIDTH = 76;
const int ENEMY_HEIGHT = 50;
const int BULLET_WIDTH = 5;
const int BULLET_HEIGTH = 20;
const int HEART_WIDTH = 25;
const int HEART_HEIGHT = 25;
extern int state;
extern int SHOOTER_HEALTH ;
extern int ENEMY_NUMS;


extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern Mix_Chunk* bullet_sound;
extern Mix_Music* background_sound;

void LoadImage(string path, SDL_Renderer* renderer, SDL_Rect* rect);
void LoadText(string text, TTF_Font* font, SDL_Rect* messageRect);
bool Check_Collision(SDL_Rect object1, SDL_Rect object2);
void Hp_Bar(string path);
void Quit();



#endif // FUNCTION_H_
