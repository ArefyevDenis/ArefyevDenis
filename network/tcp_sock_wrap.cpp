#include "tcp_sock_wrap.h"

#include <iostream>

namespace  {

  QString         ip_str = "127.0.0.1";
  unsigned short  port= 33333;
  QByteArray qba;

  int step = 0;

}

Tcp_sock_wrap::Tcp_sock_wrap(QObject *parent ):
  QTcpSocket (parent)
{
  this->connectToHost(ip_str,port);
  connect(this, SIGNAL(connected()),this,SLOT(slot_connected()));
  connect(&tmr, SIGNAL(timeout()), SLOT(slot_write_Timeout()));
  tmr.start(1000);
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

Tcp_sock_wrap::~Tcp_sock_wrap(){
  this->disconnectFromHost();
  tmr.stop();
}

void Tcp_sock_wrap::slot_connected(){

  connect(this, SIGNAL(readyRead()),this,SLOT(slot_read_data()));
  connect(this, SIGNAL(error()),this,SLOT(slot_error()));

  std::cout << __PRETTY_FUNCTION__ << "\n";
}

void Tcp_sock_wrap::slot_read_data(){

  QTcpSocket *ts = (QTcpSocket*) sender();

  qba = ts->readAll();

  std::cout << QString( qba ).toStdString() << "\n";

}

void Tcp_sock_wrap::slot_error(QAbstractSocket::SocketError er){
  std::cout << "socket error: " << er << " \n";
  switch (er) {
    //    case QAbstractSocket::ConnectionRefusedError:
    //      break;
    default:
      std::cout << " Server error = " << er << "\n";
      break;
    }
}

void Tcp_sock_wrap::slot_write_Timeout(){

  QString qst("send data");

  qst.append(QString(" %1 ").arg(step++));

  write( QString( qst ).toStdString().c_str() )  ;
}
