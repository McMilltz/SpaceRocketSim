#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string.h>
#include <iostream>

using namespace std;

class Window {
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  int width;
  int height;

public:
  Window(int width, int height);
  ~Window();

  int setup_SDL();
  void wait();

};

#endif  // WINDOW_H
