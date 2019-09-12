#ifndef LOGGER_MOD_H
#define LOGGER_MOD_H

#include <base_factory.h>
#include <logger.h>
#include "example_xml.h"
#include "parsser_xml.h"

#include <fstream>

class Logger_mod :
    public Base_factory  //,    //public Example_XML<Logger_mod>
{
  enum{MAX_TIME = 120};
public:
  Logger_mod();

  ~Logger_mod()                      ;

  virtual void b_apply(void *)               override;
  virtual void b_start(void *)               override;
  virtual void b_stop(void *)                override;
  inline virtual const char* b_type_name()   override;

private:

  Parsser_XML pr_xml;

  boost::filesystem::path             bfp;          /// путь по которому сохраняется файл
  std::ofstream of_log;

  Logger lg;

  std::time_t t;
  std::tm tm;

};

#endif // LOGGER_MOD_H
