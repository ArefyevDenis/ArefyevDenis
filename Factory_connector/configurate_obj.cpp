#include "configurate_obj.h"

#include <iostream>

namespace  {
  const std::string config_xml = "<config>"
                                  "<mod name=\"Configurate_obj\"/>"
                                 "</config>";

  std::string xmlCode = "<Data name=\"Position\" x=\"5\" y=\"5\"/>";

}

Configurate_obj::Configurate_obj():
  pr_xml(std::string(abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, nullptr) ))
{
  if(!pr_xml.load_xml()){
      pr_xml.create_xml(config_xml);
    }
 std::cout <<__PRETTY_FUNCTION__ << '\n';
}

Configurate_obj::~Configurate_obj(){
   std::cout <<__PRETTY_FUNCTION__ << '\n';
}
