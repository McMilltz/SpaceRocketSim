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
 

  float cos_t = std::cos(mRotation);
  float cos_tt = std::cos(mRotation + Momentum * _dt);
  float sin_t = std::sin(mRotation);
  float sin_tt = std::sin(mRotation + Momentum * _dt);
  
  mPosition.x += (mSpeed / mRotSpeed) * (cos_t-cos_tt) - (Force * _dt * cos_tt / mRotSpeed) + (Force / (mRotSpeed * mRotSpeed)) * (sin_tt - sin_t);
  mPosition.y += (mSpeed / mRotSpeed) * (sin_t - sin_tt) - ((Force * _dt / mRotSpeed) * sin_tt) + (Force / (mRotSpeed * mRotSpeed)) * (cos_t - cos_tt);

  mRotation += (mRotSpeed + _dt * Momentum/2.0f) * _dt; 
  mRotSpeed += Momentum * _dt;

  mSpeed += Force * _dt;
  mVelocity.x = mSpeed * sin_tt;
  mVelocity.y = -mSpeed * cos_tt;
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
