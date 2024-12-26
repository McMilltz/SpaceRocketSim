#ifndef ROCKETPHYSICS_H
#define ROCKETPHYSICS_H

#include "../constants.h"
#include "../Vector2.hpp"
#include "../UI/Gizmos.h"
#include <cmath>
#include <SDL2/SDL.h>

#define AMOUNT_OF_ENGINES 4

class Physics{
  public:
    const float LEVER[AMOUNT_OF_ENGINES] = {40, 1.5, -1.5, -40};
    const float THRUST[AMOUNT_OF_ENGINES] = {5, 25, 25, 5};
    const float _1_CRIT_ACC = 1.0f / (THRUST[0]*2.0f);
    const float _1_CRIT_TORQUE = 1.0f / (THRUST[0] * LEVER[0]);
public:
        Physics();
      ~Physics();
  virtual void resetToStart();
  virtual void update(float _dt);
  void setThruster(float* _t);
  int getEngineBitMask();

  float getRotSpeed();
  Vector2f getVelocity();
  float getX();
  float getY();
  float getRotation_deg();
  float getRotation();
  float getSpeed();
  float getAngle(Vector2f _v);
  float* getEngines();


  public:
    const float J_zz = 300; //Inertia of rotation
    const float m = 3;     //mass
    
  protected:
    Vector2f  mVelocity;
    float     mSpeed;
    Vector2f  mPosition;
    float     mRotSpeed;
    float     mRotation;
    float     mEngines[AMOUNT_OF_ENGINES];

};

#endif
