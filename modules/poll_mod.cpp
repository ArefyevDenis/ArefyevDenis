#include "poll_mod.h"

#include <string>
#include <typeinfo>
#include <iostream>
#include <exception>
#include <ctime>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strstream>
#include "factory_morf.h"

REGISTER_SERIALIZABLE(Poll_mod);

namespace  {
  const std::string poll_mod = "<Poll_mod>"
                                  "<mod name=\"Poll_mod\"/>"
                                  "<devices>"
                                    "<dev name=\"/dev/fd_0\"/>"
                                    "<dev name=\"/dev/fd_1\"/>"
                                    "<dev name=\"/dev/fd_2\"/>"
                                  "</devices>"
                               "</Poll_mod>";

}

Poll_mod::Poll_mod() :
  pr_xml(std::string(abi::__cxa_demangle(typeid(*this).name(), nullptr, nullptr, nullptr) ))
{
  if(!pr_xml.load_xml()){
      pr_xml.create_xml(poll_mod);
      pr_xml.print_xml();
    }
}

Poll_mod::~Poll_mod(){
  b_stop(nullptr);
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

void Poll_mod::b_apply(void *pt){

  std::string *str{nullptr};

  if(pt != nullptr){
      str = static_cast<std::string *>(pt);

//      if(static_cast<double>(MAX_TIME) < std::difftime(std::time(nullptr),t)){
//          b_stop(nullptr);
//          b_start(nullptr);
//        }

    }

}

void Poll_mod::b_start(void *str){

  std::string *v_str = static_cast<std::string *>(str);


  if(auto fd = ::dup(STDIN_FILENO); -1 != fd){

      try {//
        std::string str_dev = pr_xml.get<std::string>("Poll_mod.devices.dev_out.<xmlattr>.name");
      } catch (std::exception & ex) {

      }

      vec_fd.push_back(pollfd());
      vec_fd.back().fd = fd;
      vec_fd.back().events = POLLIN;
      vec_fd.back().revents = 0;

      std::thread temp(&Poll_mod::loop_poll,this);

      std_thread = std::move(temp);

    }else{
      std::cout << __PRETTY_FUNCTION__ <<' '<< __LINE__ << '\n';
      std::terminate();
    }

  std::cout << __PRETTY_FUNCTION__ << '\n';

}

void Poll_mod::loop_poll(){

  unsigned char buff[2048];

  while(!b_stop_thread.load()){
      try {
        int ret = poll(&vec_fd.at(0),vec_fd.size(),1); /// Ждём событие
        switch (ret) {
          case -1:                                          /// ошибка
            break;
          case 0:                                           /// время истекло
            //std::cout << __PRETTY_FUNCTION__ << " time out\n";
            break;
          default:
            for (uint i_fd = 0; i_fd < vec_fd.size(); ++i_fd) {  /// проверка событий
                if((vec_fd[i_fd].revents & POLLIN) == POLLIN){
                    auto sz = read(vec_fd[i_fd].fd,buff,sizeof (buff));
                    std::cout << "< " << sz << " >\n";
                    vec_fd[i_fd].revents = 0;
                  }
              }
            break;
          }
      }catch (std::exception& ex) {
        std::cout << ex.what() << __FILE__ <<' '<< __LINE__ << '\n';
        std::terminate();
      }
    }

   std::cout << __PRETTY_FUNCTION__ << '\n';
}

void Poll_mod::b_stop(void *pt){
  std::cout << __PRETTY_FUNCTION__ << " 0\n";
  b_stop_thread.store(true);
  if(std_thread.joinable()){
      std::cout << __PRETTY_FUNCTION__ << " 1\n";
      std_thread.join();
    }
  std::cout << __PRETTY_FUNCTION__ << " 2\n";
}

const char* Poll_mod::b_type_name(){ return typeid (this).name(); }










//std::thread temp([this](){
//    while(!b_stop_thread.load()){
//        try {
//          int ret = poll(&vec_fd.at(0),vec_fd.size(),10000); /// Ждём событие
//          switch (ret) {
//            case -1:                                          /// ошибка
//              break;
//            case 0:                                           /// время истекло
//              break;
//            default:
//              for (uint i_fd=0; i_fd<vec_fd.size();++i_fd) {  /// проверка событий
//                  switch (vec_fd[i_fd].revents ){
//                      case POLLPRI: /// есть приоритетные данные
//                       /// если работаем с gpio
//                       /// lseek()
//                       /// read();
//                      break;
//                    case POLLIN: /// просто данные
//                      break;
//                      /// read();
//                    default:
//                      /// другие события
//                      break;
//                    }
//                }
//              break;
//            }
//        } catch (std::exception& ex) {
//          std::cout << ex.what() << __FILE__ <<' '<< __LINE__ << '\n';
//          std::terminate();
//        }
//      }
//    std::cout << __PRETTY_FUNCTION__ << '\n';
//  });
