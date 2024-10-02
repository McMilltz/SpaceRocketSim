struct InputData{
  double dX, dY, relDist;
  double velX, velY, speed;
  double cos_phi, sin_phi;
  double rotSpeed, d_phi;
  double thrust[4];

  #define INPUT_COUNT 14 
private:
  double input[INPUT_COUNT];

public:
  double* getInputs(){
    input[0] =  dX;
    input[1] =  dY;
    input[2] =  velX;
    input[3] =  velY;
    input[4] =  speed;
    input[5] =  relDist;
    input[6] =  cos_phi;
    input[7] =  sin_phi;
    input[8] =  rotSpeed;
    input[9] =  d_phi;
    input[10] =  thrust[0];
    input[11] =  thrust[1];
    input[12] = thrust[2];
    input[13] = thrust[3];

    return &input[0];
  }
};
