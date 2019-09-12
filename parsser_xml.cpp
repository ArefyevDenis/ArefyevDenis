#include "parsser_xml.h"

#include <boost/foreach.hpp>
#include <experimental/filesystem>
#include <iostream>
#include <exception>
#include <string>
#include <ostream>

#include <unistd.h>
#include <stdio.h>
#include <linux/limits.h>


Parsser_XML::Parsser_XML(std::string p_xml) :
  name_xml(p_xml)
{
  name_xml += ".xml";

  bfp = boost::filesystem::current_path();

  bfp += "/config/";

  if(!boost::filesystem::exists(bfp)){                /// если такой директории нет создадим
      if(!boost::filesystem::create_directory(bfp)){  /// если не получилось сразу завалим программу
          std::terminate();                           /// на этапе отладки чем громче упадёт тем лучше.
        }
    }

  bfp += name_xml;

  std::cout << __PRETTY_FUNCTION__ << '\n';
}

Parsser_XML::~Parsser_XML(){
  save_xml();
}

void Parsser_XML::create_xml(std::string str){

  is << str;                ///подгрузим stringstream  это основа для xml файла
  boost::property_tree::read_xml( is, pt1, boost::property_tree::xml_parser::trim_whitespace);

}

bool Parsser_XML::load_xml(std::string str){                        /// полный путь к файлу который будем читать
  try{
    boost::filesystem::path m_path_xml = str.empty() ? bfp : str ;  /// выбираем какой файл читать
    if(!boost::filesystem::exists(m_path_xml))                      /// если файл  не существует сразу выходим
      return false;

    boost::property_tree::read_xml( m_path_xml.string(), pt1, boost::property_tree::xml_parser::trim_whitespace);
    print_xml();
    return true;

  }catch(std::exception &e) {
    std::cout << e.what() << __FILE__ <<__LINE__ << "\n";
    std::terminate();
  }
}

void Parsser_XML::save_xml(std::string str){                          /// путь к файлу который будем читать
  try{
    boost::filesystem::path m_path_xml = str.empty() ? bfp : str ; /// выбираем куда сохранять
    boost::property_tree::xml_writer_settings<std::string> w( '\t', 1);
    boost::property_tree::write_xml(m_path_xml.string(), pt1, std::locale(), w);
  }catch(std::exception &e) {
    std::cout << "Error: " << e.what() << "\n";
  }
}

void  Parsser_XML::recursive_print(boost::property_tree::ptree const& pt){
    using boost::property_tree::ptree;
    ptree::const_iterator end = pt.end();
    for (auto it = pt.begin(); it != end; ++it) {
        if(it->second.empty()){
            std::stringstream ss;
            deep_xml.push_back(it->first);
            //std::copy(deep_xml.begin(),deep_xml.end(),std::ostream_iterator<std::string> {std::cout, "."});
            std::copy(deep_xml.begin(),deep_xml.end(),std::ostream_iterator<std::string> {ss, "."});
            //std::cout /*<< it->first*/ << ": " << it->second.get_value<std::string>() << std::endl;
            std::cout << ss.str() << ": " << it->second.get_value<std::string>() << std::endl;
            map_xml[ss.str()] = it->second.get_value<std::string>();
            deep_xml.pop_back();
        }else{
           deep_xml.push_back(it->first);
           recursive_print(it->second);
           deep_xml.pop_back();
        }
    }
}

void Parsser_XML::print_xml(std::string str){
    try{
        if(str.empty()){
            recursive_print(pt1);
        }else{
            boost::property_tree::read_xml( str, pt1);
            recursive_print(pt1);
        }
    }catch(std::exception &e) {
        std::cout << "print_xml: " << e.what() << "\n";
    }
}

std::map<std::string, std::string> Parsser_XML::get_map_xml(){
    return map_xml;
}






















//void Parsser_XML::save_xml(std::string str){ /// путь к файлу который будем читать
//    try{
//       boost::filesystem::path m_path_xml = str.empty() ? bfp : str ; /// выбираем куда сохранять

//        boost::property_tree::xml_writer_settings<std::string> w( '\t', 1);
//        if(str.empty()){
//            boost::property_tree::write_xml( bfp.string() , pt1, std::locale(), w);
//        }else{
//            boost::property_tree::write_xml( str, pt1, std::locale(), w);
//        }
//    }catch(std::exception &e) {
//        std::cout << "Error: " << e.what() << "\n";
//    }
//}

//void Parsser_XML::load_xml(std::string str){
//    try{
//        if(str.empty()){
//            boost::filesystem::path bfp{boost::filesystem::current_path()};
//            bfp += "/" + path_xml;
//            if( boost::filesystem::exists(bfp)){ /// если файл существует прочитаем его
//                std::cout << bfp.string() << "\n";
//                boost::property_tree::read_xml( path_xml, pt1, boost::property_tree::xml_parser::trim_whitespace);
//              }else{                            /// если нет подгрузим stringstream
//                 is << base_xml;                /// это основа для xml файла
//                 std::cout << is.str() << "\n";
//                 boost::property_tree::read_xml( is, pt1, boost::property_tree::xml_parser::trim_whitespace);
//              }
//        }else{
//            boost::property_tree::read_xml( str, pt1);
//        }
//        print_xml();
//    }catch(std::exception &e) {
//        std::cout << e.what() << __FILE__ <<__LINE__ << "\n";
//        std::terminate();
//    }
//}

//  char cwd[PATH_MAX];
//  if (getcwd(cwd, sizeof(cwd)) != nullptr){
//      curent_path.append(cwd);
//      std::cout <<" < "<< curent_path << " >\n";
//    }
