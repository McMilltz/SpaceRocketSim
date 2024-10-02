#include "NNPhysics.h"
#include "NeuralNet.h"
#include <vector>

NNPhysics::NNPhysics() : Brain(){
  
}
void NNPhysics::init(const float _MAX_WEIGHT){
  Brain.setRandomWeights(_MAX_WEIGHT);
}

void NNPhysics::setStarPositionVector(std::vector<Vector2f>* _track){
  starPositionVector = _track;
  starPosition = (*starPositionVector)[0];
}

void NNPhysics::update(float _dt){
  Vector2f distance = starPosition - mPosition;

  Brain.inputData.dX = distance.x;
  Brain.inputData.dY = distance.y;
  Brain.inputData.velX = mVelocity.x * Physics::_1_CRIT_ACC;
  Brain.inputData.velY = mVelocity.y * Physics::_1_CRIT_ACC;
  Brain.inputData.speed = mVelocity.magnitude();
  Brain.inputData.relDist = distance.magnitude() / Brain.inputData.speed;
  Brain.inputData.d_phi = (distance.angle() - mRotation);
  Brain.inputData.rotSpeed = mRotSpeed * Physics::_1_CRIT_TORQUE;
  Brain.inputData.cos_phi = cos(Brain.inputData.d_phi);
  Brain.inputData.sin_phi = sin(Brain.inputData.d_phi);
  for (int it=0; it < AMOUNT_OF_ENGINES; it++) {
    Brain.inputData.thrust[it] = mEngines[it];
  }

  Brain.calculate();
  // Brain.printOutput();

  addThruster(Brain.getResult(), _dt);
  Physics::update(_dt);
  updateErrorFunction(_dt);
}

void NNPhysics::updateErrorFunction(float _dt){
  float dJ = 0.0f;
  for (int it=0; it < AMOUNT_OF_ENGINES; it++) {
    dJ += mEngines[it];
  }
  dJ *= J_ENGINE;
  dJ += (starPosition - mPosition).magnitude();  
  dJ += mRotSpeed * mRotSpeed * J_ROT_SPEED;

  J_err += dJ * _dt;
}
bool NNPhysics::collisionCheck(){
  float d = (starPosition - mPosition).magnitude();
  if(d < MAX_SCORE_DISTANCE){
    scoreIdx++;
    starPosition = (*starPositionVector)[scoreIdx%starPositionVector->size()];
    J_err -= SCORE_REWARD;
    return true;
  }  
  return false;
}

void NNPhysics::addThruster(float* _increment, float _dt){
  for (int it=0; it < AMOUNT_OF_ENGINES; it++) {
    mEngines[it] += _increment[it] * 1.0f / ENGINE_CHANGE_RATE * _dt;
    if(mEngines[it] < 0.0f ){
      mEngines[it] = 0.0f;
    }else if (mEngines[it] > 1.0f) {
      mEngines[it] = 1.0f;
    }
  }
}

void NNPhysics::toggleAutopilot(){
  
}

int NNPhysics::getWeightCount(){
  return Brain.getNumberOfWeights();
}

void NNPhysics::incrementWeight(int _globalIdx, float _increment){
  double* w = Brain.getWeight(_globalIdx);
  *w = *w + _increment;
}
void NNPhysics::setWeight(int _globalIdx, float _value){
  double* w = Brain.getWeight(_globalIdx);
  *w = _value;
}
double NNPhysics::getWeight(int _globalIdx){
  return *(Brain.getWeight(_globalIdx));
}


void NNPhysics::resetToStart(){
  // std::cout << "[NNP] begin resetToStart().\n";
  Physics::resetToStart();
  J_err = 0.0f;
  scoreIdx = 0;
  starPosition = (*starPositionVector)[0];
  // std::cout << "[NNP] end resetToStart().\n";
}

float NNPhysics::getJ_err(){
  return J_err;
}

void NNPhysics::copyWeights(NNPhysics* _source){
  Brain.copyWeights(&_source->Brain);
}

void NNPhysics::safe(std::string& _filename){
  Brain.safe(_filename);
}
void NNPhysics::loadFromFile(std::string& _filename){
  Brain.loadFromFile(_filename);
}

Vector2f* NNPhysics::getStarPosition(){
  return &starPosition;
}
