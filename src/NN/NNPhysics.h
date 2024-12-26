#include "../Rocket/RocketPhysics.h"
#include "NeuralNet.h"
#include <vector>

class NNPhysics : public Physics {
  
  // const int layerSizes[NUM_LAYER] = {INPUT_COUNT,8,6,2};
public:
        NNPhysics();
  void init(const float _MAX_WEIGHT);
  void resetToStart() override;
  void update(float _dt) override;
  void setStarPositionVector(std::vector<Vector2f>* _track);
  void toggleAutopilot();
  int   getWeightCount();
  void incrementWeight(int _globalIdx, float _increment);
  void setWeight(int _globalIdx, float _value);
  double getWeight(int _globalIdx);
  float getJ_err();
  void copyWeights(NNPhysics* _source);
  bool  collisionCheck();
  Vector2f* getStarPosition();

  void safe(std::string& _filename);
  void loadFromFile(std::string& _filename);
private:
  void  updateErrorFunction(float _dt);
  void addThruster(float* _increment, float _dt);
private:
  NeuralNet Brain;
  std::vector<Vector2f>* starPositionVector;
  Vector2f starPosition;
  float J_err;
  int scoreIdx;
};
