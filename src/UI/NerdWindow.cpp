#include "NerdWindow.h"
#include "TextRenderer.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cmath>
#include <cstddef>
#include <string>


NerdWindow::NerdWindow(int width, int height)
  : Window(width, height) {

}

void NerdWindow::loadImages() {

  std::string path = SPRITE_DIR"MacroPosition";
  for (int i = 0; i < DISTANCE_MAP_NUMBER_OF_AREAS; i++) {
    std::string pathToImage = path + std::to_string(i) + ".png";
    this->macroMapSurfaces[i] = IMG_Load(pathToImage.c_str());
    this->macroMapTextures[i] = SDL_CreateTextureFromSurface(
      this->renderer, 
      this->macroMapSurfaces[i]);
  }

}

void NerdWindow::drawEnginePower(SDL_Renderer* renderer, 
                                 float* enginePower) {

  // Drawing borders
  SDL_SetRenderDrawColor(renderer, BORDER_COLOR);
  SDL_Rect r;
  for (int i = 0; i < AMOUNT_OF_ENGINES; i++) {
    r.x = ENGINE_POWER_START_X + i * 100;
    r.y = ENGINE_POWER_START_Y;
    r.w = ENGINE_POWER_WIDTH;
    r.h = ENGINE_POWER_HEIGHT;
    SDL_RenderDrawRect(renderer, &r);
  }
  
  // Drawing power
  SDL_SetRenderDrawColor(renderer, ENGINE_FILL_COLOR);
  for (int i = 0; i < AMOUNT_OF_ENGINES; i++) {
    r.x = ENGINE_POWER_START_X + i * 100;
    r.y = ENGINE_POWER_START_Y + ENGINE_POWER_HEIGHT;
    r.w = ENGINE_POWER_WIDTH;
    r.h = - ENGINE_POWER_HEIGHT * enginePower[i];
    SDL_RenderFillRect(renderer, &r);
  }

}

void NerdWindow::drawVelocityInformation(SDL_Renderer* renderer,
                                         TextRenderer* tr,
                                         int vel,
                                         float angle) {

  std::string speedText = "Speed: " + std::to_string(vel);
  tr->renderText(this->renderer, 
                 speedText, 
                 SPEED_TEXT_START_X, 
                 SPEED_TEXT_START_Y, 
                 {255, 255, 255, 255}, 
                 FONT_SIZE, 
                 FONT_SIZE);

  SDL_SetRenderDrawColor(renderer, TEXT_COLOR);
  SDL_Rect centerPoint = {
    .x = SPEED_GRAPH_START_X - GRAPH_CENTER_DOT_SIZE / 2,
    .y = SPEED_GRAPH_START_Y - GRAPH_CENTER_DOT_SIZE / 2,
    .w = GRAPH_CENTER_DOT_SIZE,
    .h = GRAPH_CENTER_DOT_SIZE
  };
  SDL_RenderFillRect(renderer, &centerPoint);

  int xDir = SPEED_GRAPH_START_X + SPEED_GRAPH_POINTER_SIZE * sin(angle);
  int yDir = SPEED_GRAPH_START_Y - SPEED_GRAPH_POINTER_SIZE * cos(angle);

  SDL_RenderDrawLine(renderer, 
                     SPEED_GRAPH_START_X, 
                     SPEED_GRAPH_START_Y, 
                     xDir, 
                     yDir);

}

void NerdWindow::drawDistanceInformation(TextRenderer* tr,
                                         int x1,
                                         int y1,
                                         int x2,
                                         int y2) {

  int d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
  std::string distanceText = "Distance: " + std::to_string(d);
  tr->renderText(this->renderer, 
                 distanceText, 
                 DISTANCE_TEXT_START_X, 
                 DISTANCE_TEXT_START_Y, 
                 {255, 255, 255, 255}, 
                 FONT_SIZE,
                 FONT_SIZE);

}

void NerdWindow::drawDistanceMap(int zeroX,
                                 int zeroY,
                                 float x,
                                 float y) {

  SDL_Rect renderTarget = {
    .x = DISTANCE_MAP_START_X,
    .y = DISTANCE_MAP_START_Y,
    .w = DISTANCE_MAP_SIZE,
    .h = DISTANCE_MAP_SIZE
  };
  SDL_Texture* currentMap = nullptr;

  int distance = sqrt(pow(x - zeroX, 2) + pow(y - zeroY, 2));
  if (distance < DISTANCE_MAP_THRESHOLD_1) {
    currentMap = this->macroMapTextures[0];
  } else if (distance < DISTANCE_MAP_THRESHOLD_2) {
    currentMap = this->macroMapTextures[1];
  } else if (distance < DISTANCE_MAP_THRESHOLD_3){
    currentMap = this->macroMapTextures[2];
  } else {
    currentMap = this->macroMapTextures[3];
  }

  SDL_RenderCopy(this->renderer, 
                 currentMap, 
                 NULL, 
                 &renderTarget);


  SDL_SetRenderDrawColor(this->renderer, 
                         255, 0, 0, 255);
  SDL_Rect r = {
    .x = DISTANCE_MAP_START_X + DISTANCE_MAP_SIZE / 2 -
         GRAPH_CENTER_DOT_SIZE / 2,
    .y = DISTANCE_MAP_START_Y + DISTANCE_MAP_SIZE / 2 -
         GRAPH_CENTER_DOT_SIZE / 2,
    .w = GRAPH_CENTER_DOT_SIZE,
    .h = GRAPH_CENTER_DOT_SIZE
  };
  SDL_RenderFillRect(this->renderer, 
                     &r);

  float dX = x - zeroX;
  float dY = y - zeroY;
  float hyp = sqrt(pow(dX, 2) + pow(dY, 2)) + 1;

  float dirX = r.x + GRAPH_CENTER_DOT_SIZE / 2 + ((dX / hyp) * 
    DISTANCE_MAP_POINTER_SIZE);
  float dirY = r.y + GRAPH_CENTER_DOT_SIZE / 2 + ((dY / hyp) * 
    DISTANCE_MAP_POINTER_SIZE);

  SDL_RenderDrawLine(this->renderer, 
                     r.x + GRAPH_CENTER_DOT_SIZE / 2,
                     r.y + GRAPH_CENTER_DOT_SIZE / 2,
                     dirX,
                     dirY);

}
