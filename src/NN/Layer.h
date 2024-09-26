#include <iostream>

class Layer{
public:
  Layer();
  ~Layer();

  void init(int _size, Layer* _nextLayer, int _nextSize);
  int getSize();
  double* calculateNN_recursive(double* _input);
  double* getWeight(int _idx);
  
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
