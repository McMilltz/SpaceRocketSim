#include "Layer.h"
#include "NNData.hpp"
#include <iostream>

#define OUTPUT_COUNT 4
#define NUM_LAYER 4

class NeuralNet{

public:
  NeuralNet();
  ~NeuralNet();
  void calculate();
  double* getResult();
  void printOutput();
 
public:
  InputData inputData;
  const int layer_count = NUM_LAYER;
  const int layerSizeArray[NUM_LAYER] = {8,8,10,8};

private:
  Layer* layerArray;
  double output[OUTPUT_COUNT];
  double* layerOutputAddress;
};
