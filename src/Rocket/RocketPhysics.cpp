#include "RocketPhysics.h"

Physics::Physics() : mSpeed(0.0f), mRotSpeed(0.0f), mRotation(0.0f){
  mVelocity = {.x = 0.0f, .y=0.0f};
  mPosition = START_POSITION;
  for(int it = 0; it < AMOUNT_OF_ENGINES; it++){
    mEngines[it] = 0.0f;
}
/*  DrawLineRequest<float>* d = new DrawLineRequest<float>(&mPosition.x,&mPosition.y,&mVelocity.x,&mVelocity.y,DrawLineRequest<float>::Type::Direction);
  ((DrawLineRequest<float>*)d)->setColor(0, 255, 0, 255);
  Gizmos::addRequest("Velocity", d);*/
}
Physics::~Physics(){
//  Gizmos::remove("Velocity");
}

void Physics::resetToStart(){
  mSpeed = 0.0f;
  mRotSpeed = 0.0f;
  mRotation = 0.0f;
  mVelocity = {0.0f, 0.0f};
  mPosition = START_POSITION;
  for (int it=0.0; it < AMOUNT_OF_ENGINES; it++) {
    mEngines[it] = 0.0f;
  }
  // std::cout << "[RP] resetted to Start.\n";
}

void Physics::update(float _dt){
  float Momentum = 0.0f, Force = 0.0f;
  for(int it=0; it < AMOUNT_OF_ENGINES; it++){
    Momentum += LEVER[it] * THRUST[it] * mEngines[it];
    Force += THRUST[it] * mEngines[it];
  }
  Momentum /= J_zz;
  Force /= m;
  
  mRotSpeed += Momentum * _dt;
  mRotation += mRotSpeed * _dt;

  mVelocity.x += Force * std::sin(mRotation) * _dt;
  mVelocity.y -= Force * std::cos(mRotation) * _dt;
  mPosition.x += mVelocity.x * _dt;
  mPosition.y += mVelocity.y * _dt;

  mSpeed = sqrt(pow(mVelocity.x, 2) + pow(mVelocity.y, 2));
}

void Physics::setThruster(float* _t){
   for(unsigned int it=0;it < AMOUNT_OF_ENGINES; it++){
    mEngines[it] = _t[it];
  } 
}

int Physics::getEngineBitMask(){
  int result = 0;
  for(int it=0; it < AMOUNT_OF_ENGINES; it++){
    if(mEngines[it] > 0.0f){
      result += pow(2, it);
    }
  }
  
  return result;

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
float Physics::getRotation_deg(){
  return mRotation * 180.0f / M_PI;
}
float Physics::getRotation(){
  return mRotation;
}
float Physics::getSpeed() {
  return mSpeed;
}
float Physics::getAngle(Vector2f _v){
  float result = acos(-_v.y/(_v.magnitude() + 0.00001f));
  if(_v.x < 0.0f){
    result *= -1.0f;
  }
  return result;
}
float* Physics::getEngines(){
  return &mEngines[0];
}
