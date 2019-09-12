#include "base_factory.h"

#include <iostream>

std::map<std::string, Base_factory *> Base_factory::map_obj;

Base_factory::Base_factory( )//QObject* p) : QObject (p)
{}

Base_factory::~Base_factory() {
  //std::cout <<__PRETTY_FUNCTION__ << '\n';
}

/// все объекты знают всё друг о друге
void  Base_factory::set_obj(std::pair<std::string, Base_factory *> m_pair){
  map_obj.insert(m_pair);
}

///// все объекты знают всё друг о друге
//void  Base_factory::set_obj(std::map<std::string, Base_factory *> m_obj){
//  map_obj = m_obj;
//}
