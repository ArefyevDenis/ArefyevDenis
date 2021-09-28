#ifndef PARSER_ARGS_H
#define PARSER_ARGS_H

#include <string>
#include <sstream>
#include <map>

#define r_pars() Parser_args::instance()

class Parser_args
{
public:

   static Parser_args& instance() ;

   void set_args(int argc, char *argv[]);

   void set_args(std::string&);

   void parsing_args(int argc, char *argv[]);

   void parsing_args(std::string&);

   Parser_args(const Parser_args&)              = delete;
   Parser_args(Parser_args &&)                  = delete;
   Parser_args& operator = (const Parser_args&) = delete;
   Parser_args& operator = (Parser_args&&)      = delete;

   const std::string get_argv(const char* key) const ;

   template<typename TT>
   TT get_argv_t(const char* key)
   {
     TT tt;

     auto iter = map_argv.find(key);

     if(iter != map_argv.end()){
         std::stringstream ss_str(iter->second);
         ss_str >> tt;
         return tt;
       }

     return tt;
   }

private:

  Parser_args();

  void parsing();

private:

  int   argc_   {0};
  char  **argv_ {nullptr};

  std::string str_args_{""};

  std::map<std::string, std::string> map_argv;

};

#endif // PARSER_ARGS_H
