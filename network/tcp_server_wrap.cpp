#include "tcp_server_wrap.h"

#include <iostream>

#include <QTcpSocket>
#include <QString>

#include "factory_morf.h"

namespace  {
  unsigned short tcp_port =  33333;
}

REGISTER_SERIALIZABLE(Tcp_server_wrap);

Tcp_server_wrap::Tcp_server_wrap(QObject *parent) :
  QTcpServer (parent)
{
  std::cout << __PRETTY_FUNCTION__ << "\n";
}


Tcp_server_wrap::~Tcp_server_wrap(){std::cout << __PRETTY_FUNCTION__ << "\n";}

void Tcp_server_wrap::sv_start(QString str){
  if(listen(QHostAddress::Any,tcp_port )){
      connect(this, SIGNAL(newConnection()), this, SLOT(slot_new_user()));
      connect(this, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(slot_accept_error(QAbstractSocket::SocketError)));
      std::cout << " Server opening \n";
    }
}


void Tcp_server_wrap::sv_stop(){}


void Tcp_server_wrap::b_start(void *arg) {

  sv_start((arg!=nullptr) ? *static_cast<QString*>(arg) : QString("111"));

}

void Tcp_server_wrap::b_stop(void *arg)  {
  if(arg!=nullptr){}
  sv_stop();
}


void Tcp_server_wrap::slot_accept_error(QAbstractSocket::SocketError err){
  std::cout << "socket error: " << err << " \n";
  switch (err) {
    //case QAbstractSocket::ConnectionRefusedError:
    //break;
    default:
      std::cout << " Server error = " << err << "\n";
      break;
    }
}

void Tcp_server_wrap::slot_new_user(){

  QTcpSocket *ts = nextPendingConnection();

  connect(ts, SIGNAL(disconnected()),this,SLOT(slot_del_user()));

  connect(ts, SIGNAL(readyRead()),this,SLOT(read_data()));

  vec_sock.push_back(ts);

  std::cout << __PRETTY_FUNCTION__ << "\n";
}

void Tcp_server_wrap::slot_del_user(){

  QTcpSocket *ts = (QTcpSocket*)sender();

  vec_sock.erase(std::remove_if(vec_sock.begin(), vec_sock.end(), [ts](QTcpSocket *p) { return p == ts; }), vec_sock.end());

  std::cout << __PRETTY_FUNCTION__ << "\n";

}

void Tcp_server_wrap::read_data(){

  QTcpSocket *ts = (QTcpSocket*)sender();

  QByteArray qba = ts->readAll();

  std::cout << QString( qba ).toStdString() << "\n";

  ts->write( QString( qba ).toLower().toStdString().c_str() );



}
