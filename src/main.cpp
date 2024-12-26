// #include "Window.h"
// #include "NerdWindow.h"
// #include "constants.h"
// #include "Rocket.h"
// #include "Cockpit.h"
// #include "Score.h"
// #include "TextRenderer.h"
//
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_events.h>
// #include <SDL2/SDL_keycode.h>
// #include <SDL2/SDL_rect.h>
// #include <SDL2/SDL_render.h>
// #include <SDL2/SDL_timer.h>
// #include <SDL2/SDL_video.h>
// #include <cmath>
// #include <cstdlib>
// #include <iostream>
#include "Game.h"
#include "NN/LearningManager.h"
#include "Rocket/RocketPhysics.h"

int main(void) {
  //see previous main method at the end of the file
  {
   // Game game;
    // game.run();
    LearningManager LM;
    std::string file = "RocketBrain.csv";
    std::string file2 = "RocketBrain2.csv";
    LM.init();
    LM.loadFromFile(file, 0);
    LM.loadFromFile(file2, 1);
    std::cout << "loading complete.\n";
    LM.run_and_show();
    for (int it=0; it < 5; it++) {
      for (int jl=0; jl < 40; jl++) {
        LM.startGo();
      }
      // LM.run_and_show();
      LM.sortByScore();
      for(int s=3; s < ROCKET_COUNT; s++)
          LM.init(s);
    }
    LM.run_and_show();
    LM.sortByScore();

    LM.safe(file, 0);
    LM.safe(file2, 1);
    // LM.loadFromFile(file, 0);
  }
  return EXIT_SUCCESS;
}

