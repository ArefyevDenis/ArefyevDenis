#ifndef LIBRARY_TWO_H
#define LIBRARY_TWO_H

#include <iostream>

namespace LIBTWO {

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

  class Library_two : public
      Base_alg
  {
  public:
    Library_two(void *arg = nullptr )               {std::cout << "Construct Library_two \n";}
    Library_two(const Library_two&)                 = default;
    Library_two(Library_two&& )                     = default;
    Library_two& operator = (const Library_two& )   = default;
    Library_two& operator = (Library_two&& )        = default;
    ~Library_two()                                  {std::cout << "Destruct Library_two \n";}

    void apply(void * arg);
  };

#define CREATE_CLASS(B, C) extern "C" B* create_##C(){ return new C(); } /// std::cout << " create object \n";
#define DESTROY_CLASS(C) extern "C" void destroy_##C(C* p) { delete p; }
#define REGISTER_CREATE_CLASS(C) CREATE_CLASS(Base_alg, C)

}



#endif // LIBRARY_TWO_H
