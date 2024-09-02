#include "Rocket.h"
#include "Cockpit.h"
#include <SDL2/SDL_render.h>
#include <cmath>
#include <string>



Rocket::Rocket() : physics() {

  this->width = ROCKET_WIDTH;
  this->height = ROCKET_HEIGHT;
  geometry.w = ROCKET_WIDTH;
  geometry.h = ROCKET_HEIGHT;
  geometry.x = 0.0f;
  geometry.y = 0.0f;
  compass.w = COMPASS_WIDTH;
  compass.h = COMPASS_HEIGHT;
  compass.x = 20;
  compass.y = 20;
}

void Rocket::setTargetPosition(int x, int y) {
  physics.setStarPosition(x, y);
}
void Rocket::toggleAutopilot(){
  physics.toggleAutopilot();
}

void Rocket::loadTexture(SDL_Renderer* renderer){
  std::string file = SPRITE_DIR"R";
  std::string completedFile = file;
  for(int it = 0; it < SPRITE_SHEET_COUNT; it++){
    completedFile = file + std::to_string(it) + ".png";
    
    spriteSheet = IMG_Load(completedFile.c_str());
    texture[it] = SDL_CreateTextureFromSurface(renderer, 
                                               spriteSheet);
  }
}


void Rocket::update(float deltaTime) {

  cockpit.updateEngines(deltaTime);
  physics.setThruster(cockpit.getEngines());
  if(true){
    physics.update(deltaTime);
  }else{
    physics.Physics::update(deltaTime);
  }
  // physics.update(deltaTime);
  geometry.x = physics.getX() - width/2.0f;
  geometry.y = physics.getY() - height/2.0f;

  // std::cout << "Rocket position: X: " << physics.getX() << 
  // ", Y: " << physics.getY() << "\n";

}

void Rocket::getCoordinates(float& x, float& y) {

  x = this->physics.getX();
  y = this->physics.getY();
  
}

void Rocket::draw(SDL_Renderer* renderer) {

  int spriteIndex = cockpit.getEngineBitMask();
  SDL_RenderCopyEx(renderer, texture[spriteIndex], NULL, 
                   &geometry, physics.getRotation_deg(), 
                   NULL, SDL_FLIP_HORIZONTAL);

  SDL_RenderCopyEx(renderer, texture[spriteIndex], NULL, 
                   &compass, physics.getRotation_deg(), 
                   NULL, SDL_FLIP_HORIZONTAL);

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderDrawLine(renderer, 
                     physics.getX(), physics.getY(), 
                     WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

}

Cockpit* Rocket::getCockpit() {
  return &this->cockpit;
}
Physics* Rocket::getPhysics(){
  return &this->physics;
}
int Rocket::getWidth() {
  return this->width;
}
int Rocket::getHeight() {
  return this->height;
}
