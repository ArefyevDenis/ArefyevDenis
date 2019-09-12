#include "producer_stdout.h"

#include <iostream>
#include "factory_morf.h"

REGISTER_SERIALIZABLE(Producer_stdout)

Producer_stdout::Producer_stdout()
{

}

Producer_stdout::~Producer_stdout(){std::cout << __PRETTY_FUNCTION__ << '\n'; }

void Producer_stdout::b_apply(void *){

}

void Producer_stdout::b_start(void *) {

  std::thread temp([this](){
      std::string str;
      while(!b_stop_thread.load()){
//          while(std::cin >> str){
//              std::cout << str << '\n';
//              for (auto kvp: map_obj) {
//                  kvp.second->b_apply(nullptr);
//                }
//            }
        }
    });
  std_thread = std::move(temp);
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

void Producer_stdout::b_stop(void *)  {
  b_stop_thread.store(true);
  if(std_thread.joinable())
    std_thread.join();
}

const char* Producer_stdout::b_type_name(){ return typeid (this).name(); }
