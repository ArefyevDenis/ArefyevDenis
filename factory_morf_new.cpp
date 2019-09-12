#include "factory_morf_new.h"

#include <iostream>

std::map<std::string, std::function<Base_factory*()>> _map_builders;

std::map<std::string, Base_factory *(*)()> *_iserialize_builders_new ;

void delete_iserialize_builders_new(){
  if(_iserialize_builders_new != nullptr){
      delete _iserialize_builders_new;
      _iserialize_builders_new = nullptr;
    }
}

Factory_Morf_new::~Factory_Morf_new() {
  //std::cout << __PRETTY_FUNCTION__ << '\n';
}

bool Factory_Morf_new::set(const char *name, Base_factory *(*creator)()){
 // std::cout << __PRETTY_FUNCTION__ << '\n';
  if(_iserialize_builders_new == nullptr){
      _iserialize_builders_new = new std::map<std::string, Base_factory *(*)()>();
      atexit(delete_iserialize_builders_new);
    }
  return _iserialize_builders_new->insert(std::map<std::string, Base_factory *(*)()>::value_type (name, creator)).second;
}

Base_factory* Factory_Morf_new::create(const char *name){
  //std::cout << __PRETTY_FUNCTION__ << '\n';
  auto it = _iserialize_builders_new->find(name);
  if(it == _iserialize_builders_new->end())
    return nullptr;
  return (it->second)();
}

CREATOR_FUNC Factory_Morf_new::getCreator(const char *name){
  std::cout << __PRETTY_FUNCTION__ << '\n';
  auto it = _iserialize_builders_new->find(name);
  if(it == _iserialize_builders_new->end())
    return nullptr;
  return (it->second);
}
























//void delete_iserialize_builders_new(){
//  if(_iserialize_builders_new != nullptr){
//      delete _iserialize_builders_new;
//      _iserialize_builders_new = nullptr;
//    }
//}

//Factory_Morf_new::~Factory_Morf_new() {
//  //std::cout << __PRETTY_FUNCTION__ << '\n';
//}

//bool Factory_Morf_new::set(const char *name, Base_factory *(*creator)()){
// // std::cout << __PRETTY_FUNCTION__ << '\n';
//  if(_iserialize_builders_new == nullptr){
//      _iserialize_builders_new = new std::map<std::string, Base_factory *(*)()>();
//      atexit(delete_iserialize_builders_new);
//    }
//  return _iserialize_builders_new->insert(std::map<std::string, Base_factory *(*)()>::value_type (name, creator)).second;
//}

//Base_factory* Factory_Morf_new::create(const char *name){
//  //std::cout << __PRETTY_FUNCTION__ << '\n';
//  std::map<std::string, Base_factory *(*)()>::iterator it = _iserialize_builders_new->find(name);
//  if(it == _iserialize_builders_new->end())
//    return nullptr;
//  return (it->second)();
//}

//CREATOR_FUNC Factory_Morf_new::getCreator(const char *name){
//  std::cout << __PRETTY_FUNCTION__ << '\n';
//  std::map<std::string, Base_factory *(*)()>::iterator it = _iserialize_builders_new->find(name);
//  if(it == _iserialize_builders_new->end())
//    return nullptr;
//  return (it->second);
//}
