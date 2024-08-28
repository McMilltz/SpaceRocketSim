#include "Window.h"
#include "constants.h"
#include "Cockpit.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <cstdlib>
#include <iostream>

Cockpit cockpit;

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
            cockpit.setEnginePressed(0, true);
          break;
          case SDLK_b:
            cockpit.setEnginePressed(1, true);
          break;
          case SDLK_SLASH:
            cockpit.setEnginePressed(2, true);
          break;
          case SDLK_RETURN:
            cockpit.setEnginePressed(3, true);

        }
      break;

      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          
          case SDLK_z:
            cockpit.setEnginePressed(0, false);
          break;
          case SDLK_b:
            cockpit.setEnginePressed(1, false);
          break;
          case SDLK_SLASH:
            cockpit.setEnginePressed(2, false);
          break;
          case SDLK_RETURN:
            cockpit.setEnginePressed(3, false);

        }
      break;


    }
  }

}

void updateSimulation() {

  cockpit.updateEngines(deltaTime);

}

void render() {

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
  return true;

}

int main(void) {

  Window w(800, 600);
  w.setup_SDL();

  isRunning = setup();
  gameLoop();

  return EXIT_SUCCESS;

}
