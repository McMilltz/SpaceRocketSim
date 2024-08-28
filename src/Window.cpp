#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstddef>

Window::Window(int width, int height) {

    this->width = width;
    this->height = height;

}

Window::~Window() {

  if (window != NULL) {
    SDL_DestroyWindow(window);
    window = NULL;
  }
  if (renderer != NULL) {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
  }
  SDL_Quit();

}

int Window::setup_SDL() {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Error on SDL initialization: " << SDL_GetError() << endl;
        return 1;
    }

    window = SDL_CreateWindow(  "Super insane rocket holy shit", 
                                SDL_WINDOWPOS_CENTERED, 
                                SDL_WINDOWPOS_CENTERED,
                                width,
                                height,
                                SDL_WINDOW_BORDERLESS);
    if (window == NULL) {
        cout << "Error on SDL Window Creation: " << SDL_GetError() << endl;
        return 1;
    }

    renderer = SDL_CreateRenderer(window, 0, 0);
    if (renderer == NULL) {
        cout << "Error on SDL Renderer Creation: " << SDL_GetError() << endl;
        return 1;
    }

    return 0;

}

void Window::wait() {

    SDL_Delay(2000);

}


