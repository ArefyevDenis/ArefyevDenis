#ifndef ENCAPSULATION_OBJ_H
#define ENCAPSULATION_OBJ_H

#include "configurate_obj.h"
#include "factory_morf.h"

#include <memory>
#include <map>
#include <string>

class Encapsulation_obj
{
public:
  Encapsulation_obj(Configurate_obj&);

  Encapsulation_obj(const Encapsulation_obj&)               = delete ;
  Encapsulation_obj(Encapsulation_obj&&)                    = delete ;
  Encapsulation_obj& operator = (Encapsulation_obj&&)       = delete ;
  Encapsulation_obj& operator = (const Encapsulation_obj&)  = delete ;

  ~Encapsulation_obj();

  void create_modules();

private:

  Configurate_obj &c_obj_;

  Factory_Morf f_morf;

  std::map<std::string, Base_factory *> map_str_f;

};

#endif // ENCAPSULATION_OBJ_H
