#ifndef DBG_H
#define DBG_H

#include <sstream>
#include <iostream>

#ifdef MDBG
  #define who()         std::printf(" %s \n",__PRETTY_FUNCTION__);
  #define LOG(...)                                                              \
    do{                                                                         \
      std::stringstream logstream;  logstream << __VA_ARGS__;                   \
      std::printf("%s {{%s}}\n",__PRETTY_FUNCTION__, logstream.str().c_str() ); \
    }while(0)

#else
  #define who()
  #define LOG(...)
#endif

#endif
