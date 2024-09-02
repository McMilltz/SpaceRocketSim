#include "Score.h"
#include "constants.h"
#include <SDL2/SDL_render.h>
#include <cstdlib>
#include <ctime>

Score::Score(int width, int height) {

  srand((unsigned) time(NULL));
  this->hitbox.w = width;
  this->hitbox.h = height;

}

/**
* Sets the position of the Score to a random location.
* the location is then passed to the parameters x, y by reference.
*/
void Score::setToRandomLocation(int& x, int& y) {

  this->x = rand() % (WINDOW_WIDTH - this->hitbox.w);
  this->y = rand() % (WINDOW_HEIGHT - this->hitbox.h);
  hitbox.x = this->x - hitbox.w / 2;
  hitbox.y = this->y - hitbox.h / 2;

  x = this->x;
  y = this->y;

}

void Score::draw(SDL_Renderer* renderer){

  SDL_SetRenderDrawColor(renderer, SCORE_COLOR);
  SDL_RenderFillRect(renderer, &(this->hitbox));

}

SDL_Rect Score::getHitbox() {
  return this->hitbox;
}
int Score::getX() {
  return this->x;
}
int Score::getY() {
  return this->y;
}
