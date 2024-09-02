#include "RocketPhysics.h"
#include <cmath>
#include <SDL2/SDL.h>

float Vector2f::magnitude(){
  return sqrt(pow(x, 2) + pow(y, 2));
}
Vector2f Vector2f::operator-(Vector2f& _other){
  return {.x = x - _other.x, .y = y - _other.y};
}
Vector2f Vector2f::operator*(float _f){
  return {.x = _f * x, .y = _f * y};
}
void Vector2f::print(){
  std::cout << "x: " << (int)x << ", y: " << (int)y << "\n";
}

Physics::Physics() : mSpeed(0.0f), mRotSpeed(0.0f), mRotation(0.0f){
  mVelocity = {.x = 0.0f, .y=0.0f};
  mPosition = START_POSITION;
  for(int it = 0; it < AMOUNT_OF_ENGINES; it++)
    mEngines[it] = 0.0f;

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
