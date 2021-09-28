#include <QCoreApplication>

#include "din_load_lib.h"

#include "../library_one/library_one.h"
#include "../library_two/library_two.h"
#include "../library_three/library_three.h"

#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[])
{
//  QCoreApplication a(argc, argv);

  DLL::Din_load_lib dll;

  std::string out_pwd(PATH_OBJECT_FILE);

  std::string lib_one = out_pwd  + "/../lib/liblibrary_one.so";
  std::string lib_two = out_pwd  + "/../lib/liblibrary_two.so";
  std::string lib_tree = out_pwd + "/../lib/liblibrary_three.so";

 LIBONE::Library_one* l_one  = (LIBONE::Library_one*) dll.open_find_creat(lib_one,std::string("create_Library_one"));
  {
    LIBTWO::Library_two* l_two  = (LIBTWO::Library_two*) dll.open_find_creat(lib_two,std::string("create_Library_two"));
    {
      LIBTHREE::Library_three* l_three  = (LIBTHREE::Library_three*) dll.open_find_creat(lib_tree,std::string("create_Library_three"));

      for(int i = 0; i < 10;i++){
          ::sleep(1);
          l_one->apply(nullptr);
          l_two->apply(nullptr);
          l_three->apply(nullptr);
        }

      dll.delete_close_lib(lib_tree,std::string("destroy_Library_three"));
    }
    dll.delete_close_lib(lib_two,std::string("destroy_Library_two"));
  }
  dll.delete_close_lib(lib_one,std::string("destroy_Library_one"));

  std::cout <<  lib_one << "\n";
  std::cout <<  lib_two << "\n";
  std::cout <<  lib_tree << "\n";


//  return a.exec();
}
