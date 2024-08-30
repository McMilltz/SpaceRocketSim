#include "Cockpit.h"
#include "RocketPhysics.h"
#include <iostream>
#include <SDL2/SDL_render.h>

#ifndef ROCKET_H
#define ROCKET_H


class Rocket {

private:
  Cockpit cockpit;
  Physics physics;
  int width;
  int height;


public:
  Rocket();

  void setEnginePressed(int index, bool value);
  void update(float deltaTime);
  void getCoordinates(float& x, float& y);
  void draw(SDL_Renderer* renderer);

  Cockpit* getCockpit();
  int getWidth();
  int getHeight();


};

#endif // !ROCKET_H
