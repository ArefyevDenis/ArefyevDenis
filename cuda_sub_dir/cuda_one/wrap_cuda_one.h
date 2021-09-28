#ifndef WRAP_CUDA_ONE_H
#define WRAP_CUDA_ONE_H

#include "../base_alg.h"

class Wrap_cuda_one : public
    Base_alg
{
public:
  Wrap_cuda_one( )              ;
  Wrap_cuda_one(const Wrap_cuda_one&)                 = default;
  Wrap_cuda_one(Wrap_cuda_one&& )                     = default;
  Wrap_cuda_one& operator = (const Wrap_cuda_one& )   = default;
  Wrap_cuda_one& operator = (Wrap_cuda_one&& )        = default;
  ~Wrap_cuda_one()              ;

  void apply(void* arg = nullptr) override;
};

#define CREATE_CLASS(B, C) extern "C" B* create_##C(){  return new C(); }
#define DESTROY_CLASS(C) extern "C" void destroy_##C(C* p) { delete p; }
#define REGISTER_CREATE_CLASS(C) CREATE_CLASS(Base_alg, C)

#endif // WRAP_CUDA_ONE_H
