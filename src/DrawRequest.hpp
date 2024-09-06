#include <SDL2/SDL.h>
#include <iostream>

class DrawRequest{
  public:
          DrawRequest(){std::cout << "Create DrawRequest\n";}
  virtual ~DrawRequest(){std::cout << "Delete DrawRequest()\n";}
  virtual void  draw(SDL_Renderer* _renderer){}
};

template<typename T>
class DrawLineRequest : public DrawRequest{
public:
  ~DrawLineRequest<T>() override { std::cout << "Delete Line.\n";}

  enum Type{
    Endpoint,
    Direction
  };
  DrawLineRequest(T* _x1, T* _y1, T* _x2, T* _y2, Type _type) : c(0,0,0,0){
    type = _type;
    x1 = _x1;
    y1 = _y1;
    x2 = _x2;
    y2 = _y2;
  }
  void setColor(int _r, int _g, int _b, int _a){
      c.r = _r;
      c.g = _g;
      c.b = _b;
      c.a = _a;
  }
  Type type;
  void draw(SDL_Renderer* _renderer) override{
  SDL_SetRenderDrawColor(_renderer,c.r,c.g,c.b,c.a);
    if(type == Type::Endpoint){
      SDL_RenderDrawLine(_renderer, (int)*x1,(int)*y1,(int)*x2,(int)*y2);
    }else{
      SDL_RenderDrawLine(_renderer,(int)*x1,(int)*y1,(int)(*x1+*x2),(int)(*y1 + *y2));
    }
  }
  
  struct color{
    int r,g,b,a;
    color(int _r, int _g, int _b, int _a){r=_r;g=_g;b=_b;a=_a;}
  };

private:
  T *x1, *y1;
  T *x2, *y2;
  color c;
};
