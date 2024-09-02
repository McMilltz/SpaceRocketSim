#include "TextRenderer.h"
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <cstddef>

void TextRenderer::init(SDL_Renderer* renderer,
                               std::string& texturePath, 
                               std::string *bitmapLayout,
                               int amountOfRows,
                               int charWidth,
                               int charHeight) {

  this->texturePath = texturePath;
  this->bitmapLayout = bitmapLayout;
  this->amountOfRows = amountOfRows;
  this->charWidth = charWidth;
  this->charHeight = charHeight;

  std::cout << "renderer: " << renderer << "\n";

  loadBitmap(renderer);
  

}

void TextRenderer::loadBitmap(SDL_Renderer* renderer) {

  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    std::cout << "Error initializing IMG_INIT_PNG: " << IMG_GetError() << "\n";
    return;
  }

  this->spriteSurface = IMG_Load(this->texturePath.c_str());
  if (this->spriteSurface == nullptr) {
    std::cout << "Error loading font image: " << IMG_GetError() << "\n";
    return;
  }

  SDL_Texture* fontTexture = SDL_CreateTextureFromSurface(renderer, 
                                                          this->spriteSurface);
  if (fontTexture == NULL) {
    std::cerr << "Error SDL_CreateTextureFromSurface: " << SDL_GetError() << "\n";
    return;
  }
  SDL_SetTextureBlendMode(fontTexture, SDL_BLENDMODE_BLEND);
  
  for (int rows = 0; rows < this->amountOfRows; rows++) {
    for (int c = 0; c < (int) this->bitmapLayout[rows].size(); c++) {

      SDL_Rect srcRect;
      srcRect.x = c * this->charWidth;
      srcRect.y = rows * this->charHeight;
      srcRect.w = this->charWidth;
      srcRect.h = this->charHeight;

      SDL_Texture* charTexture = SDL_CreateTexture(renderer, 
                                                   SDL_PIXELFORMAT_RGBA8888, 
                                                   SDL_TEXTUREACCESS_TARGET, 
                                                   this->charWidth, 
                                                   this->charHeight);
      SDL_SetTextureBlendMode(charTexture, SDL_BLENDMODE_BLEND);

      SDL_Texture* renderTargetBackup = SDL_GetRenderTarget(renderer);
      SDL_SetRenderTarget(renderer, charTexture);
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, fontTexture, &srcRect, NULL);
      SDL_SetRenderTarget(renderer, renderTargetBackup);
      this->charTextureMap[this->bitmapLayout[rows][c]] = charTexture;

    }
  }


}

void TextRenderer::renderText(SDL_Renderer* renderer, 
                              std::string text,
                              int x, int y,
                              SDL_Color color,
                              int fontWidth,
                              int fontHeight) {

  SDL_Rect targetRect;
  targetRect.w = fontWidth;
  targetRect.h = fontHeight;
  targetRect.y = y;

  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  
  for (int i = 0; i < (int) text.size(); i++) {

    targetRect.x = x + i * fontWidth;
    SDL_RenderCopy(renderer, this->charTextureMap[text[i]], NULL, &targetRect);

  }

}

void TextRenderer::cleanUp() {

  for (auto& pair : charTextureMap) {
    SDL_DestroyTexture(pair.second);
  }
  charTextureMap.clear();

  SDL_FreeSurface(spriteSurface);
  IMG_Quit();

}
