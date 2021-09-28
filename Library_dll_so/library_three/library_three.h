#ifndef LIBRARY_THREE_H
#define LIBRARY_THREE_H

#include <iostream>

namespace LIBTHREE {

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

  class Library_three : public
      Base_alg
  {
  public:
    Library_three(void *arg = nullptr )               {std::cout << "Construct Library_three \n";}
    Library_three(const Library_three&)                 = default;
    Library_three(Library_three&& )                     = default;
    Library_three& operator = (const Library_three& )   = default;
    Library_three& operator = (Library_three&& )        = default;
    ~Library_three()                                  {std::cout << "Destruct Library_three \n";}

    void apply(void * arg);
  };

#define CREATE_CLASS(B, C) extern "C" B* create_##C(){ return new C(); } /// std::cout << " create object \n";
#define DESTROY_CLASS(C) extern "C" void destroy_##C(C* p) { delete p; }
#define REGISTER_CREATE_CLASS(C) CREATE_CLASS(Base_alg, C)

}
#endif // LIBRARY_THREE_H
