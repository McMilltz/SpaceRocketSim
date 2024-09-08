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
    weightMatrix[it] = 3.0;
  }

  std::cout << "Initialized Layer.\n"; 
}

Layer::~Layer(){
  delete[] t_outputValueArray;
  delete[] weightMatrix;
  std::cout << "~Layer()\n";
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


