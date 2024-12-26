#ifndef NEURALNET_H
#define NEURALNET_H

#include "Layer.h"
#include "NNData.hpp"
#include <fstream>
#include <sstream>

#define OUTPUT_COUNT 4
#define NUM_LAYER 4

class NeuralNet{
public:
  const int DEF_LAYER_SIZE_ARRAY[NUM_LAYER] = {INPUT_COUNT,8,6,2};
public:
  NeuralNet();
  NeuralNet(int _layerCount,const int* _layerSizeArray);
  ~NeuralNet();
  void setRandomWeights(const float _MAX_WEIGHT);
  void calculate();
  float* getResult();
  void printOutput();
  int getNumberOfWeights();
  double* getWeight(int _globalIdx);
  double* getWeight(int _layer, int _idx);
  void copyWeights(NeuralNet* _source);
  void safe(std::string& _filename);
  void loadFromFile(std::string& _filename);
   
public:
  InputData inputData;
  int layer_count;
  int* layerSizeArray;

private:
  Layer*  layerArray;
  float   output[OUTPUT_COUNT];
  double* layerOutputAddress;
  int totalWeightCount;
};

#endif //NEURALNET_H
