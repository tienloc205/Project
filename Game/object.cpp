#include "object.h"
#include "function.h"

void MainObject::HandleKey(SDL_Event event)
{
  if (event.type == SDL_KEYDOWN)
  {
      switch (event.key.keysym.sym)
      {
      case SDLK_UP:
        dy-=17; break;
      case SDLK_DOWN:
        dy+=17; break;
      case SDLK_RIGHT:
        dx+=21;break;
      case SDLK_LEFT:
        dx-=21;break;
      default:
        break;
      }
  }
  else if (event.type == SDL_KEYUP)
  {
      switch (event.key.keysym.sym)
      {
      case SDLK_UP:
        dy=0; break;
      case SDLK_DOWN:
        dy=0; break;
      case SDLK_RIGHT:
        dx=0;break;
      case SDLK_LEFT:
        dx=0;break;
      default:
        break;
      }
  }
  else if (event.type == SDL_MOUSEBUTTONDOWN)
  {
          Bullet* Ammo = new Bullet;
          Ammo->setX(MainObject::getX()+23);
          Ammo->setY(MainObject::getY());

          Ammo->setActive(true);
          ammo_list.push_back(Ammo);
  }
  else
  {
      ;
  }
}
void MainObject::Move()
{
    x+=dx;
    if (x<0 || x+53>SCREEN_WIDTH)
    {
        x-=dx;
    }
    y+=dy;
    if (y<0 || y+67>SCREEN_HEIGHT)
    {
        y-=dy;
    }
}

Bullet::Bullet()
{
    x = 0;
    y = 0;
    dx = 0;
    dy = 0;
    active = false;
}

void Bullet::Move(const int& x_des, const int& y_des)
{
  if (active == true)
  {
    dy = 20;
    y -= dy;
    if (y < y_des)
    {
      active = false;
    }
  }
}

