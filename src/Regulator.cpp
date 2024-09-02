#include "Regulator.h"
#include <SDL2/SDL_mouse.h>
#include <cmath>

Regulator::Regulator(){
  mStarPosition = {.x = 750, .y = 300};
}

void Regulator::setStarPosition(float _x, float _y){
  mStarPosition = {.x = _x, .y = _y};
}

void Regulator::toggleAutopilot(){
  active = !active;
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
  std::cout << "optAcc: ";
  optAcceleration.print();
}

void Regulator::calculateTargetAngle(){
  phi_0 = acos(-optAcceleration.y / optAcceleration.magnitude());
  if(starDist.x < 0){
    phi_0 *= -1.0f;
  }
  std::cout << "phi_0: " << phi_0 << "\n";
  
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
    // std::cout << "d_phi_2: " << (int)d_phi_2 << "d_phi_crit: " << (int)d_phi_crit << " , d_phi_1: " << (int)d_phi_1 << " , delta: " << (int)delta << ".\n";

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
    // std::cout << "d_phi_1: " << (int)d_phi_1 << " , d_phi_crit: " << (int)d_phi_crit << " , d_phi_2: " << (int)d_phi_2 << " , delta: " << (int)delta << ".\n";
  }
  // std::cout << "mRotSpeed: " << mRotSpeed << " , 2PI: " << N_2PI << ".\n"; 
  return OmG;

}

void Regulator::regulateEngines(){
  if(ang_acc >= 0.5f){
    mEngines[0] = 1.0f;
    mEngines[AMOUNT_OF_ENGINES - 1] = 0.0f;
    // std::cout << "turn right.\n";
  }else if(ang_acc <= -0.5f){
    mEngines[0] = 0.0f;
    mEngines[AMOUNT_OF_ENGINES - 1] = 1.0f;
    // std::cout << "turn left.\n";
  } 
  d_phi -= ((int)(d_phi/N_2PI)) * N_2PI;
  if(d_phi > M_PI){
    d_phi -= N_2PI;
  }else if (d_phi < -M_PI) {
    d_phi += N_2PI;
  }
  std::cout << "d_phi: " << d_phi << "\n";
  if(abs(d_phi) < 1.3f){//Pi/6
    std::cout << "main thruster activated.\n";
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
