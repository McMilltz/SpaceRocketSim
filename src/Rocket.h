#include "Cockpit.h"
#include "RocketPhysics.h"
#include <iostream>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

#ifndef ROCKET_H
#define ROCKET_H


class Rocket {

private:
  Cockpit cockpit;
  Physics physics;
  int width;
  int height;
  SDL_Rect geometry;

  SDL_Surface* spriteSheet;
  SDL_Texture* texture[SPRITE_SHEET_COUNT];


public:
  Rocket();

  void setEnginePressed(int index, bool value);
  void update(float deltaTime);
  void getCoordinates(float& x, float& y);
  void draw(SDL_Renderer* renderer);

  Cockpit* getCockpit();
  int getWidth();
  int getHeight();

  void loadTexture(SDL_Renderer* renderer);


};

#endif // !ROCKET_H
