#include "Cockpit.h"
#include <cstdio>


void Cockpit::updateEngines(float delta_time) {

  for (int i = 0; i < AMOUNT_OF_ENGINES; i++) {
    if (this->input[i]) {
      this->engines[i] += delta_time * 1.0f / ENGINE_CHANGE_RATE;
    } else {
      this->engines[i] -= delta_time * 1.0f / ENGINE_CHANGE_RATE;
    }

    if (this->engines[i] > 1) {
      this->engines[i] = 1;
    }
    else if (this->engines[i] < 0) {
      this->engines[i] = 0;
    }
  }

  // WARNING: debugging engine power
  printf("engines: \n"
         "0: %f, 1: %f, 2: %f, 3: %f\n",
         this->engines[0],
         this->engines[1],
         this->engines[2],
         this->engines[3]);


}

float* Cockpit::getEngines() {

  return engines;

}
void Cockpit::setEnginePressed(int index, bool value) {
  
  this->input[index] = value;

}
