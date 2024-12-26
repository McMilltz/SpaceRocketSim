#include "LearningManager.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include "../Score.h"

LearningManager::LearningManager()
   : mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT) 
{

  srand((unsigned) time(NULL));

  const float start_x = (WINDOW_WIDTH/2.0f);
  const float start_y = (WINDOW_HEIGHT/2.0f);
  track.push_back({start_x, start_y - 150});
  track.push_back({start_x + 200, start_y + 100});
  track.push_back({start_x - 70, start_y - 100});

  mainWindow.setup_SDL();

  isRunning = setup();
}
LearningManager::~LearningManager(){
  cleanUp();
}
void LearningManager::init(){
  for (int it=0; it < ROCKET_COUNT; it++) {
    rocket[it].init();
    rocket[it].setStarPositionVector(&track);
  }
  // std::cout << "[LM] Rocket initialized.\n";
  // std::cout << "[LM] Star Position set. Finish init method.\n";
}
void LearningManager::init(int _rocketIdx){
  if(_rocketIdx >= ROCKET_COUNT || _rocketIdx < 0){
    std::cout << "[LM]init(int) _rocketIdx " << _rocketIdx << " not in range.\n";
    return;
  }
  rocket[_rocketIdx].init();
  rocket[_rocketIdx].setStarPositionVector(&track);
}

void LearningManager::startGo(){
  float time = 0.0f;
  for(int it=0; it < ROCKET_COUNT; it++){
    rocket[it].prepareGo();
  }
  // std::cout << "[LM] : go prepared.\n";
  while(time < timePerGo){
    for (int it=0; it < ROCKET_COUNT; it++) {
      rocket[it].update(dt);
    }
    
    time += dt;
    // std::cout << "Time: " << time << "\t";
  }
  for (int it=0; it < ROCKET_COUNT; it++) {
    rocket[it].finishGo();
  }
}
void LearningManager::run_and_show(){
  float time = 0.0f;
  for(int it=0; it < ROCKET_COUNT; it++){
    rocket[it].prepareGo();
  }
  isRunning = true;
  Score sc(SCORE_SIZE, SCORE_SIZE);
  // std::cout << "[LM] : go prepared.\n";
  std::cout << "[LM] run_and_show() begin.\n";
  lastUpdate = SDL_GetTicks();
  while(time < timePerGo && isRunning){

    int timeSinceLastUpdate = SDL_GetTicks() - lastUpdate;
    // std::cout << timeSinceLastUpdate << " of " << (1000*dt) << "\n";
    while(timeSinceLastUpdate >= 1000 * dt){
      //update
      for (int it=0; it < ROCKET_COUNT; it++) {
        rocket[it].update(dt);
      }
      // std::cout << "[LM] run_and_show rockets updated.\n";
      timeSinceLastUpdate -= 1000 * dt;
      time += dt;
      lastUpdate = SDL_GetTicks();
    }
    //render
    SDL_SetRenderDrawColor(mainRenderer, MAIN_BACKGROUND_COLOR);
    SDL_RenderClear(mainRenderer);
    // std::cout << "[LM]run_and_show() start rendering.\n";
    for (int it=0; it < ROCKET_COUNT; it++) {
      // std::cout << "[LM]run_and_show render rocket[" << it << "].\n";
     rocket[it].draw(mainRenderer);
    }
    //score
    SDL_RenderPresent(mainRenderer);
    // std::cout << "[LM]run_and_show render complete.\n";
  }
  // std::cout << "[LM]run_and_show end loop.\n";
  for (int it=0; it < ROCKET_COUNT; it++) {
    rocket[it].finishGo();
  }
}

void LearningManager::sortByScore(){
  int sortIdx[ROCKET_COUNT];
  float scores[ROCKET_COUNT];
  for(int it=0;it<ROCKET_COUNT;it++)
    scores[it] = rocket[it].getScoreResult();

  float minScore;
  int minIdx = 0;
  NNRocket tempNNR;

  for(int placement=0; placement<ROCKET_COUNT; placement++){
    minScore = 1000000.0f;
    minIdx = placement;
    for(int rIt=placement; rIt < ROCKET_COUNT; rIt++){
      if(scores[rIt]<minScore){
        minIdx = rIt;
        minScore = scores[rIt];
      }
    }
    sortIdx[placement] = minIdx;
    tempNNR.copyFrom(&rocket[placement]);
    rocket[placement].copyFrom(&rocket[minIdx]);
    rocket[minIdx].copyFrom(&tempNNR);
    std::cout << "placement " << placement << " is rocket " << minIdx << "\n";
  }
}

void LearningManager::safe(std::string& _filename, int _rocketIdx){
  if(_rocketIdx >= ROCKET_COUNT){
    std::cout << "Saving rocket " << _rocketIdx << " not possible. Only " << ROCKET_COUNT << " rockets exist.\n";
    return;
  }

  rocket[_rocketIdx].safe(_filename);
}

void LearningManager::loadFromFile(std::string& _filename, int _rocketIdx){
  rocket[_rocketIdx].loadFromFile(_filename);
  rocket[_rocketIdx].setStarPositionVector(&track);
}

bool LearningManager::setup(){
  lastUpdate = SDL_GetTicks();

  SDL_SetWindowPosition(mainWindow.getWindow(), MAIN_WINDOW_POSITION);

  mainRenderer = mainWindow.getRenderer();
  if (mainRenderer == nullptr) {
    std::cout << "Failed to get mainRenderer from mainWindow.\n";
    return 1;
  }
  for (int it=0; it < ROCKET_COUNT; it++) {
   rocket[it].loadTexture(mainRenderer);
  }

  return true;
}

void LearningManager::cleanUp(){
  mainWindow.cleanUp();
  if(mainRenderer != nullptr)
    mainRenderer = nullptr;
  Gizmos::clear();
}
