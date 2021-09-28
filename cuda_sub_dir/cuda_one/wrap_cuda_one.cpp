#include "wrap_cuda_one.h"

#include <iostream>

extern "C" void Cuda_Main_Test1();

Wrap_cuda_one::Wrap_cuda_one(){
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

Wrap_cuda_one::~Wrap_cuda_one(){
   std::cout << __PRETTY_FUNCTION__ << "\n";
}

void Wrap_cuda_one::apply(void* ptr){

  Cuda_Main_Test1();

}
