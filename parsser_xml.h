#ifndef PARSSER_XML_H
#define PARSSER_XML_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem.hpp>
#include <string>
#include <stdio.h>
#include <map>

class Parsser_XML
{
public:
    Parsser_XML(std::string p_xml);/// пердаём файл который будем парсить

    Parsser_XML(const Parsser_XML&)                 = delete;
    Parsser_XML(Parsser_XML&& )                     = delete;
    Parsser_XML& operator = (const Parsser_XML& )   = delete;
    Parsser_XML& operator = (Parsser_XML&& )        = delete;

    ~Parsser_XML();

    void create_xml(std::string str );
    bool load_xml(std::string str = "");  /// при необходимости можно парсить новый файл
    void save_xml(std::string str = "");  /// сохраним файл
    void print_xml(std::string str = ""); /// напечатаем файл

    template<typename TT>
    TT get(std::string str){        /// извлечь из дерева необходимый параметр
        return pt1.get<TT>(str);
    }

    template<typename TT>
    TT set(TT str){                 /// параметр
        return pt1.add<TT>(str);
    }

    std::map<std::string, std::string> get_map_xml(); //

private:

    void  recursive_print(boost::property_tree::ptree const& pt); /// в связке с print_xml печать всего файла

    boost::filesystem::path             bfp;          /// путь по которому сохраняется файл
    std::string                         name_xml{""}; /// имя файла конфигурации
    boost::property_tree::ptree         pt1;          /// дерево свойств
    std::vector<std::string>            deep_xml;     ///
    std::map<std::string, std::string>  map_xml;      ///

    std::stringstream is;

};

#endif // PARSSER_XML_H
