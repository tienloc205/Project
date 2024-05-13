#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "function.h"


struct Bullet;

class Object
{
protected:
    SDL_Rect rect;
    int dx = 0;
    int dy = 0;
    bool active;
    std::vector <Bullet*> bullet_list;
public:
    void Set_Rect(SDL_Rect rect_) {rect = rect_;}
    SDL_Rect Get_Rect() {return rect;}

    void Set_Active(bool active_) {active = active_;}
    bool Get_Active() {return active;}

    void HandleKey(SDL_Event event, Mix_Chunk* bul_sound);
    void Move(const int& x_des, const int y_des);

    void Set_Bullet_List(std::vector <Bullet*> bullet_list_) {bullet_list = bullet_list_;}
    vector <Bullet*> Get_Bullet_List() {return bullet_list;}

};

struct Bullet : public Object
{
    void Move(const int& x_des, const int& y_des, int y);
    void Enemy_Move(const int& x_des, const int& y_des, int y);
};

struct Enemy : public Object
{
    ~Enemy();
    void Move(const int& x_des, const int& y_des, int y);
    void Init_Bullet(Bullet* enemy_bullet);
    void Make_Bullet_Move(const int& x_des, const int& y_des, SDL_Rect player);
    void Reset();
};

struct TextObject : public Object
{
    string Inf;
    int Score;
    int High_Score = 0;

    int Check_Digit(string text);
    string Change_Score(string text);
};
#endif // OBJECT_H_INCLUDED