// Rocket rocket;
// Cockpit* cockpit = nullptr;
// Score score(50, 50);
// Window mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
// NerdWindow nerdWindow(NERD_WINDOW_WIDTH, NERD_WINDOW_HEIGHT);
// SDL_Renderer* mainRenderer = nullptr;
// SDL_Renderer* nerdRenderer = nullptr;
// TextRenderer textRenderer;
//
// bool isRunning;
// int lastUpdate;
// float deltaTime;
//
// void processInput() {
//
//   SDL_Event event;
//
//   while (SDL_PollEvent(&event)) {
//     switch (event.type) {
//
//       case SDL_QUIT:
//         isRunning = false;
//       break;
//
//       case SDL_KEYDOWN:
//         switch (event.key.keysym.sym) {
//
//           case SDLK_ESCAPE:
//             isRunning = false;
//           break;
//
//           case SDLK_a:
//             cockpit->setEnginePressed(0, true);
//           break;
//           case SDLK_b:
//             cockpit->setEnginePressed(1, true);
//           break;
//           case SDLK_l:
//             cockpit->setEnginePressed(2, true);
//           break;
//           case SDLK_RETURN:
//             cockpit->setEnginePressed(3, true);
//           break;
//
//           case SDLK_SPACE:
//             rocket.toggleAutopilot();
//           break;
//
//         }
//       break;
//
//       case SDL_KEYUP:
//         switch (event.key.keysym.sym) {
//
//           case SDLK_a:
//             cockpit->setEnginePressed(0, false);
//           break;
//           case SDLK_b:
//             cockpit->setEnginePressed(1, false);
//           break;
//           case SDLK_l:
//             cockpit->setEnginePressed(2, false);
//           break;
//           case SDLK_RETURN:
//             cockpit->setEnginePressed(3, false);
//
//         }
//       break;
//
//
//     }
//   }
//
// }
//
// bool checkForScoreCollision() {
//
//   float rocketX;
//   float rocketY;
//   rocket.getCoordinates(rocketX, rocketY);
//
//   float dX = score.getX() - rocketX;
//   float dY = score.getY() - rocketY;
//
//   return ((sqrt(pow(dX, 2) + pow(dY, 2))) < 
//       ((rocket.getWidth() + rocket.getHeight()) / 4.0f + 
//        (score.getHitbox().w + score.getHitbox().h) / 4.0f));
//
// }
//
// void updateSimulation() {
//
//   rocket.update(deltaTime);
//   if (checkForScoreCollision()) {
//     int x;
//     int y;
//     score.setToRandomLocation(x, y);
//     rocket.setTargetPosition(x, y);
//   }
//
// }
//
// void render() {
//
//   // Main Window
//   SDL_SetRenderDrawColor(mainRenderer, MAIN_BACKGROUND_COLOR);
//   SDL_RenderClear(mainRenderer);
//
//   score.draw(mainRenderer);
//   rocket.draw(mainRenderer);
//
//   Gizmos::drawAll(mainRenderer);
//
//   SDL_RenderPresent(mainRenderer);
//
//   // Nerd Window
//   SDL_SetRenderDrawColor(nerdRenderer, NERD_BACKGROUND_COLOR);
//   SDL_RenderClear(nerdRenderer);
//
//   Physics* ph = rocket.getPhysics();
//   nerdWindow.drawEnginePower(nerdRenderer,
//                              ph->getEngines());
//
//   nerdWindow.drawVelocityInformation(nerdRenderer,
//                                      &textRenderer, 
//                                      ph->getSpeed(),
//                                      ph->getAngle(ph->getVelocity()));
//
//   nerdWindow.drawDistanceInformation(&textRenderer,
//                                      ph->getX(), 
//                                      ph->getY(), 
//                                      score.getX(), 
//                                      score.getY());
//   nerdWindow.drawDistanceMap(WINDOW_WIDTH / 2, 
//                              WINDOW_HEIGHT / 2,
//                              ph->getX(),
//                              ph->getY());
//
//   SDL_RenderPresent(nerdRenderer);
//
// }
//
// void gameLoop() {
//
//   while (isRunning) {
//
//     int timeToWait = IMAGE_DURATION - (SDL_GetTicks() - lastUpdate);
//     if (timeToWait > 0)
//       SDL_Delay(timeToWait);
//     deltaTime = (SDL_GetTicks() - lastUpdate) / 1000.0f;
//     lastUpdate = SDL_GetTicks();
//
//     processInput();
//     updateSimulation();
//     render();
//
//   }
//
// }
//
// bool setup() {
//
//   lastUpdate = SDL_GetTicks();
//
//   // Windows
//   SDL_SetWindowPosition(mainWindow.getWindow(), MAIN_WINDOW_POSITION);
//   SDL_SetWindowPosition(nerdWindow.getWindow(), NERD_WINDOW_POSITION);
//   nerdWindow.loadImages();
//
//   // Cockpit
//   cockpit = rocket.getCockpit();
//   if (cockpit == nullptr) {
//     std::cout << "Failed to get cockpit from rocket.\n";
//   }
//
//   // Score
//   int x;
//   int y;
//   score.setToRandomLocation(x, y);
//   rocket.setTargetPosition(x, y);
//
//   // Renderer
//   mainRenderer = mainWindow.getRenderer();
//   if (mainRenderer == nullptr) {
//     std::cout << "Failed to get mainRenderer from mainWindow.\n";
//     return 1;
//   }
//   nerdRenderer = nerdWindow.getRenderer();
//   if (nerdRenderer == nullptr) {
//     std::cout << "Failed to get nerdRenderer from nerdWindow.\n";
//     return 1;
//   }
//
//   // TextRenderer
//   std::string path = "./sprites/FontBitmap.png";
//   std::string layout[6] = {
//                             "abcdefghijklmnop",
//                             "qrstuvwxyz",
//                             "ABCDEFGHIJKLMNOP",
//                             "QRSTUVWXYZ",
//                             "0123456789",
//                             ".,()+-!: ="
//                           };
//
//   textRenderer.init(nerdRenderer, 
//                     path,
//                     layout,
//                     6, 8, 8);
//
//   // Rocket
//   rocket.loadTexture(mainRenderer);
//
//   return true;
//
// }
//
// void cleanUp() {
//
//   mainWindow.cleanUp();
//   if (cockpit != nullptr) {
//     cockpit = nullptr;
//   }
//   if (mainRenderer != nullptr) {
//     mainRenderer = nullptr;
//   }
//
//   nerdWindow.cleanUp();
//   Gizmos::clear();//delete all DrawRequests in heap
// }

// int main(void) {
//
//   // mainWindow.setup_SDL();
//   // nerdWindow.setup_SDL();
//   //
//   // isRunning = setup();
//   // gameLoop();
//   //
//   // cleanUp();
//   {
//     Game game;
//     game.run();
//   }
//   return EXIT_SUCCESS;
// }
