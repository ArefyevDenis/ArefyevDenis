#include "listen_std_out.h"

#include <iostream>

#include <fcntl.h>
#include <unistd.h>

#include <QTextStream>

#include "factory_morf.h"

#include "QException"
#include "stdexcept"

//REGISTER_SERIALIZABLE(Listen_std_in);

REGISTER_SERIALIZABLE(Console_Reader);

#define dbg() std::cout << __PRETTY_FUNCTION__ << "\n";


Console_Reader::Console_Reader(QObject *parent) :
  QObject(parent),
  notifier(STDIN_FILENO, QSocketNotifier::Read)
{
  dbg();
  connect(&notifier, SIGNAL(activated(int)), this, SLOT(text()));
}

void Console_Reader::text()
{
  QTextStream qin(stdin);
  QString line = qin.readLine();
  std::cout << __PRETTY_FUNCTION__ << " " << line.toStdString() << "\n";

  emit textReceived(line);

  // Console_Reader то же модуль его бы в числе первых загрузить
  if(line.toStdString().find("modules") != std::string::npos){/// проверим сколько модулей загружено
      for (auto& kvp: map_obj ) {
          std::cout << "M : " << kvp.first << "\n";
        }
    } else {                                                  /// иначе передадим команду модулю
      try {
        QStringList str_list = line.split(QRegExp(" "));
        map_obj.at(str_list.takeFirst().toStdString())->b_apply(&line);
      } catch (std::exception & ex) {                         /// если ошибка такого модуля нет перехватим исключение
        std::cout  << __FILE__ << " " << __LINE__ << " " << ex.what() << "\n";
      }
    }

}









//==================================================================================================//



Listen_std_in::Listen_std_in(QObject *pt):
  QObject (pt)
{
  dbg()
}

Listen_std_in::~Listen_std_in(){  dbg() }


void Listen_std_in::b_start(void *arg){
  dbg();
  if(arg != nullptr){}
  bool res = fff.open(::dup(STDOUT_FILENO),QIODevice::ReadWrite);
  std::cout << " open /dev/stdout = " << res << " \n";
  this->connect(&fff,SIGNAL(readyRead()), this, SLOT(read_from_std_in()));
}

void Listen_std_in::b_stop(void *arg){
  if(arg != nullptr){}
  this->disconnect(&fff,SIGNAL(readyRead()), this, SLOT(read_from_std_in()));
}

void Listen_std_in::read_from_std_in(){
  dbg();
  QByteArray qbr = fff.readAll();
  std::cout << "[ " << QString(qbr).toStdString() << "]\n";
}

//==================================================================================================//


//Joystick::Joystick(QObject *parent)
//   : QObject(parent)
//{
//    auto file = new QFile();
//    file->setFileName(fileName);
//    if( !file->exists() ){
//        qWarning("file does not exist");
//        return;
//    }

//    fd = open(fileName.toUtf8().data(), O_RDONLY|O_NONBLOCK);
//    if( fd==-1 ){
//        qWarning("can not open file");
//        return;
//    }

//    notifier = new QSocketNotifier( fd, QSocketNotifier::Read, this);

//    connect( notifier, &QSocketNotifier::activated, this, &Joystick::handle_readNotification );
//}

//Joystick::~Joystick()
//{
//    if( fd>=0 ){
//        close(fd);
//    }
//    if(notifier!=nullptr)
//      delete notifier;
//}

//void
//Joystick::handle_readNotification(int /*socket*/)
//{
////    struct js_event buf;
////    while( read(fd,&buf,sizeof(buf))>0 ){
////        switch (buf.type) {
////        case JS_EVENT_BUTTON:
////            emit buttonPressed(buf.number, buf.value);
////            break;
////        case JS_EVENT_AXIS:
////            emit axisMoved(buf.number, buf.value);
////            break;
////        }
////    }
//}
