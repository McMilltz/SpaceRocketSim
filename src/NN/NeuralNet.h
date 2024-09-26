#include "Layer.h"
#include "NNData.hpp"

#define OUTPUT_COUNT 4
#define NUM_LAYER 4

class NeuralNet{

public:
  NeuralNet();
  ~NeuralNet();
  void calculate();
  float* getResult();
  void printOutput();
  int getNumberOfWeights();
  double* getWeight(int _globalIdx);
  double* getWeight(int _layer, int _idx);
 
public:
  InputData inputData;
  const int layer_count = NUM_LAYER;
  const int layerSizeArray[NUM_LAYER] = {INPUT_COUNT,8,10,8};

private:
  Layer*  layerArray;
  float   output[OUTPUT_COUNT];
  double* layerOutputAddress;
  int totalWeightCount;
};
