#ifndef EXAMPLE_XML_H
#define EXAMPLE_XML_H

#include <string>
#include <typeinfo>
#include <iostream> /// после отладки удалить
#include <cxxabi.h>
#include <parsser_xml.h>
// если xml файлов нет создадим их
//
// статический полиморфизм

template<class CLASS>
class Example_XML
{
public:
  Example_XML(){
    str_derived = std::string(abi::__cxa_demangle(typeid (CLASS).name(), nullptr, nullptr, nullptr) );

    Parsser_XML p_xaml(str_derived);

    std::cout << "<" << str_derived  << ">\n";  /// после отладки удалить

  }
private:

  std::string str_derived{""};

};

#endif // EXAMPLE_XML_H
