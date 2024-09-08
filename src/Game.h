#include "Window.h"
#include "NerdWindow.h"
#include "constants.h"
#include "Rocket.h"
#include "Cockpit.h"
#include "Score.h"
#include "TextRenderer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <cstdlib>
#include <iostream>


class Game{

public:
      Game();
      ~Game();
  void run();

private:
  void processInput();
  bool checkForScoreCollision();
  void updateSimulation();
  void render();
  bool setup();
  void cleanUp();
 

private:
  Rocket rocket;
  Cockpit* cockpit = nullptr;
  Score score;
  Window mainWindow;
  NerdWindow nerdWindow;
  SDL_Renderer* mainRenderer = nullptr;
  SDL_Renderer* nerdRenderer = nullptr;
  TextRenderer textRenderer;

  bool isRunning;
  int lastUpdate;
  float deltaTime;
};
