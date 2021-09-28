#include "library_one.h"

//#include &lt;iostream&gt;

namespace LIBONE {

  void Library_one::apply(void * arg){
      if(arg == nullptr){
          std::cout << "Library_one::apply(void * arg) \n";
        }
  }

  REGISTER_CREATE_CLASS(Library_one)
  DESTROY_CLASS(Library_one)

}


