#include "Regulator.h"
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_pixels.h>
#include <cmath>

Regulator::Regulator(){
  mStarPosition = {.x = 750, .y = 300};
  active = true;
  // DrawRequest* d = new DrawLineRequest<float>(&mPosition.x,&mPosition.y,&optAcceleration.x,&optAcceleration.y,DrawLineRequest<float>::Type::Direction);
  // Gizmos::addRequest("optAcceleration", d);
  DrawRequest* d = new DrawLineRequest<float>(&mPosition.x,&mPosition.y,&optVelocity.x,&optVelocity.y,DrawLineRequest<float>::Type::Direction);
  ((DrawLineRequest<float>*)d)->setColor(255, 0, 0, 255);
  Gizmos::addRequest("optVelocity", d);

}
Regulator::~Regulator(){
  Physics::~Physics();
  //clear other Gizmos
  Gizmos::remove("optAcceleration");
  Gizmos::remove("optVelocity");
  
}

void Regulator::setStarPosition(float _x, float _y){
  mStarPosition = {.x = _x, .y = _y};
}

void Regulator::toggleAutopilot(){
  active = !active;
  std::cout << "Autopilot is now " << (active ? "active" : "inactive")<< ".\n";
}

void Regulator::calculateTranslation(){
  starDist = mStarPosition - mPosition;
  starDist.x -= mVelocity.x*sqrt(2.0f*N_2PI/ALPHA);
  starDist.y -= mVelocity.y*sqrt(2.0f*N_2PI/ALPHA);
  // float redStarDist = starDist.magnitude() - mVelocity.magnitude()*sqrt(2.0f*N_2PI/ALPHA);
  // float redF = redStarDist / starDist.magnitude();
  // starDist.x *= redF;
  // starDist.y *= redF;

  float v_opt = sqrt(2.0f * ACC / (1.0f + starDist.magnitude()));
  optVelocity.x = starDist.x * v_opt;
  optVelocity.y = starDist.y * v_opt;

  optAcceleration = optVelocity - mVelocity;
}

void Regulator::calculateTargetAngle(){
  phi_0 = acos(-optAcceleration.y / optAcceleration.magnitude());
  if(starDist.x < 0){
    phi_0 *= -1.0f;
  }
}

bool Regulator::calculateOvershootAngle(){
  d_phi = mRotation - phi_0;
  bool OmG = false;
  if(mRotSpeed >= 0.0f){
    //Calculate Angle Phase State: d_phi_1 and d_phi_crit
    d_phi_crit = -pow(mRotSpeed,2)/(2.0f*ALPHA);
    delta = d_phi - d_phi_crit;
    // int m = (int)(d_phi - d_phi_crit) / N_2PI;
    int m = delta / N_2PI;
    delta -= m*N_2PI;
    // d_phi_1 = d_phi - m*N_2PI;
    // delta = d_phi - d_phi_crit - m*N_2PI;
    // if(d_phi_1 < d_phi_crit){
    //   d_phi_1 += N_2PI;
    // }
    if(delta < 0.0f){
      delta += N_2PI;
    }

    d_phi_1 = d_phi_crit + delta;
    d_phi_2 = d_phi_1 - N_2PI;

    //decide on which route to take:
    // delta = d_phi_1 - d_phi_crit;
    float G = delta + sqrt(-2.0f * delta * d_phi_crit) - M_PI;
    // OmG = M_PI < delta + sqrt(-2.0f * delta * d_phi_crit);
    OmG = G > 0.0f;

  }
  else{
    d_phi_crit = pow(mRotSpeed,2)/(2.0f*ALPHA);
    delta = d_phi_crit - d_phi;
    int m = (int)(-delta) / N_2PI;
    delta += m*N_2PI;
    if(delta < 0.0f){
      delta += N_2PI;
    }

    d_phi_1 = d_phi_crit - delta;
    d_phi_2 = d_phi_1 + N_2PI;

    float G = delta + sqrt(2.0f * delta * d_phi_crit) - M_PI;
    OmG = G > 0.0f;
    // OmG = M_PI < delta + sqrt(2.0f * delta * d_phi_crit);
  }
  return OmG;

}

void Regulator::regulateEngines(){
  if(ang_acc >= 0.5f){
    mEngines[0] = 1.0f;
    mEngines[AMOUNT_OF_ENGINES - 1] = 0.0f;
  }else if(ang_acc <= -0.5f){
    mEngines[0] = 0.0f;
    mEngines[AMOUNT_OF_ENGINES - 1] = 1.0f;
  } 
  d_phi -= ((int)(d_phi/N_2PI)) * N_2PI;
  if(d_phi > M_PI){
    d_phi -= N_2PI;
  }else if (d_phi < -M_PI) {
    d_phi += N_2PI;
  }

  if(abs(d_phi) < 1.3f){//Pi/6
    float thr = 1.0f - (abs(d_phi)/1.3f);
    mEngines[1] = thr;
    mEngines[2] = thr;
  }else{
    mEngines[1] = 0.0f;
    mEngines[2] = 0.0f;
  }

}

void Regulator::update(float _dt){
  if(active){
    std::cout << "Regulator update.\n";
    calculateTranslation();
    calculateTargetAngle();
    bool OmG = calculateOvershootAngle();
    if(mRotSpeed > 0.0f){
      ang_acc = OmG ? 1.0f : -1.0f;
    }else{
      ang_acc = OmG ? -1.0f : 1.0f;
    }
    regulateEngines();
  }
  Physics::update(_dt);

}
