#include "Window.h"
#include "constants.h"
#include "Rocket.h"
#include "Cockpit.h"
#include "Score.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <cmath>
#include <cstdlib>
#include <iostream>

Rocket rocket;
Cockpit* cockpit;
Score score(50, 50);
Window w(WINDOW_WIDTH, WINDOW_HEIGHT);
SDL_Renderer* renderer;

bool isRunning;
int lastUpdate;
float deltaTime;

void processInput() {
  
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      
      case SDL_QUIT:
        isRunning = false;
      break;

      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {

          case SDLK_ESCAPE:
            isRunning = false;
          break;
          
          case SDLK_z:
            cockpit->setEnginePressed(0, true);
          break;
          case SDLK_b:
            cockpit->setEnginePressed(1, true);
          break;
          case SDLK_SLASH:
            cockpit->setEnginePressed(2, true);
          break;
          case SDLK_RETURN:
            cockpit->setEnginePressed(3, true);

        }
      break;

      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          
          case SDLK_z:
            cockpit->setEnginePressed(0, false);
          break;
          case SDLK_b:
            cockpit->setEnginePressed(1, false);
          break;
          case SDLK_SLASH:
            cockpit->setEnginePressed(2, false);
          break;
          case SDLK_RETURN:
            cockpit->setEnginePressed(3, false);

        }
      break;


    }
  }

}

bool checkForScoreCollision() {

  float rocketX;
  float rocketY;
  rocket.getCoordinates(rocketX, rocketY);
  
  float dX = score.getHitbox().x + score.getHitbox().w - 
    (rocketX + rocket.getWidth());
  float dY = score.getHitbox().y + score.getHitbox().h - 
    (rocketY + rocket.getHeight());

  return ((sqrt(pow(dX, 2) + pow(dY, 2))) < 
      ((rocket.getWidth() + rocket.getHeight()) / 4.0f + 
       (score.getHitbox().w + score.getHitbox().h) / 4.0f));

}

void updateSimulation() {

  rocket.update(deltaTime);
  if (checkForScoreCollision()) {
    score.setToRandomLocation();
    //TODO: increase player score
  }

}

void render() {

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  score.draw(renderer);

  SDL_RenderPresent(renderer);

}

void gameLoop() {

  while (isRunning) {

    int timeToWait = IMAGE_DURATION - (SDL_GetTicks() - lastUpdate);
    if (timeToWait > 0)
      SDL_Delay(timeToWait);
    deltaTime = (SDL_GetTicks() - lastUpdate) / 1000.0f;
    lastUpdate = SDL_GetTicks();

    processInput();
    updateSimulation();
    render();

  }

}

bool setup() {

  lastUpdate = SDL_GetTicks();
  score.setToRandomLocation();
  renderer = w.getRenderer();
  return true;

}

int main(void) {

  w.setup_SDL();

  isRunning = setup();
  gameLoop();

  return EXIT_SUCCESS;

}
