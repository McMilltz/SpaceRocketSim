#include "NeuralNet.h"

NeuralNet::NeuralNet() : inputData() {
  layerArray = new Layer[layer_count];
  for (int it=0; it < layer_count-1; it++) {
    layerArray[it].init(layerSizeArray[it],&layerArray[it+1],layerSizeArray[it + 1]);
  }
  layerArray[layer_count-1].init(layerSizeArray[layer_count-1],nullptr,OUTPUT_COUNT);
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

double* NeuralNet::getResult(){
  return &output[0];
}

void NeuralNet::printOutput(){
  for (int it=0; it < OUTPUT_COUNT-1; it++) {
    std::cout << "NN output[" << it << "] : " << output[it] << "\n";
  }
  std::cout << "NN output[" << (OUTPUT_COUNT-1) << "] : " << output[OUTPUT_COUNT-1] << "\n";
}
