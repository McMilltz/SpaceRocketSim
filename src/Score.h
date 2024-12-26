#ifndef SCORE_H
#define SCORE_H

#include "Vector2.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <iostream>
class Score {
public:
  static Score* instance;
  ~Score();
private:
  int x;
  int y;
  SDL_Rect hitbox;
  
public:
  Score(int width, int height);
  void setToRandomLocation(int& x, int& y);
  void setPosition(Vector2f* _pos);
  void draw(SDL_Renderer* renderer);

  SDL_Rect getHitbox();
  int getX();
  int getY();
  
};

#endif // !SCORE_H
