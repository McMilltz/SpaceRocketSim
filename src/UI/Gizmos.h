#include "DrawRequest.hpp"
#include <algorithm>
#include <map>

class Gizmos{
public:
  typedef std::map<std::string, DrawRequest*> MAP;
public:
  ~Gizmos();
  static void addRequest(const std::string& _key, DrawRequest* _request);
  static void drawAll(SDL_Renderer* _renderer);
  static void remove(const std::string& _key);
  static void clear();
private:
  static MAP mQueue;
};
