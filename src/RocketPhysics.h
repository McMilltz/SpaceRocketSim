#include <math.h>

typedef struct Vector2f{
  float x;
  float y;
} Vector2f;

#define AMOUNT_OF_ENGINES 4
#define START_POSITION {.x = 100, .y=100}

class Physics{
  public:
  typedef struct ThrustData {
    const float LEVER[AMOUNT_OF_ENGINES] = {5,3,-3,-5};
    const float THRUST[AMOUNT_OF_ENGINES] = {10,5,5,10};
  } Data;

  Data thrustData;

  public:
        Physics();
  void update(float _dt);
  void setThruster(float* _t);

  float getRotSpeed();
  Vector2f getVelocity();
  float getX();
  float getY();
  float getRotation_deg();
  float getRotation();


  public:
    const float J_zz = 100; //Inertia of rotation
    const float m = 10;     //mass
    
  private:
    Vector2f  mVelocity;
    float     mSpeed;
    Vector2f  mPosition;
    float     mRotSpeed;
    float     mRotation;
    float     mEngines[AMOUNT_OF_ENGINES];

};
