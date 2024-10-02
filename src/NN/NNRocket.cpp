#include "NNRocket.h"
#include "../Score.h"
#include <cstdlib>
#include <vector>

NNRocket::NNRocket() : physics()
{
  weightCount = physics[0].getWeightCount();
  // std::cout << "[NNR]constructor. weightCount: " << weightCount << "\n";
  this->width = ROCKET_WIDTH;
  this->height = ROCKET_HEIGHT;
  geometry.w = ROCKET_WIDTH;
  geometry.h = ROCKET_HEIGHT;
  geometry.x = 0.0f;
  geometry.y = 0.0f;
}

void NNRocket::init(){
  physics[0].init(WEIGHT_ORDER);
  // std::cout << "[NNR] init physics[0].\n";
  for (int it=1; it < VARIANTS; it++) {
    // std::cout << "[NNR] init rocket[" << it << "] : \n";
     physics[it].copyWeights(&physics[0]); 
  }
  // std::cout << "[NNR] finish init().\n";
}

void NNRocket::loadFromFile(std::string& _filename){
  physics[0].loadFromFile(_filename);
  for(int it=0; it < VARIANTS; it++){
    physics[it].copyWeights(&physics[0]);
  }
  weightCount = physics[0].getWeightCount();
}

void NNRocket::prepareGo(){
  //pick random weights
  // std::cout << "[NNR]prepareGo() begin.\n";
  bool doAgain;
  for (int it = 0; it < VARY_WEIGHT_COUNT; it++) {
    modifyIndizes[it] = -1;
    do{
      doAgain = false;
      modifyIndizes[it] = rand() % weightCount;
      // std::cout << "rand IDX[" << it << "] : " << modifyIndizes[it] << "\n";
      for (int j=0; j < it; j++){
        if(modifyIndizes[j] == modifyIndizes[it]){
          doAgain = true; 
        }
      }
    }while(doAgain);
  }
  // std::cout << "[NNR] weightCount: " << weightCount << "\n";
  //change Weights to get partial derivative later
  for (int it=1; it <= VARY_WEIGHT_COUNT; it++) {
    physics[it].incrementWeight(modifyIndizes[it-1], DH);
    physics[it+VARY_WEIGHT_COUNT].incrementWeight(modifyIndizes[it-1], -DH);
  } 
  for (int it=0; it < VARIANTS; it++) {
    physics[it].setStarPositionVector(starPositionVector);
    physics[it].resetToStart();
  }
}
void NNRocket::finishGo(){
  float J0 = physics[0].getJ_err();
  // std::cout << "[NNR] begin finishGo().\n";
  for (int it=1; it <= VARY_WEIGHT_COUNT; it++) {
    float dJ1 = physics[it].getJ_err() - J0;
    float dJ2_ = physics[it+VARY_WEIGHT_COUNT].getJ_err() - J0;
    float dJ = dJ1 - dJ2_;
    if(dJ1 < 0 || dJ2_ < 0)
      physics[0].incrementWeight(modifyIndizes[it-1], -dJ * STEP_SIZE);
    float newWeight = physics[0].getWeight(modifyIndizes[it-1]);
    if(abs(dJ) > 10){
    // std::cout << "wIdx: " << modifyIndizes[it-1] << "\t dJ: " << dJ << "\t";
    // std::cout << "dJ1: " << dJ1 << "\t dJ2_: " << dJ2_ << " \t dW: " << (-dJ*STEP_SIZE/2.0f) << "\n";
    }
    // std::cout << "wIdx: " << modifyIndizes[it-1] << "\t";
    // std::cout << "dW: " << (-dJ * STEP_SIZE) << " to " << newWeight << ".\n";
    for (int j=1; j < VARIANTS; j++) {
      physics[j].setWeight(modifyIndizes[it-1], newWeight);
    }
  }
  // std::cout << "[NNR] quit finishGo().\n";
}

void NNRocket::setStarPositionVector(std::vector<Vector2f>* _track){
  starPositionVector = _track;
}

void NNRocket::update(float _dt){
  for (int it=0; it < VARIANTS; it++) {
    physics[it].update(_dt);
    physics[it].collisionCheck();
  }
  geometry.x = physics[0].getX() - width/2.0f;
  geometry.y = physics[0].getY() - height/2.0f;
  // std::cout << "J[0]: " << physics[0].getJ_err() << ".\n";
}

void NNRocket::printScoreResults(){
  // std::cout << "\n ------------- \n Score Results: \n\n";
  // for (int it=0; it < VARIANTS; it++){
    // std::cout << "J[" << it << "] : " << physics[it].getJ_err() << ".\n";
  // }
  // std::cout << "\n ------------\n";
  //
  //
  std::cout << "J[0] : " << physics[0].getJ_err() << ".\n";
}

void NNRocket::safe(std::string& _filename){
  physics[0].safe(_filename);
}

void NNRocket::draw(SDL_Renderer* _renderer){
  // std::cout << "[NNR] draw begin.\n";
  int spriteIdx = physics[0].getEngineBitMask();
  // std::cout << "[NNR]draw : bitMask received.\n";
  SDL_RenderCopyEx(_renderer, texture[spriteIdx], NULL, &geometry, physics[0].getRotation_deg(), NULL, SDL_FLIP_HORIZONTAL);
  // std::cout << "[NNR]draw : rocket drawn.\n";
  //draw current target
  Vector2f* target = physics[0].getStarPosition();
  // std::cout << "[NNR]draw : target Position received.\n";
  Score::instance->setPosition(target);
  Score::instance->draw(_renderer);
  // std::cout << "[NNR]draw end. &NNR: " << this << "\n";
}
void NNRocket::loadTexture(SDL_Renderer* _renderer){
  std::string file = SPRITE_DIR"R";
  std::string completedFile = file;
  for(int it = 0; it < SPRITE_SHEET_COUNT; it++){
    completedFile = file + std::to_string(it) + ".png";
    
    spriteSheet = IMG_Load(completedFile.c_str());
    texture[it] = SDL_CreateTextureFromSurface(_renderer, 
                                               spriteSheet);
  }
}
