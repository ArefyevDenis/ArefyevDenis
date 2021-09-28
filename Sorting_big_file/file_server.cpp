#include "file_server.h"

#include <parser_args.h>
#include <iostream>

#include<factory.h>

File_server::File_server(QObject *parent) :
  QObject(parent),
  f_create(this),
  f_fill(this),
  f_sort(this)
{  
  files = r_pars().get_argv("-f");
  sizes = r_pars().get_argv("-s");

  FACT::Factory<QObject>::crt("TFC::AA");

  apply();

  std::cout << __PRETTY_FUNCTION__ << " "+files << " "+sizes << '\n';
}

void File_server::apply()
{
  f_create.create_sfile(files.c_str());
  f_create.create_qfile(files.c_str());

  f_fill.filling_sfile();
  f_fill.filling_qfile();

}

File_server::~File_server()
{
  /// https://www.kdab.com/qt-range-based-for-loops-and-structured-bindings/
  for(auto kvp : _qfile_map){
     delete kvp;
    }
  for(auto kvp : _fstrm_map){
      delete kvp.second;
    }
   std::cout << __PRETTY_FUNCTION__ << '\n';
}
