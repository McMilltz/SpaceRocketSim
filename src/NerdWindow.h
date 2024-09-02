#include "Window.h"
#include "TextRenderer.h"
#include "constants.h"
#include <SDL2/SDL_surface.h>

#ifndef NERDWINDOW_H
#define NERDWINDOW_H

#define FONT_SIZE 16
#define TEXT_COLOR 255, 0, 0, 255
#define GRAPH_CENTER_DOT_SIZE 10

#define ENGINE_POWER_START_X 50
#define ENGINE_POWER_START_Y 50
#define ENGINE_POWER_WIDTH 80
#define ENGINE_POWER_HEIGHT 150

#define BORDER_COLOR 40, 40, 40, 255
#define ENGINE_FILL_COLOR 255, 0, 50, 255

#define SPEED_TEXT_START_X 50
#define SPEED_TEXT_START_Y (ENGINE_POWER_START_Y + ENGINE_POWER_HEIGHT + 80)
#define SPEED_GRAPH_START_X (SPEED_TEXT_START_X + 220)
#define SPEED_GRAPH_START_Y (SPEED_TEXT_START_Y + 8)
#define SPEED_GRAPH_POINTER_SIZE 50

#define DISTANCE_TEXT_START_X 50
#define DISTANCE_TEXT_START_Y (SPEED_TEXT_START_Y + 80)

#define DISTANCE_MAP_START_X 50
#define DISTANCE_MAP_START_Y (DISTANCE_TEXT_START_Y + 50)
#define DISTANCE_MAP_SIZE 400
#define DISTANCE_MAP_NUMBER_OF_AREAS 4
#define DISTANCE_MAP_THRESHOLD_1 1000
#define DISTANCE_MAP_THRESHOLD_2 2500
#define DISTANCE_MAP_THRESHOLD_3 5000
#define DISTANCE_MAP_POINTER_SIZE 200

class NerdWindow : public Window {

  private:
  SDL_Surface* macroMapSurfaces[4];
  SDL_Texture* macroMapTextures[4];

  public:
  NerdWindow(int width, int height);
  void loadImages();
  
  void drawEnginePower(SDL_Renderer* renderer, 
                       float* enginePower);
  void drawVelocityInformation(SDL_Renderer* renderer,
                               TextRenderer* tr,
                               int vel,
                               float velDir);
  void drawDistanceInformation(TextRenderer* tr,
                               int x1, 
                               int y1,
                               int x2,
                               int y2);
  void drawDistanceMap(int zeroX,
                       int zeroY,
                       float x,
                       float y);
    

};

#endif // !NERDWINDOW_H
