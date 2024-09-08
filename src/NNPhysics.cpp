#include "NNPhysics.h"

void NNPhysics::setStarPosition(float _x, float _y){
  starPosition.x = _x;
  starPosition.y = _y;
}

void NNPhysics::update(float _dt){

  Brain.inputData.posX = 100;
  Brain.inputData.posY = 100;
  Brain.inputData.velX = 1000;
  Brain.inputData.velY = 1000;
  Brain.inputData.starX = 500;
  Brain.inputData.starY = 500;
  Brain.inputData.rotAngle = -700;
  Brain.inputData.rotSpeed = 700;
  for (int it=0; it < AMOUNT_OF_ENGINES; it++) {
    Brain.inputData.thrust[it] = mEngines[it];
  }

  Brain.calculate();
  Brain.printOutput();


  Physics::update(_dt);
}

void NNPhysics::toggleAutopilot(){
  
}
