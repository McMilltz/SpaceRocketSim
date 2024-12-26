#include "NeuralNet.h"
#include <fstream>
#include <sstream>
#include <string>
NeuralNet::NeuralNet(int _layerCount,const int* _layerSizeArray)
  : inputData()
{
  layer_count = _layerCount;
  layerSizeArray = new int[_layerCount];
  for(int it=0; it < _layerCount; it++){
    layerSizeArray[it] = _layerSizeArray[it];
  }
  if(layerSizeArray[0] != INPUT_COUNT){
    std::cout << "[NN]::NN number of inputs dont match.\n";
  }
  layerArray = new Layer[layer_count];
  for(int it=0; it<layer_count-1; it++){
    layerArray[it].init(layerSizeArray[it], &layerArray[it+1], layerSizeArray[it+1]);
  }
  layerArray[layer_count-1].init(layerSizeArray[layer_count-1], nullptr, OUTPUT_COUNT);

  //calcualte number of Weights.
  // totalWeightCount = layerSizeArray[0] * INPUT_COUNT;
  totalWeightCount = 0;
  for (int it=0; it < layer_count; it++) {
    totalWeightCount += layerArray[it].getWeightCount();
  }
}
NeuralNet::NeuralNet() : inputData() {
  layer_count = NUM_LAYER;
  layerSizeArray = new int[layer_count];
  for(int it=0; it < layer_count; it++){
    layerSizeArray[it] = DEF_LAYER_SIZE_ARRAY[it];
  }
  //setup layers
  layerArray = new Layer[layer_count];
  for (int it=0; it < layer_count-1; it++) {
    layerArray[it].init(layerSizeArray[it],&layerArray[it+1],layerSizeArray[it + 1]);
  }
  layerArray[layer_count-1].init(layerSizeArray[layer_count-1],nullptr,OUTPUT_COUNT);

  //calcualte number of Weights.
  // totalWeightCount = layerSizeArray[0] * INPUT_COUNT;
  totalWeightCount = 0;
  for (int it=0; it < layer_count; it++) {
    totalWeightCount += layerArray[it].getWeightCount();
  }
  // std::cout << "[NN] totalWeightCount: " << totalWeightCount << "\n";
}
NeuralNet::~NeuralNet(){
  delete[] layerArray;
  delete[] layerSizeArray;
}

void NeuralNet::setRandomWeights(const float _MAX_WEIGHT){
  for (int it=0; it < layer_count; it++) {
    layerArray[it].setRandomWeights(_MAX_WEIGHT);
  }
}

void NeuralNet::copyWeights(NeuralNet* _source){
  bool resize = false;
  if(_source->layer_count != layer_count){
    std::cout << "[NeuralNet::copyWeights] Error: Different number of layers.\n";
    resize = true;
  }else{
    for (int it=0; it < layer_count; it++) {
      if(layerSizeArray[it] != _source->layerSizeArray[it]){
          resize = true;
      }
    }
  }

  if(resize){
    delete[] layerSizeArray;
    delete[] layerArray;

    layer_count = _source->layer_count;
    layerSizeArray = new int[layer_count];
    for (int it=0; it < layer_count; it++) {
       layerSizeArray[it] = _source->layerSizeArray[it];
    }
    layerArray = new Layer[layer_count];
    for(int it=0; it < layer_count-1; it++){
        layerArray[it].init(layerSizeArray[it], &layerArray[it+1], layerSizeArray[it+1]); 
    }
    layerArray[layer_count-1].init(layerSizeArray[layer_count-1],nullptr,OUTPUT_COUNT);
    totalWeightCount = _source->totalWeightCount;
  }



  for (int it=0; it < layer_count; it++) {
    layerArray[it].copyWeights(&(_source->layerArray[it]));
  }
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
  }
  std::cout << "NN output[" << (OUTPUT_COUNT-1) << "] : " << output[OUTPUT_COUNT-1] << "\n";
}

