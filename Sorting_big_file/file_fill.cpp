#include "file_fill.h"

#include <file_server.h>
#include <iostream>
#include <iomanip>
#include <QFile>
#include <QTextStream>
#include <cstring>
#include <parser_args.h>
namespace  {
  uint SZ_BUF{1024};
}

File_fill::File_fill(QObject *parent) :
  QObject(parent)
{
  p_fs  = dynamic_cast<File_server*>(parent);
 // size_ =  std::stoi(""); trow
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

void File_fill::filling_sfile()
{
  try{
    size_ =  std::stoi(r_pars().get_argv("-s"));
    char buf[SZ_BUF];
    // std::fstream *
    for(auto kvp: p_fs->_fstrm_map){
        std::cout << kvp.first << " " << kvp.second << "\n";
        std::fstream *p_fsstr = kvp.second;
        for(uint ix=0;ix<size_;++ix){
            std::memset(buf,0,sizeof(buf));
            //std::sprintf(buf,"%8d%c",std::rand()%1024," \n"[ix%16==15]);
            std::sprintf(buf,"%10d%c",ix," \n"[ix%16==15]);
            *p_fsstr << buf;
          }
        *p_fsstr << "\n";
      }
  }catch(std::exception& ex){
    std::cout << __PRETTY_FUNCTION__ << ' ' << ex.what() << '\n';
  }

}
/// https://www.kdab.com/qt-range-based-for-loops-and-structured-bindings/
void File_fill::filling_qfile()
{
  try{
    size_ =  std::stoi(r_pars().get_argv("-s"));
    char buf[SZ_BUF];
    // Qfile *
    for(auto kvp: p_fs->_qfile_map){
        std::cout  << kvp << "\n";
        QFile *p_qfile = kvp;
        QTextStream qt_stream(p_qfile);
        for(int ix=0;ix<size_;++ix){
            std::memset(buf,0,sizeof(buf));
            //std::sprintf(buf,"%8d%c",std::rand()%1024," \n"[ix%16==15]);
            std::sprintf(buf,"%10d%c",ix," \n"[ix%16==15]);
            qt_stream << buf;
          }
        qt_stream << "\n";
      }

  }catch(std::exception& ex){
    std::cout << __PRETTY_FUNCTION__ << ' ' << ex.what() << '\n';
  }
}
