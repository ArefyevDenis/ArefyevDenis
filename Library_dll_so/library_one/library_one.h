#ifndef LIBRARY_ONE_H
#define LIBRARY_ONE_H

#include <iostream>

namespace LIBONE {

  class Base_alg{
  public:
    Base_alg()                                = default;
    Base_alg(const Base_alg&)                 = default;
    Base_alg(Base_alg&& )                     = default;
    Base_alg& operator = (const Base_alg& )   = default;
    Base_alg& operator = (Base_alg&& )        = default;
    virtual ~Base_alg()                       = default;

    virtual void apply(void *) = 0; ///применять, использовать

  };

  class Library_one : public
      Base_alg
  {
  public:
    Library_one(void *arg = nullptr )               {std::cout << "Construct Library_one \n";}
    Library_one(const Library_one&)                 = default;
    Library_one(Library_one&& )                     = default;
    Library_one& operator = (const Library_one& )   = default;
    Library_one& operator = (Library_one&& )        = default;
    ~Library_one()                                  {std::cout << "Destruct Library_one \n";}

    void apply(void * arg);
  };

#define CREATE_CLASS(B, C) extern "C" B* create_##C(){  return new C(); } ///std::cout << " create object \n";
#define DESTROY_CLASS(C) extern "C" void destroy_##C(C* p) { delete p; }
#define REGISTER_CREATE_CLASS(C) CREATE_CLASS(Base_alg, C)

}




#endif // LIBRARY_ONE_H
