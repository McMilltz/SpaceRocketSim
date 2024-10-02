#include "NNPhysics.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <vector>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>

#define VARY_WEIGHT_COUNT 5
#define VARIANTS 11

class NNRocket{

  const float DH = 25.0f;
  const float WEIGHT_ORDER = 20.0f;
  const float STEP_SIZE = DH / SCORE_REWARD;
  
public:
        NNRocket();
  void  init();
  
  void prepareGo();
  void finishGo();

  void  setStarPositionVector(std::vector<Vector2f>* _track);
  void  update(float _dt);

  void printScoreResults();
  void safe(std::string& _filename);
  void loadFromFile(std::string& _filename);

  void draw(SDL_Renderer* _renderer);
  void loadTexture(SDL_Renderer* _renderer);

private:
  NNPhysics physics[VARIANTS];
  std::vector<Vector2f>*  starPositionVector;
  int       weightCount;
  int       modifyIndizes[VARY_WEIGHT_COUNT];

private:
  int width;
  int height;
  SDL_Rect geometry;
  SDL_Surface* spriteSheet;
  SDL_Texture* texture[SPRITE_SHEET_COUNT];
};
