#include "NerdWindow.h"
#include "TextRenderer.h"
#include <SDL2/SDL_render.h>
#include <cmath>
#include <string>


NerdWindow::NerdWindow(int width, int height)
  : Window(width, height) {


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
                 {255, 255, 255, 255}, 16, 16);

  SDL_SetRenderDrawColor(renderer, TEXT_COLOR);
  SDL_Rect centerPoint = {
    .x = SPEED_GRAPH_START_X - GRAPH_CENTER_DOT_SIZE / 2,
    .y = SPEED_GRAPH_START_Y - GRAPH_CENTER_DOT_SIZE / 2,
    .w = GRAPH_CENTER_DOT_SIZE,
    .h = GRAPH_CENTER_DOT_SIZE
  };
  SDL_RenderFillRect(renderer, &centerPoint);

  std::cout << "Angle: " << angle << ".\n";

  int xDir = SPEED_GRAPH_START_X + SPEED_GRAPH_POINTER_SIZE * sin(angle);
  int yDir = SPEED_GRAPH_START_Y - SPEED_GRAPH_POINTER_SIZE * cos(angle);

  std::cout << "xDir: " << xDir << ", yDir: " << yDir << "\n";

  SDL_RenderDrawLine(renderer, 
                     SPEED_GRAPH_START_X, 
                     SPEED_GRAPH_START_Y, 
                     xDir, 
                     yDir);

}
