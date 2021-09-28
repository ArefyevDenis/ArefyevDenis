#include "shared_lib.h"

#include <iostream>

Shared_lib::Shared_lib(){
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

Shared_lib::~Shared_lib(){
   std::cout << __PRETTY_FUNCTION__ << "\n";
}
