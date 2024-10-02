#ifndef LAYER_H
#define LAYER_H

#include <iostream>

class Layer{
public:
  Layer();
  ~Layer();

  void init(int _size, Layer* _nextLayer, int _nextSize);
  void setRandomWeights(float _maxWeight);
  int getSize();
  double* calculateNN_recursive(double* _input);
  double* getWeight(int _idx);
  void copyWeights(Layer* _source);
  int getNextSize();
  int getWeightCount();
  
private:
  int size;
  int nextSize;
  int weightCount;
  bool isLast;

  Layer* nextLayer;
  double* t_outputValueArray;
  double* weightMatrix;
private:
  void NL_FUNC(double& _in_value);
};

#endif //LAYER_H
