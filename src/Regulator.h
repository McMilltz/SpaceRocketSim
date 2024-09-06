#include "RocketPhysics.h"

class Regulator : public Physics{
  
  public:
        Regulator();
        ~Regulator();
  void update(float _dt) override;
  void setStarPosition(float _x, float _y);
  void toggleAutopilot();
  
private:
  Vector2f mStarPosition;
  Vector2f starDist;

  Vector2f optVelocity;
  Vector2f optAcceleration;
  float ang_acc;
  float phi_0;
  float d_phi;

  float d_phi_crit;
  float d_phi_1;
  float d_phi_2;
  float delta;

  bool active;

  const float ALPHA = THRUST[0] * LEVER[0] / J_zz;
  const float ACC = 2.0f * THRUST[1] / m;
  public:
private:
  void calculateTranslation();
  void calculateTargetAngle();
  bool calculateOvershootAngle();
  void regulateEngines();
};
