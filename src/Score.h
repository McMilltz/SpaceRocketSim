#ifndef SCORE_H
#define SCORE_H

#include <SDL2/SDL_rect.h>
class Score {

private:
  SDL_Rect hitbox;
  
public:
  Score(int width, int height);
  void setToRandomLocation();

  SDL_Rect getHitbox();
  
};

#endif // !SCORE_H
