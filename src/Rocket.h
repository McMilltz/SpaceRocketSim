#include "Cockpit.h"
#include "RocketPhysics.h"

#ifndef ROCKET_H
#define ROCKET_H


class Rocket {

private:
  Cockpit cockpit;
  Physics physics;
  int width;
  int height;


public:
  Rocket();

  void setEnginePressed(int index, bool value);
  void update(float deltaTime);
  void getCoordinates(float& x, float& y);
  Cockpit* getCockpit();
  int getWidth();
  int getHeight();


};

#endif // !ROCKET_H
