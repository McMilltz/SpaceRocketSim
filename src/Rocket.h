#include "Cockpit.h"

#ifndef ROCKET_H
#define ROCKET_H


class Rocket {

private:
  Cockpit cockpit;


public:
  Rocket();

  void setEnginePressed(int index, bool value);
  void update(float deltaTime);
  Cockpit* getCockpit();


};

#endif // !ROCKET_H
