#include "Window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED,
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
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
      std::cout << "Error initializing IMG_INIT_PNG.\n";
    }
    return 0;

}


void Window::cleanUp() {

  if (this->renderer != nullptr) {
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
  }
  if (this->window != nullptr) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
  
  IMG_Quit();
  SDL_Quit();

}

SDL_Renderer* Window::getRenderer() {
  return this->renderer;
}
SDL_Window* Window::getWindow() {
  return this->window;
}

void Window::wait() {

    SDL_Delay(2000);

}


