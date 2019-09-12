#include "modules.h"

#include <iostream>
#include <typeinfo>
#include <factory_morf.h>

#include <opencv2/core/cvstd.hpp>
#include <opencv2/opencv.hpp>

REGISTER_SERIALIZABLE(Mod_a);
Mod_a::Mod_a()  { std::cout << __PRETTY_FUNCTION__ << '\n'; }
Mod_a::~Mod_a() { std::cout << __PRETTY_FUNCTION__ << '\n'; }

void Mod_a::b_apply(void *pt){

  cv::Mat* mt = static_cast<cv::Mat*>(pt);
  if(!mt->empty()){
      //cv::imshow(typeid (this).name(),*mt);
      std::string str; str += std::string( typeid (this).name()) ;
      map_obj.at("Logger_mod")->b_apply(&str);
    }

}

void Mod_a::b_start(void *) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
const char* Mod_a::b_type_name(){ return typeid (this).name(); }

REGISTER_SERIALIZABLE(Mod_b);
Mod_b::Mod_b()  { std::cout << __PRETTY_FUNCTION__ << '\n'; }
Mod_b::~Mod_b() { std::cout << __PRETTY_FUNCTION__ << '\n'; }

void Mod_b::b_apply(void *pt){
  cv::Mat* mt = static_cast<cv::Mat*>(pt);
  if(!mt->empty()){
      //cv::imshow(typeid (this).name(),*mt);
      std::string str; str += std::string( typeid (this).name()) ;
      map_obj.at("Logger_mod")->b_apply(&str);
    }
}

void Mod_b::b_start(void *) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
const char* Mod_b::b_type_name(){ return typeid (this).name(); }

REGISTER_SERIALIZABLE(Mod_c);
Mod_c::Mod_c()  { std::cout << __PRETTY_FUNCTION__ << '\n'; }
Mod_c::~Mod_c() { std::cout << __PRETTY_FUNCTION__ << '\n'; }

void Mod_c::b_apply(void *pt){
  cv::Mat* mt = static_cast<cv::Mat*>(pt);
  if(!mt->empty()){
     // cv::imshow(typeid (this).name(),*mt);
      std::string str; str += std::string( typeid (this).name()) ;
      map_obj.at("Logger_mod")->b_apply(&str);
    }
}

void Mod_c::b_start(void *) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
const char* Mod_c::b_type_name(){ return typeid (this).name(); }