double* NeuralNet::getWeight(int _globalIdx){
  // std::cout << "getWeight(" << _globalIdx << ") : \n";
  for (int it=0; it < layer_count-1; it ++) {
    int numberOfWeights = layerSizeArray[it] * layerSizeArray[it + 1];
    if(numberOfWeights < _globalIdx+1){
      _globalIdx -= numberOfWeights;
    }else{
      // std::cout << "layer " << it << " at idx " << _globalIdx << "\n";
      return layerArray[it].getWeight(_globalIdx);
    }
  }
  // std::cout << "last layer: " << (layer_count-1) << " at idx " << _globalIdx << "\n";
  return layerArray[layer_count-1].getWeight(_globalIdx);
}

int NeuralNet::getNumberOfWeights(){
  return totalWeightCount;
}

void NeuralNet::safe(std::string& _filename){
  std::ofstream outputFile(_filename);
  outputFile << std::to_string(layer_count) << ",";
  for (int it=0; it < layer_count; it++) {
    outputFile << std::to_string(layerSizeArray[it]) << ",";
  }
  outputFile << std::to_string(OUTPUT_COUNT) << ",";
  outputFile << "\n";
  for (int l=0; l<layer_count; l++) {
    for (int nw=0; nw<layerArray[l].getWeightCount(); nw++) {
        outputFile << std::to_string(*layerArray[l].getWeight(nw)) << ",";
    }
    outputFile << "\n";
  }

  outputFile.close();
}

void NeuralNet::loadFromFile(std::string& _filename){
  std::ifstream inFile(_filename);

  std::string currentLine;
  std::string cell;

  if(inFile.eof()){
    std::cout << "[NN] loadFromFile error: empty file.\n";
  }
  delete[] layerArray;
  delete[] layerSizeArray;
  //read dimensions = layerSizes
  // std::getline(inFile,currentLine);
  int l_it = -1;
  int lines = -1;
  
  {//read first line
    std::getline(inFile, currentLine);
    std::istringstream lineStream(currentLine);
    while(std::getline(lineStream,cell,',')){
      if(l_it <= -1){
        layer_count = std::stoi(cell);
        layerSizeArray = new int[layer_count];
        l_it = 0;
        std::cout << "layer_count: " << layer_count << "\n";
      }else if(l_it < layer_count){
        layerSizeArray[l_it] = std::stoi(cell);
        std::cout << "layerSize[" << l_it << "] : " << layerSizeArray[l_it] << "\n";
        l_it++;
      }else{
        //OUTPUT_COUNT
        std::cout << "OUTPUT_COUNT: " << cell << "\n";
      }
    }
    lines = 0;
  }
  //setup layers.
  layerArray = new Layer[layer_count];
  for(int it=0; it<layer_count-1; it++){
    layerArray[it].init(layerSizeArray[it], &layerArray[it+1], layerSizeArray[it+1]);
  }
  layerArray[layer_count-1].init(layerSizeArray[layer_count-1], nullptr, OUTPUT_COUNT);

  //calcualte number of Weights.
  totalWeightCount = 0;
  for (int it=0; it < layer_count; it++) {
    totalWeightCount += layerArray[it].getWeightCount();
  }

  //Read weights
  while(std::getline(inFile, currentLine)){
    if(lines >= layer_count){
      std::cout << "[NN] loadFromFile: more lines than layers.\n";
      break;
    }
    std::istringstream lineStream(currentLine);
    int wIdx = 0;
    while(std::getline(lineStream,cell,',')){
      if(wIdx >= layerArray[lines].getWeightCount()){
        std::cout << "wIdx to big: " << wIdx << " out of " << layerSizeArray[lines] << " in layer " << lines << ".\n";
        break;
      }
      double* w_ptr = layerArray[lines].getWeight(wIdx);
      *w_ptr = std::stod(cell);
      // std::cout << "l[" << lines << "] w[" << wIdx << "] : " << *w_ptr << "\n";
      wIdx++;
    }
    lines++;
  }
 
  inFile.close();
}
