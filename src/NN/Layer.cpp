#include "Layer.h"
#include <cmath>

Layer::Layer() 
  : size(0), nextSize(0), weightCount(0), isLast(true), nextLayer(nullptr), t_outputValueArray(nullptr)  {}

void Layer::init(int _size, Layer* _nextLayer, int _nextSize){
  size = _size;
  nextSize = _nextSize;
  if(nextSize <= 0 || size <= 0){
    return;
  }

  weightCount = nextSize * size;
  t_outputValueArray = new double[nextSize];
  weightMatrix = new double[weightCount];

  if(_nextLayer != nullptr){
    isLast = false;
    nextLayer = _nextLayer;
  }

  for (int it=0; it < weightCount; it++) {
    weightMatrix[it] = 1.0;
  }

  // std::cout << "Initialized Layer.\n"; 
}

Layer::~Layer(){
  delete[] t_outputValueArray;
  delete[] weightMatrix;
  // std::cout << "~Layer()\n";
}

void Layer::setRandomWeights(float _maxWeight){
  _maxWeight *= 2.f;
  for (int it=0; it < weightCount; it++) {
    weightMatrix[it] = ((rand() / (float)RAND_MAX) - 0.5f) * _maxWeight; 
  }
}

void Layer::copyWeights(Layer* _source){
  if(_source->weightCount != this->weightCount){
    std::cout << "[Layer::copyWeights] Error: different number of weights.\n";
    return;
  }
  for (int it=0; it < weightCount; it++) {
    weightMatrix[it] = _source->weightMatrix[it];
  }
}

double* Layer::calculateNN_recursive(double* _input){
  for (int outIt=0; outIt < nextSize; outIt++) {
    t_outputValueArray[outIt] = 0.0;
    for (int wIt=0; wIt < size; wIt++) {
      t_outputValueArray[outIt] += weightMatrix[(outIt * size) + wIt] * _input[wIt];
    }
    NL_FUNC(t_outputValueArray[outIt]);
  }

  if(isLast){
    return t_outputValueArray;
  }else{
    //print t_outputValueArray
    return nextLayer->calculateNN_recursive(t_outputValueArray);
  }

}

void Layer::NL_FUNC(double& _in_value){
  _in_value = std::atan(_in_value) / M_PI;
}

double* Layer::getWeight(int _idx){
  if(_idx < weightCount){
    return &weightMatrix[_idx];
  }else{
    std::cout << "Error in Layer::getWeight. Weight idx not in range.\n";
    std::cout << "idx: " << _idx << "\t weightCount: " << weightCount << "\n";
    return nullptr;
  }
}

int Layer::getSize(){
  return size;
}
int Layer::getNextSize(){
  return nextSize;
}
int Layer::getWeightCount(){
  return weightCount;
}

