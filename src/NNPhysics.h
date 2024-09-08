#include "RocketPhysics.h"
#include "NeuralNet.h"

class NNPhysics : public Physics {

public:
  void update(float _dt) override;
  void setStarPosition(float _x, float _y);
  void toggleAutopilot();

private:
  NeuralNet Brain;
  Vector2f starPosition;

};
