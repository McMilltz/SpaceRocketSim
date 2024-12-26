#include "Game.h"

Game::Game() 
  : score(SCORE_SIZE, SCORE_SIZE)
  , mainWindow(WINDOW_WIDTH, WINDOW_HEIGHT)
  , nerdWindow(NERD_WINDOW_WIDTH, NERD_WINDOW_HEIGHT)
{
  mainWindow.setup_SDL();
  nerdWindow.setup_SDL();

  isRunning = setup();
}
Game::~Game(){
  cleanUp();
}

void Game::run(){
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

void Game::processInput(){
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

          case SDLK_a:
            cockpit->setEnginePressed(0, true);
            break;
          case SDLK_b:
            cockpit->setEnginePressed(1, true);
            break;
          case SDLK_l:
            cockpit->setEnginePressed(2, true);
            break;
          case SDLK_RETURN:
            cockpit->setEnginePressed(3, true);
            break;

          case SDLK_SPACE:
            rocket.toggleAutopilot();
            break;

        }
        break;

      case SDL_KEYUP:
        switch (event.key.keysym.sym) {

          case SDLK_a:
            cockpit->setEnginePressed(0, false);
            break;
          case SDLK_b:
            cockpit->setEnginePressed(1, false);
            break;
          case SDLK_l:
            cockpit->setEnginePressed(2, false);
            break;
          case SDLK_RETURN:
            cockpit->setEnginePressed(3, false);

        }
        break;


    }
  }


}

bool Game::checkForScoreCollision(){
  float rocketX;
  float rocketY;
  rocket.getCoordinates(rocketX, rocketY);
  
  float dX = score.getX() - rocketX;
  float dY = score.getY() - rocketY;

  return ((sqrt(pow(dX, 2) + pow(dY, 2))) < 
      ((rocket.getWidth() + rocket.getHeight()) / 4.0f + 
       (score.getHitbox().w + score.getHitbox().h) / 4.0f));
}

void Game::updateSimulation(){
  rocket.update(deltaTime);
  if(checkForScoreCollision()){
    int x;
    int y;
    score.setToRandomLocation(x, y);
    rocket.setTargetPosition(x, y);
  }
}

void Game::render() {

  // Main Window
  SDL_SetRenderDrawColor(mainRenderer, MAIN_BACKGROUND_COLOR);
  SDL_RenderClear(mainRenderer);

  score.draw(mainRenderer);
  rocket.draw(mainRenderer);

  Gizmos::drawAll(mainRenderer);

  SDL_RenderPresent(mainRenderer);

  // Nerd Window
  SDL_SetRenderDrawColor(nerdRenderer, NERD_BACKGROUND_COLOR);
  SDL_RenderClear(nerdRenderer);

  Physics* ph = rocket.getPhysics();
  nerdWindow.drawEnginePower(nerdRenderer,
                             ph->getEngines());

  nerdWindow.drawVelocityInformation(nerdRenderer,
                                     &textRenderer, 
                                     ph->getSpeed(),
                                     ph->getAngle(ph->getVelocity()));

  nerdWindow.drawDistanceInformation(&textRenderer,
                                     ph->getX(), 
                                     ph->getY(), 
                                     score.getX(), 
                                     score.getY());
  nerdWindow.drawDistanceMap(WINDOW_WIDTH / 2, 
                             WINDOW_HEIGHT / 2,
                             ph->getX(),
                             ph->getY());

  SDL_RenderPresent(nerdRenderer);

}

bool Game::setup() {

  lastUpdate = SDL_GetTicks();

  // Windows
  SDL_SetWindowPosition(mainWindow.getWindow(), MAIN_WINDOW_POSITION);
  SDL_SetWindowPosition(nerdWindow.getWindow(), NERD_WINDOW_POSITION);
  nerdWindow.loadImages();

  // Cockpit
  cockpit = rocket.getCockpit();
  if (cockpit == nullptr) {
    std::cout << "Failed to get cockpit from rocket.\n";
  }

  // Score
  int x;
  int y;
  score.setToRandomLocation(x, y);
  rocket.setTargetPosition(x, y);

  // Renderer
  mainRenderer = mainWindow.getRenderer();
  if (mainRenderer == nullptr) {
    std::cout << "Failed to get mainRenderer from mainWindow.\n";
    return 1;
  }
  nerdRenderer = nerdWindow.getRenderer();
  if (nerdRenderer == nullptr) {
    std::cout << "Failed to get nerdRenderer from nerdWindow.\n";
    return 1;
  }

  // TextRenderer
  std::string path = "./sprites/FontBitmap.png";
  std::string layout[6] = {
                            "abcdefghijklmnop",
                            "qrstuvwxyz",
                            "ABCDEFGHIJKLMNOP",
                            "QRSTUVWXYZ",
                            "0123456789",
                            ".,()+-!: ="
                          };

  textRenderer.init(nerdRenderer, 
                    path,
                    layout,
                    6, 8, 8);
  
  // Rocket
  rocket.loadTexture(mainRenderer);

  return true;

}

void Game::cleanUp() {

  mainWindow.cleanUp();
  if (cockpit != nullptr) {
    cockpit = nullptr;
  }
  if (mainRenderer != nullptr) {
    mainRenderer = nullptr;
  }

  nerdWindow.cleanUp();
  Gizmos::clear();//delete all DrawRequests in heap
}



