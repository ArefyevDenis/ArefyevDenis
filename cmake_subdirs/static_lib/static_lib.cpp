#include "static_lib.h"

#include <iostream>

Static_lib::Static_lib(){
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

Static_lib::~Static_lib(){
   std::cout << __PRETTY_FUNCTION__ << "\n";
}
