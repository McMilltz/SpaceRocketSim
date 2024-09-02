#include <math.h>
#include "constants.h"
#include <iostream>

typedef struct Vector2f{
  float x;
  float y;
  float magnitude();
  void print();
  Vector2f operator-(Vector2f& _other);
  Vector2f operator*(float _f);
} Vector2f;

#define AMOUNT_OF_ENGINES 4
#define START_POSITION {.x = WINDOW_WIDTH / 2, \
                        .y = WINDOW_HEIGHT / 2}

class Physics{
  public:
    const float LEVER[AMOUNT_OF_ENGINES] = {40, 1.5, -1.5, -40};
    const float THRUST[AMOUNT_OF_ENGINES] = {5, 25, 25, 5};

public:
        Physics();
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
