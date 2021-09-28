#include "din_load_lib.h"

#include <dlfcn.h>
#include <iostream>

/// __attribute __ ((constructor)
/// __attribute __ ((destructor)

namespace DLL {

  /// открывает библиотеку ищет символ создаёт объект
  Base_alg* Din_load_lib::open_find_creat(const std::string &lib,const std::string &sym){

    dlerror();
    void *handle = dlopen(lib.c_str(),RTLD_LAZY); ///RTLD_LAZY ///RTLD_GLOBAL|RTLD_NOW
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
        return nullptr;
      }else{
        LString_handl.insert(std::map<std::string,void *>::value_type (lib.c_str(), handle));    ///.second; /// сохраним handle библиотеки
        Base_alg *(*create)(void) = (Base_alg *(*)())(dlsym(handle,sym.c_str()));/// ищем в этой библиотеке указанный символ ( функцию )
        if ( create == nullptr) { ///((err = dlerror()) != NULL)
            std::cerr << "andle error, the symbol wasn't found: " << dlerror() << '\n';
            return nullptr;
          } else {
            LHandl_point.insert(std::pair<void* ,Base_alg* >(handle,(*create)()));
            return  LHandl_point[handle];
          }
      }

  }

  /// уничтожаем объект закрывает (выгружает) библиотеку
  void Din_load_lib::delete_close_lib(const std::string &lib,const std::string &sym){

    dlerror();
    std::map<std::string, void *>::iterator it = LString_handl.find(lib);/// проверяем подгружена ли библиотека
    if (it != LString_handl.end()){
        void *handle = it->second; /// если да подгружена то прочтём её дескриптор
        if(handle != nullptr){     /// если дескриптор не равен 0 то
            Base_alg *(*destroy)(Base_alg*) = (Base_alg *(*)(Base_alg*))(dlsym(handle,sym.c_str()));/// ищем в этой библиотеке указанный символ ( функцию )
            if ( destroy == nullptr) { ///((err = dlerror()) != NULL)
                std::cerr << "andle error, the symbol wasn't found: " << dlerror() << '\n';
              } else {
                (*destroy)(LHandl_point[handle]);
                dlclose(handle);
              }
          }
      }

  }

  /// возвращает указатель на созданый объект
  Base_alg* Din_load_lib::get_pointer_object(const std::string &sym){

  }

}
