#include "Rocket.h"



Rocket::Rocket() {

  this->width = 40;
  this->height = 40;

}

void Rocket::update(float deltaTime) {

  //TODO: update rocket.

}

void Rocket::getCoordinates(float& x, float& y) {

  x = this->physics.getX();
  y = this->physics.getY();
  
}

Cockpit* Rocket::getCockpit() {
  return &this->cockpit;
}
int Rocket::getWidth() {
  return this->width;
}
int Rocket::getHeight() {
  return this->height;
}
