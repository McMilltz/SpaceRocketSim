#include "Window.h"
#include "TextRenderer.h"
#include "constants.h"

#ifndef NERDWINDOW_H
#define NERDWINDOW_H

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
  


class NerdWindow : public Window {

  private:

  public:
  NerdWindow(int width, int height);
  
  void drawEnginePower(SDL_Renderer* renderer, 
                       float* enginePower);
  void drawVelocityInformation(SDL_Renderer* renderer,
                               TextRenderer* tr,
                               int vel,
                               float velDir);
  void drawDistanceMap();
    

};

#endif // !NERDWINDOW_H
