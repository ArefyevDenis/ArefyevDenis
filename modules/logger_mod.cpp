#include "logger_mod.h"

#include <string>
#include <typeinfo>
#include <iostream>
#include <ctime>
#include <strstream>
#include "factory_morf.h"

REGISTER_SERIALIZABLE(Logger_mod);

namespace  {
  const std::string logger_mod = "<logger_mod>"
                                  "<mod name=\"Logger_mod\"/>"
                                 "</logger_mod>";
}

Logger_mod::Logger_mod() :
  pr_xml(std::string(abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, nullptr) ))
{


  bfp = boost::filesystem::current_path();
  bfp += "/logger/";
  if(!boost::filesystem::exists(bfp)){                /// если такой директории нет создадим
      if(!boost::filesystem::create_directory(bfp)){  /// если не получилось сразу завалим программу
          std::terminate();                           /// на этапе отладки чем громче упадёт тем лучше.
        }
    }

  if(!pr_xml.load_xml()){
      pr_xml.create_xml(logger_mod);
    }

  //LOG(NULL,timeStr.c_str());

}

Logger_mod::~Logger_mod(){
  of_log.close();
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

void Logger_mod::b_apply(void *pt){

  std::string *str{nullptr};

  if(pt != nullptr){
      str = static_cast<std::string *>(pt);
      //lg(*str);
      lg(of_log, *str);

      if(static_cast<double>(MAX_TIME) < std::difftime(std::time(nullptr),t)){
          b_stop(nullptr);
          b_start(nullptr);
        }

    }

}

void Logger_mod::b_start(void *pt){

  t = std::time(nullptr);
  tm = *std::localtime(&t);
  std::stringstream st_vid;
  st_vid << std::put_time(&tm,"%Y_%m_%d_%H_%M_%S") << ".log";
  bfp += st_vid.str();
  of_log = std::move(std::ofstream(bfp.string()));

  std::cout << __PRETTY_FUNCTION__ << '\n';}

void Logger_mod::b_stop(void *pt){
  of_log.close();
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

const char* Logger_mod::b_type_name(){ return typeid (this).name(); }

