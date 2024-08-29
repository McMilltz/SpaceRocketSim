typedef struct Vector2f{
  float x;
  float y;
} Vector2f;

#define AMOUNT_OF_ENGINES 4

class Physics{
  // public:
  // typedef struct ThrustData {
  //   const float LEVER_O = 5;
  //   const float LEVER_I = 3;
  //   const float THRUST_I = 10;
  //   const float THRUST_O = 10;
  // } Data;

  public:
  void update(float _dt);
  void setThruster(float* _t);

  float getRotSpeed();
  Vector2f getVelocity();
  float getX();
  float getY();


  public:
    const float J_zz = 100; //Inertia of rotation
    const float m = 10;     //mass
    
  private:
    Vector2f  mVelocity;
    Vector2f  mPosition;
    float     mRotSpeed;
    float     mRotation;
    float     mEngines[AMOUNT_OF_ENGINES];

};
