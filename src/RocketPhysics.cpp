#include "RocketPhysics.h"

Physics::Physics() : mSpeed(0.0f), mRotSpeed(0.0f), mRotation(0.0f){
  mVelocity = {.x = 0.0f, .y=0.0f};
  mPosition = START_POSITION;
  for(int it = 0; it < AMOUNT_OF_ENGINES; it++)
    mEngines[it] = 0.0f;

}

void Physics::update(float _dt){
  float Momentum = 0.0f, Force = 0.0f;
  for(int it=0; it < AMOUNT_OF_ENGINES; it++){
    Momentum += thrustData.LEVER[it] * thrustData.THRUST[it] * mEngines[it];
    Force += thrustData.THRUST[it] * mEngines[it];
  }
  Momentum /= J_zz;
  Force /= m;
  
  mRotSpeed += Momentum * _dt;
  mRotation += mRotSpeed * _dt;

  mVelocity.x += Force * std::sin(mRotation) * _dt;
  mVelocity.y -= Force * std::cos(mRotation) * _dt;
  mPosition.x += mVelocity.x * _dt;
  mPosition.y += mVelocity.y * _dt;

}

void Physics::setThruster(float* _t){
   for(unsigned int it=0;it < AMOUNT_OF_ENGINES; it++){
    mEngines[it] = _t[it];
  } 
}

 
float Physics::getRotSpeed(){
  return mRotSpeed;
}

Vector2f Physics::getVelocity(){
  return mVelocity;
}

float Physics::getX() {
  return mPosition.x;
}
float Physics::getY() {
  return mPosition.y;
}
