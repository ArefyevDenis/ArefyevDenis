#include "file_create.h"

#include <QFile>
#include <QDir>
#include <QTextStream>

#include <qqfile.h>

#include <file_server.h>
#include <parser_args.h>

#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>

// только для отладки
//class FFStream :
//    public std::fstream
//{
//public:
//  FFStream () : std::fstream()
//  {}

//  explicit FFStream( const char* filename, std::ios_base::openmode mode = ios_base::in|ios_base::out )
//  : std::fstream(filename,mode)
//  {std::cout << __PRETTY_FUNCTION__ << "\n";}

// // explicit FFStream( const std::filesystem::path::value_type* filename, std::ios_base::openmode mode = ios_base::in|ios_base::out ){}

//  explicit FFStream( const std::string& filename, std::ios_base::openmode mode = ios_base::in|ios_base::out )
//   : std::fstream(filename,mode)
//  {std::cout << __PRETTY_FUNCTION__ << "\n";}

//  explicit FFStream( const std::filesystem::path& filename,  std::ios_base::openmode mode = ios_base::in|ios_base::out )
//   : std::fstream(filename,mode)
//  {std::cout << __PRETTY_FUNCTION__ << "\n";}

//  FFStream( FFStream&& other )
//   : std::fstream(std::move(other))
//  {std::cout << __PRETTY_FUNCTION__ << "\n";}

//  ~FFStream() override {std::cout << __PRETTY_FUNCTION__ << "\n";}

//};

File_create::File_create(QObject *parent) : QObject(parent)
{
  p_fs = dynamic_cast<File_server*>(parent);
  p_qfile_map = &p_fs->_qfile_map;
  p_fstrm_map = &p_fs->_fstrm_map;
}

File_create::~File_create()
{

}

void File_create::create_qfile(const char* name)
try{
  QString q_path = QDir::currentPath();

  QString s_name{name};
  QStringList f_list{QString(name).split(' ')};

  for(auto kvp: f_list){
      // если ключ в массиве найден
      if(p_qfile_map->contains(kvp))
        continue;
      // если ключа в массиве небыло
      QQFile *p_qqf = new QQFile(q_path+"/temp/"+kvp+".qtxt");
      if(p_qqf == nullptr)
        continue;
      // если память выделена откроем
      if(p_qqf->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)){
          std::cout << q_path.toStdString()+"/temp/"+kvp.toStdString()+".qtxt" << '\n';
        }
      // всегда вставим
      p_qfile_map->insert(kvp,p_qqf);
    }
  std::cout << __PRETTY_FUNCTION__ << '\n';
}catch(...){
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

void File_create::create_sfile(const char *name)
{

  std::string path{std::filesystem::current_path()};

  std::stringstream sstr{name};
  std::string arg;
  while(std::getline(sstr,arg,' ')){
      // если такой ключ есть заход на новый круг
      if(p_fstrm_map->find(arg) !=  p_fstrm_map->end())
        continue;
      // если ключа нет создаём std::fstream
      std::fstream* p_ffs = new  std::fstream();
      if(p_ffs == nullptr)
        continue;
      // если всё ОК вставим в MAP
      auto pair = p_fstrm_map->insert({arg, p_ffs});
      // если вставка не произошла утечка памяти ??????
      if(pair.second){
          pair.first->second->open(path+"/temp/"+arg+".stxt",std::ios_base::out|std::ios_base::trunc);
          std::cout << path+"/temp/"+arg+".stxt"  <<  "\n";
        }else{
          delete p_ffs;
        }
    }

}
