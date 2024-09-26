#include "NNRocket.h"

NNRocket::NNRocket() : physics()
{

}

void NNRocket::update(float _dt){
  physics.update(_dt);
}
