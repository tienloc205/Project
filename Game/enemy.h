#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "function.h"
#include "object.h"

class Enemy : public Object
{
private:
    int dx = 0 ;
    int dy = 0;
    vector <Bullet*> enemy_bullet_list;
public:
    ~Enemy();
    void Set_Enemy_Bullet(vector<Bullet*> enemy_bullet_list_) {enemy_bullet_list = enemy_bullet_list_;}
    vector<Bullet*> Get_Enemy_Bullet() {return enemy_bullet_list;}
    void Init_Bullet(Bullet* enemy_bullet);
    void Enemy_Bullet_Move(const int& x_des, const int& y_des);
    void Move();
};
#endif // ENEMY_H_INCLUDED
