#include "parser_args.h"

#include <vector>
#include <exception>
#include <iostream>

namespace argum {
  std::vector<std::string> v_str;
}

Parser_args::Parser_args()
{

}

Parser_args& Parser_args::instance()
{
  static Parser_args pa;
  return pa;
}

void Parser_args::parsing()
{
  for(int ix = 1,iy = 2; ix < argc_; ++ix,++iy){
      std::string s1(argv_[ix]);
      if(s1.find("-") != std::string::npos){
          std::string s2(++ix < argc_ ? argv_[ix] : "");
          map_argv[s1] = s2;
        }
    }
  for(int ix = 1,iy = 2; ix < argc_; ++ix,++iy){
      argum::v_str.push_back(argv_[ix]);
    }
}

void Parser_args::parsing_args(int argc, char *argv[])
{
  argc_ = argc;
  argv_ = argv;

  for(int ix = 1,iy = 2; ix < argc_; ++ix,++iy){
      std::string s1(argv_[ix]);
      if(s1.find("-") != std::string::npos){
          std::string s2(++ix < argc_ ? argv_[ix] : "");
          map_argv[s1] = s2;
        }
    }

  for(int ix = 1,iy = 2; ix < argc_; ++ix,++iy){
      argum::v_str.push_back(argv_[ix]);
    }
}

// 0 Надо вот так
// 1 заранее продумать список ключей -f --file --file=qwerty.txt или так -abc == -a -b -c
// 2 if( map_argv.find(argv[i]) == true) ключ валидный то сохраним его как std::string temp и continue:
// 3 if( map_argv.find(argv[i]) == false) то это не ключ, это параметр для предыдущего ключа добавим его к строке параметров
// 4 посмотреть как сделано в oprncv

void Parser_args::parsing_args(std::string&s_args)
{
  str_args_ = s_args;
  std::stringstream sstr{s_args};
  std::string arg,key;
  while(std::getline(sstr,arg,' ')){
      if(arg.find("-") != std::string::npos){
          key = arg;
          map_argv[arg] = "";
        }else{
          map_argv.at(key).append(arg+' ');
        }
    }
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

void Parser_args::set_args(int argc, char *argv[])
{
  argc_ = argc;
  argv_ = argv;
  parsing();
}
void Parser_args::set_args(std::string &s_args)
{
  str_args_ = s_args;
}

const std::string Parser_args::get_argv(const char* key) const
{
  auto iter = map_argv.find(key);
  if(iter != map_argv.end()){
      return iter->second;
    }
  return std::string("");
}
