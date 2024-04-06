#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "function.h"
#include "object.h"

class Enemy : public Object
{
private:
    vector <Bullet*> enemy_ammo_list;
    int dx = 0 ;
    int dy = 0;
    bool is_move;
public:
    Enemy();
    void Move();
    void Set_Enemy_Ammo_List(vector <Bullet*> enemy_ammo_list_) {enemy_ammo_list = enemy_ammo_list_;}
    vector <Bullet*> Get_Enemy_Ammo_List() {return enemy_ammo_list;}

};

#endif // ENEMY_H_INCLUDED
