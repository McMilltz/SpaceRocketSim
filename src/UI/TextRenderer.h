#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include <unordered_map>

class TextRenderer {

  private:
  SDL_Surface *spriteSurface;

  std::string texturePath;
  std::string* bitmapLayout;
  int amountOfRows;
  int charWidth;
  int charHeight;
  std::unordered_map<char, SDL_Texture*> charTextureMap;

  void loadBitmap(SDL_Renderer* renderer);

  public:
  void init(SDL_Renderer* renderer,
                        std::string& texturePath, 
                        std::string *bitmapLayout,
                        int amountOfRows,
                        int charWidth,
                        int charHeight);

  void renderText(SDL_Renderer* renderer, 
                  std::string text, 
                  int x, int y, 
                  SDL_Color color, 
                  int fontWidth,
                  int fontHeight);


  void cleanUp();

};

#endif // !TEXTRENDERER_H
