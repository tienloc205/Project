#ifndef OBJET_H_INCLUDED
#define OBJET_H_INCLUDED

#include "function.h"

class Object
{
protected:
    int x,y;
    SDL_Rect rect;
public:
    void setX(int _x) {x = _x;}
    void setY(int _y) {y = _y;}
    int getX() {return x;}
    int getY() {return y;}
    void setRect(SDL_Rect rect_) {rect = rect_;}
    SDL_Rect getRect() {return rect;}
};

class Bullet : public Object
{
private:
    int dx ;
    int dy ;
    bool active ;
public:
    Bullet();
    void Move(const int& x_des, const int& y_des);
    void setActive(bool active_) {active = active_;}
    bool getActive() {return active;}
    void Enemy_Move(const int& x_des, const int& y_des);
};

class MainObject : public Object
{
private:
    int dx = 0;
    int dy = 0;
    vector <Bullet*> ammo_list;
public:
    void HandleKey(SDL_Event event);
    void Move();
    void SetAmmoList(vector <Bullet*> ammo_list_) {ammo_list = ammo_list_;}
    vector <Bullet*> getAmmoList() {return ammo_list;}
};

#endif // OBJET_H_INCLUDED
