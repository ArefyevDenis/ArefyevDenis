#include "library_three.h"

namespace LIBTHREE {

  void Library_three::apply(void * arg){
    if(arg == nullptr){
        std::cout << "Library_three::apply(void * arg) \n";
      }
  }

  REGISTER_CREATE_CLASS(Library_three)
  DESTROY_CLASS(Library_three)

}
