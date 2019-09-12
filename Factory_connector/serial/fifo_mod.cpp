#include "fifo_mod.h"

#include <iostream>

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <cstring>

#include <QTextStream>

#include <chrono>

#include "factory_morf.h"

REGISTER_SERIALIZABLE(Fifo_mod);
#define dbg() std::cout << __PRETTY_FUNCTION__ << "\n";

Fifo_mod::Fifo_mod(QObject *pr) :
  QObject (pr)
{
  dbg();

  /*


    sudo mkfifo /dev/tty-from-bpla-to-pix
    sudo chmod 666 /dev/tty-from-bpla-to-pix
    sudo ln -sn /dev/tty-from-bpla-to-pix /dev/serial/by-id/tty-from-bpla-to-pix

    sudo mkfifo /dev/tty-from-pix-to-bpla
    sudo chmod 666 /dev/tty-from-pix-to-bpla
    sudo ln -sn /dev/tty-from-pix-to-bpla /dev/serial/by-id/tty-from-pix-to-bpla

    sudo ls -l /dev/serial/by-id/

// --------------------------------------- проверка ---------------------------------------//
//  denis@denis-PC:~/REPO/mbuk/vkbpla/bpla/build_proxy$ ls -l /dev/serial/by-id/
//  итого 0
//  lrwxrwxrwx 1 root root 25 авг 22 11:56 tty-from-bpla-to-pix -> /dev/tty-from-bpla-to-pix
//  lrwxrwxrwx 1 root root 25 авг 22 12:03 tty-from-pix-to-bpla -> /dev/tty-from-pix-to-bpla
//  lrwxrwxrwx 1 root root 13 авг 22 11:07 usb-1a86_USB2.0-Serial-if00-port0 -> ../../ttyUSB0
//  lrwxrwxrwx 1 root root 13 авг 22 11:07 usb-3D_Robotics_PX4_FMU_v2.x_0-if00 -> ../../ttyACM0
// --------------------------------------- проверка ---------------------------------------//

  */


}

Fifo_mod::~Fifo_mod(){

  for (auto& kvp : vec_fifo) {
      if(kvp != nullptr){
          kvp->close();
          delete kvp;
        }
    }

  b_stop(nullptr);

  dbg();
}

void Fifo_mod::b_apply(void* ptr)  {

  if(ptr != nullptr){
      QByteArray *qba = static_cast<QByteArray *>(ptr);
      from_pix_to_bpla(qba);
    }

}

void Fifo_mod::b_start(void *ptr)  {

  if(ptr == nullptr)
    return;

  // имена открываемых каналов передаём один раз
  QVector<QString> *v_fifo = static_cast< QVector<QString> *>( ptr ) ;

  for (auto &kvp: *v_fifo ) {

      vec_fifo.push_back(new QFile());
      vec_fifo.back()->setFileName(kvp);
      if( !vec_fifo.back()->exists() ){
          qWarning("file does not exist");
          return;
        }

      // файловый дескриптор открываемого канала
      vec_fd.push_back(::open(kvp.toUtf8().data(), O_RDWR|O_NONBLOCK));
      if( vec_fd.back()==-1 ){
          std::cout << __PRETTY_FUNCTION__ << " " << "No Open " << kvp.toUtf8().data() << "\n";
          return;
        }

      if(kvp.toStdString().find("from-bpla-to-pix") != std::string::npos ){
          // будем следить за событиями в этом канале
          notifier_1 = new mQSocketNotifier(vec_fd.back(),  QSocketNotifier::Read,  this);
          connect( notifier_1, &QSocketNotifier::activated, this,  &Fifo_mod::from_bpla_to_pix /*, Qt::BlockingQueuedConnection*/ );
        }
    }
}

void Fifo_mod::b_stop(void *)   {
  for (auto &kvp: vec_fd ) {
      close(kvp);
    }
}


namespace  {
  std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
}

void Fifo_mod::from_bpla_to_pix(int fd){

  // читаем из бпла и пишем в пикс

  unsigned char buf[2048];

  //int readret = vec_fifo.at(0)->read((char*)buf, sizeof (buf));

  while(1){
      ssize_t sz = ::read(fd,&buf,sizeof(buf));

//      std::cout << "Printing took " << std::chrono::duration_cast<std::chrono::microseconds>( std::chrono::steady_clock::now() - start).count() << "us.\n";
//      start = std::chrono::steady_clock::now();
//      notifier_1->setEnabled(false);
//      notifier_1->setEnabled(true);

      if(sz <= 0)
        break;

      for(uint ix=0;ix < sz; ix++){  std::printf("%4x%c", buf[ix]," \n"[ix%16 == 15]);  }  std::printf("\n");

    }

  std::memset(buf,0,sizeof (buf));

  //dbg();

}


bool Fifo_mod::event(QEvent *evt){

  this->QObject::event(evt);
  std::cout <<__PRETTY_FUNCTION__ << " " << evt->type() << " \n";
  return true;

}

void Fifo_mod::from_pix_to_bpla(QByteArray* p){

  // читаем из пикса и пишем в канал бпла
  // читаем из приоритетного(основного) пикса

  // это плохо но пока
  // нулевой (0) канал читает из бпла
  // первый  (1) канал пишет в бпла

  if(p != nullptr){
      vec_fifo.at(1)->write(*p);
    }

  //dbg();
}







/*


  sudo mkfifo /dev/tty-from-bpla-to-pix
  sudo chmod 666 /dev/tty-from-bpla-to-pix
  sudo ln -sn /dev/tty-from-bpla-to-pix /dev/serial/by-id/tty-from-bpla-to-pix

  sudo mkfifo /dev/tty-from-pix-to-bpla
  sudo chmod 666 /dev/tty-from-pix-to-bpla
  sudo ln -sn /dev/tty-from-pix-to-bpla /dev/serial/by-id/tty-from-pix-to-bpla

  sudo ls -l /dev/serial/by-id/



*/

