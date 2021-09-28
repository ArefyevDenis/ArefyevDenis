#include "test_factory.h"


#include<dbg.h>
#include <factory.h>
#include <QObject>
#include <file_server.h>

//namespace TFC {

  class_instance( AA );

  AA::AA(QWidget *ptr) :
    QWidget(ptr)
  {
    p_fs = dynamic_cast<File_server*>(ptr);
    who();
  }

  AA::~AA()
  {
    who();
  }

//}
