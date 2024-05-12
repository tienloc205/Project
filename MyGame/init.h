#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "function.h"
#include "object.h"

bool Init();
void Init_Enemy(Enemy* enemies);
void Set_Menu_End_Game(TextObject text, TTF_Font* font);
#endif // INIT_H_INCLUDED
