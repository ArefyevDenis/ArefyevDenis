#ifndef DIN_LOAD_LIB_H
#define DIN_LOAD_LIB_H

#include <string>
#include <initializer_list>
#include <string>
#include <map>

namespace DLL {

  class Base_alg;

  class Din_load_lib{
  public:

    Din_load_lib()                                    = default;
    Din_load_lib(const Din_load_lib&)                 = default;
    Din_load_lib(Din_load_lib&& )                     = default;
    Din_load_lib& operator = (const Din_load_lib& )   = default;
    Din_load_lib& operator = (Din_load_lib&& )        = default;
    ~Din_load_lib()                                   = default;

    Din_load_lib(std::initializer_list<std::string> il);
    Din_load_lib& operator = (std::initializer_list<std::string> il );

    Base_alg* open_find_creat(const std::string &lib,const std::string &sym);   /// открывает библиотеку ищет символ создаёт объект

    void delete_close_lib(const std::string &lib,const std::string &sym);       /// закрывает (выгружает) библиотеку

    Base_alg* get_pointer_object(const std::string &sym);                       /// возвращает указатель на созданый объект

  private:

   std::map<std::string, void *>     LString_handl; /// имя библиотеки и дескриптор
   std::map<void *,  Base_alg *>     LHandl_point;  /// дескриптор и указатель на объект

  };

}


#endif // DIN_LOAD_LIB_H
