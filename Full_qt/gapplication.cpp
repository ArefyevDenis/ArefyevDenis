#include "gapplication.h"

#include <exception>
#include <common/logger.h>

#define DBG
#ifdef DBG
#include <iostream>
#include <sstream>
#define WHO()         std::printf(" %s %d\n",__PRETTY_FUNCTION__,__LINE__);
#define LOG(...)                                                              \
  do{                                                                         \
  std::stringstream logstream;  logstream << __VA_ARGS__;                   \
  std::printf("%s {{%s}}\n",__PRETTY_FUNCTION__, logstream.str().c_str() ); \
  }while(0)

#else
#define WHO()
#define LOG( ... )
#endif

GApplication::GApplication(int &argc, char **argv, int flag) :
  QApplication (argc,argv,flag)
{
  init();  WHO();
}

GApplication::~GApplication()
{
  WHO();
}

void GApplication::init()
try {
  WHO();
  connect(qApp,&QApplication::commitDataRequest, this, &GApplication::slot_commitDataRequest);
  connect(qApp,&QApplication::saveStateRequest, this, &GApplication::slot_saveStateRequest );
  mw_.showMaximized();
} catch(...) {
  WHO();
}

void GApplication::slot_commitDataRequest(QSessionManager &)
{
  WHO();
}

void GApplication::slot_saveStateRequest(QSessionManager &)
{
  WHO();
}
