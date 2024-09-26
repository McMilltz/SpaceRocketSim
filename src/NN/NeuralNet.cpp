#include "NeuralNet.h"

NeuralNet::NeuralNet() : inputData() {
  //setup layers
  layerArray = new Layer[layer_count];
  for (int it=0; it < layer_count-1; it++) {
    layerArray[it].init(layerSizeArray[it],&layerArray[it+1],layerSizeArray[it + 1]);
  }
  layerArray[layer_count-1].init(layerSizeArray[layer_count-1],nullptr,OUTPUT_COUNT);

  //calcualte number of Weights.
  // totalWeightCount = layerSizeArray[0] * INPUT_COUNT;
  for (int it=0; it < layer_count-1; it++) {
    totalWeightCount += layerSizeArray[it]*layerSizeArray[it+1];
  }
  totalWeightCount += layerSizeArray[layer_count-1] * OUTPUT_COUNT;
}
NeuralNet::~NeuralNet(){
  delete[] layerArray;
}

void NeuralNet::calculate(){
  layerOutputAddress = layerArray[0].calculateNN_recursive(inputData.getInputs());
  for (int it=0; it < OUTPUT_COUNT; it++) {
    output[it] = layerOutputAddress[it];
  }
}

float* NeuralNet::getResult(){
  return &output[0];
}

void NeuralNet::printOutput(){
  for (int it=0; it < OUTPUT_COUNT-1; it++) {
    std::cout << "NN output[" << it << "] : " << output[it] << "\n";
  }std
  std::cout << "NN output[" << (OUTPUT_COUNT-1) << "] : " << output[OUTPUT_COUNT-1] << "\n";
}

double* NeuralNet::getWeight(int _globalIdx){
  for (int it=0; it < layer_count-1; it ++) {
    int numberOfWeights = layerSizeArray[it] * layerSizeArray[it + 1];
    if(numberOfWeights < _globalIdx+1){
      _globalIdx -= numberOfWeights;
    }else{
      return layerArray[it].getWeight(_globalIdx);
    }
  }
  return layerArray[layer_count-1].getWeight(_globalIdx);
}
