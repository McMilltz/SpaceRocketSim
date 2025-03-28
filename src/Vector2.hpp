#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <math.h>
#include <iostream>

typedef struct Vector2f{
  float x;
  float y;
  float magnitude(){
    return sqrt(pow(x, 2) + pow(y, 2));
  }
  void print(){
    std::cout << "x: " << (int)x << ", y: " << (int)y << "\n";
  }
  Vector2f operator-(Vector2f& _other){
    return {.x = x - _other.x, .y = y - _other.y};
  }
  Vector2f operator*(float _f){
    return {.x = _f * x, .y = _f * y};
  }
  float angle(){
    float result = acos(-y/magnitude());
    if(x < 0)
      result *= -1.0f;
    return result;
  }
} Vector2f;

#endif
