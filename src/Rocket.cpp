#include "Rocket.h"
#include <SDL2/SDL_render.h>



Rocket::Rocket() : physics() {

  this->width = ROCKET_WIDTH;
  this->height = ROCKET_HEIGHT;

}

void Rocket::update(float deltaTime) {

  cockpit.updateEngines(deltaTime);
  physics.setThruster(cockpit.getEngines());
  physics.update(deltaTime);

  // std::cout << "Rocket position: X: " << physics.getX() << 
  // ", Y: " << physics.getY() << "\n";

}

void Rocket::getCoordinates(float& x, float& y) {

  x = this->physics.getX();
  y = this->physics.getY();
  
}

void Rocket::draw(SDL_Renderer* renderer) {

  SDL_Rect r;
  r.x = this->physics.getX();
  r.y = this->physics.getY();
  r.w = this->width;
  r.h = this->height;
  
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderFillRect(renderer, &r);

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
