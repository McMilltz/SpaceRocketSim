#ifndef COCKPIT_H
#define COCKPIT_H

#include "constants.h"

class Cockpit {

private:
  float engines[AMOUNT_OF_ENGINES];
  bool input[AMOUNT_OF_ENGINES];

public:
  void updateEngines(float delta_time);

  float* getEngines();
  void setEnginePressed(int index, bool value);
  

};

#endif // !COCKPIT_H

