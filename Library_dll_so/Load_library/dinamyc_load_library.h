#ifndef DINAMYC_LOAD_LIBRARY_H
#define DINAMYC_LOAD_LIBRARY_H

#include <string>
#include <map>

namespace DLL {

  class Base_alg;

  class Dinamyc_load_library{
  public:

    typedef Base_alg*(*CREATOR_F)();
    typedef void DESTROY_F(Base_alg*);

    Dinamyc_load_library()                                            = default;
    Dinamyc_load_library(const Dinamyc_load_library&)                 = default;
    Dinamyc_load_library(Dinamyc_load_library&& )                     = default;
    Dinamyc_load_library& operator = (const Dinamyc_load_library& )   = default;
    Dinamyc_load_library& operator = (Dinamyc_load_library&& )        = default;
    ~Dinamyc_load_library()                                           = default;

   void Open_lib(const std::string &lib);                               /// открывает (подгружает) библиотеку
   void Find_sym(const std::string &library,const std::string &sym); /// ищет символ в заданной библиотеке

   Base_alg* Delete_obj(const std::string &sym);                        /// возвращает указатель ф-ции уничтожающей объект ( delete Object )
   void Close_lib(const std::string &lib);                              /// закрывает (выгружает) библиотеку

   CREATOR_F get_creator_function(const std::string &sim);    /// возвращает указатель  на функцию для создания объекта ( new Object )
   Base_alg* get_pointer_object(const std::string &sym);      /// возвращает указатель на созданый объект ( new Object )

  private:

   std::map<std::string, Base_alg* (*)()>                        _FCreates; ///
   std::map<std::string, void *>                                 _LHandles; ///
   //std::map<std::string,std::pair<void *,Base_alg *(*)()> >      _LibHandlCreat;

  };

}


#endif // DINAMYC_LOAD_LIBRARY_H
