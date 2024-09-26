struct InputData{
  double posX, posY;
  double velX, velY;
  double starX, starY;
  double rotSpeed, rotAngle;
  double thrust[4];

  #define INPUT_COUNT 12 
private:
  double input[INPUT_COUNT];

public:
  double* getInputs(){
    input[0] =  posX;
    input[1] =  posY;
    input[2] =  velX;
    input[3] =  velY;
    input[4] =  starX;
    input[5] =  starY;
    input[6] =  rotSpeed;
    input[7] =  rotAngle;
    input[8] =  thrust[0];
    input[9] =  thrust[1];
    input[10] = thrust[2];
    input[11] = thrust[3];

    return &input[0];
  }
};
