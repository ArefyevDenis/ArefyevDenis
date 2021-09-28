#include "dinamyc_load_library.h"

#include <dlfcn.h>
#include <iostream>
namespace DLL {

  void Dinamyc_load_library::Open_lib(const std::string &lib){

    void *handle = dlopen(lib.c_str(),RTLD_LAZY); ///RTLD_LAZY ///RTLD_GLOBAL|RTLD_NOW
    if (!handle) {
        std::cerr << "Cannot open library: " << dlerror() << '\n';
      }else{
         _LHandles.insert(std::map<std::string,void *>::value_type (lib.c_str(), handle));    ///.second; /// сохраним handle библиотеки
      }
  }

  void  Dinamyc_load_library::Find_sym(const std::string &lib,const std::string &sym){

    std::map<std::string, void *>::iterator it = _LHandles.find(lib);/// проверяем подгружена ли библиотека
     if (it != _LHandles.end()){
         void *handle = it->second; /// если да подгружена то прочтём её дескриптор
         if(handle != nullptr){/// если дескриптор не равен 0 то
             Base_alg *(*create)(void) = (Base_alg *(*)())(dlsym(handle,sym.c_str()));/// ищем в этой библиотеке указанный символ ( функцию )
             _FCreates.insert(std::map<std::string,Base_alg *(*)()>::value_type(sym.c_str(), create));    ///.second; /// сохраним указатель на функцию
           }
       }

  }

  Base_alg*  Dinamyc_load_library::Delete_obj(const std::string &sym){
    std::map<std::string, Base_alg *(*)()>::iterator it = _FCreates.find(sym);
    if(it == _FCreates.end())
        return NULL;
    return (it->second)();
  }

  void  Dinamyc_load_library::Close_lib(const std::string &lib){
    std::map<std::string, void *>::iterator it = _LHandles.find(lib);    /// ищем handle библиотеки которую необходими закрыть
    void *handle = it->second;
    dlclose(handle);
  }

  Dinamyc_load_library::CREATOR_F  Dinamyc_load_library::get_creator_function(const std::string &sym){
    std::map<std::string, Base_alg* (*)()>::iterator it = _FCreates.find(sym);
    if(it == _FCreates.end())
        return NULL;
    return (it->second);
  }

  Base_alg*  Dinamyc_load_library::get_pointer_object(const std::string &sym){
    std::map<std::string, Base_alg* (*)()>::iterator it = _FCreates.find(sym);
    if(it == _FCreates.end())
        return NULL;
    return (it->second)();
  }

}
