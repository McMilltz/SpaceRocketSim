#include "Rocket.h"



Rocket::Rocket() {

}


Cockpit* Rocket::getCockpit() {
  return &this->cockpit;
}
