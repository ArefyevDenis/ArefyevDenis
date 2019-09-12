#include "factory_morf.h"

#include <iostream>

std::map<std::string, Base_factory *(*)()> *_iserialize_builders = nullptr;

void delete_iserialize_builders(){
  if(_iserialize_builders != nullptr){
      delete _iserialize_builders;
      _iserialize_builders = nullptr;
    }
}

Factory_Morf::~Factory_Morf() {
  //std::cout << __PRETTY_FUNCTION__ << '\n';
}

bool Factory_Morf::set(const char *name, Base_factory *(*creator)()){
 // std::cout << __PRETTY_FUNCTION__ << '\n';
  if(_iserialize_builders == nullptr){
      _iserialize_builders = new std::map<std::string, Base_factory *(*)()>();
      atexit(delete_iserialize_builders);
    }
  return _iserialize_builders->insert(std::map<std::string, Base_factory *(*)()>::value_type (name, creator)).second;
}

Base_factory* Factory_Morf::create(const char *name){
  //std::cout << __PRETTY_FUNCTION__ << '\n';
  std::map<std::string, Base_factory *(*)()>::iterator it = _iserialize_builders->find(name);
  if(it == _iserialize_builders->end())
    return nullptr;
  return (it->second)();
}

CREATOR_FUNC Factory_Morf::getCreator(const char *name){
  std::cout << __PRETTY_FUNCTION__ << '\n';
  std::map<std::string, Base_factory *(*)()>::iterator it = _iserialize_builders->find(name);
  if(it == _iserialize_builders->end())
    return nullptr;
  return (it->second);
}
