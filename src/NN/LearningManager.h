#include "NeuralNet.h"
#include "NNRocket.h"
#include "../UI/Window.h"
#include <vector>

class LearningManager{

public:
      LearningManager();
      ~LearningManager();
  void init(); 
  void init(int _rocketIdx);
  void startGo();
  void run_and_show();
  void sortByScore();
  
  void safe(std::string& _filename, int _rocketIdx);
  void loadFromFile(std::string& _filename, int _rocketIdx);

private:
  NNRocket rocket[ROCKET_COUNT];
  bool isRunning;

  const float timePerGo = 20.0f;
  const float dt = 0.02f;
  std::vector<Vector2f> track;

  Window mainWindow;
  SDL_Renderer* mainRenderer = nullptr;
  int lastUpdate;
private:
  bool setup();
  void cleanUp();
};
