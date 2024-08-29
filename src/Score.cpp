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

void Score::setToRandomLocation() {

  this->hitbox.x = rand() % (WINDOW_WIDTH - this->hitbox.w);
  this->hitbox.y = rand() % (WINDOW_HEIGHT - this->hitbox.h);

}

void Score::draw(SDL_Renderer* renderer){

  SDL_SetRenderDrawColor(renderer, SCORE_COLOR);
  SDL_RenderFillRect(renderer, &this->hitbox);

}

SDL_Rect Score::getHitbox() {
  return this->hitbox;
}
