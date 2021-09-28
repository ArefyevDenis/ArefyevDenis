#include "library_two.h"

namespace LIBTWO {

  void Library_two::apply(void * arg){
    if(arg == nullptr){
        std::cout << "Library_two::apply(void * arg) \n";
      }
  }

  REGISTER_CREATE_CLASS(Library_two)
  DESTROY_CLASS(Library_two)

}
