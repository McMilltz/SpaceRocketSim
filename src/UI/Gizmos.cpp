#include "Gizmos.h"

Gizmos::MAP Gizmos::mQueue;

Gizmos::~Gizmos(){
  clear();
}

void Gizmos::addRequest(const std::string& _key, DrawRequest* _request){
  Gizmos::mQueue[_key] = _request;
}
void Gizmos::drawAll(SDL_Renderer* _renderer){
  std::for_each(Gizmos::mQueue.begin(),Gizmos::mQueue.end(),[&](auto iter){
    iter.second->draw(_renderer);
  });
}

void Gizmos::remove(const std::string& _key){
  auto it = Gizmos::mQueue.find(_key);
  if(it != Gizmos::mQueue.end()){
    delete it->second;
    Gizmos::mQueue.erase(it);
  }
  // DrawRequest* ptr = mQueue.at(_key);
  // delete mQueue.find(_key)->second;
}

void Gizmos::clear(){
  std::for_each(Gizmos::mQueue.begin(),Gizmos::mQueue.end(),[&](auto it){
    delete it.second;
  });
  Gizmos::mQueue.clear();
  std::cout << "Clear Gizmos.\n";
}

