#include "udp_sock_wrap.h"
#include <iostream>
#include <QNetworkDatagram>

#include "factory_morf.h"

#include <exception>

REGISTER_SERIALIZABLE(Udp_sock_wrap);

namespace  {
  unsigned  short udp_port = 4455;
}

Udp_sock_wrap::Udp_sock_wrap(QObject *parent) :
  QObject (parent)
{
  std::cout << __PRETTY_FUNCTION__ << "\n";
}

Udp_sock_wrap::~Udp_sock_wrap(){

  for (auto& kvp: map_serv.toStdMap()) {
      delete kvp.second;
    }
  std::cout << __PRETTY_FUNCTION__ << "\n";

}

void Udp_sock_wrap::b_start(void *arg)try{

  if(arg == nullptr)
    return;

  QString *st = static_cast<QString *>( arg );

  // проверить QString должно содержать число больше 0 но меньше 65535

  map_serv[*st] =  new QUdpSocket;

  if(map_serv[*st]->bind(QHostAddress::Any,  st->toUShort())){
      connect(map_serv[*st], &QUdpSocket::readyRead, this, &Udp_sock_wrap::readPendingDatagrams);
      std::cout << __PRETTY_FUNCTION__ << "\n";
    }else{
      std::cout << " No  binding udp socket \n";
    }

}catch (std::exception &ex) {
  std::cout << __FILE__ << " " << __LINE__ << " " << ex.what() << "\n";
}

void Udp_sock_wrap::b_stop(void *arg)try{

  if(arg == nullptr)
    return;

  QString *st = static_cast<QString *>( arg );

  disconnect(map_serv[*st], &QUdpSocket::readyRead, this, &Udp_sock_wrap::readPendingDatagrams);

}catch (std::exception &ex) {
  std::cout << __FILE__ << " " << __LINE__ << " " << ex.what() << "\n";
}

void Udp_sock_wrap::readPendingDatagrams(){

  QUdpSocket *us = static_cast<QUdpSocket*>(sender());

  while (us->hasPendingDatagrams()) {

      QNetworkDatagram datagram = us->receiveDatagram();

      // emit recv_udp_datagram(datagram);
      // 1. для каждого открытого порта сделать свой метод для парсинга принятых данных

      // 2. если принята строка  от смартфона android
      QString cmd = datagram.data();

      std::cout << __PRETTY_FUNCTION__ << " " << cmd.toStdString() << "\n";

      // точно такой же алгоритм в console_reader
      if(cmd.toStdString().find("modules") != std::string::npos){/// проверим сколько модулей загружено
          for (auto& kvp: map_obj ) {
              std::cout << "M : " << kvp.first << "\n";
            }
        } else {                                                  /// иначе передадим команду модулю
          try {
            QStringList str_list = cmd.split(QRegExp(" "));
            map_obj.at(str_list.takeFirst().toStdString())->b_apply(&cmd);
          } catch (std::exception & ex) {                         /// если ошибка такого модуля нет перехватим исключение
            std::cout  << __FILE__ << " " << __LINE__ << " " << ex.what() << "\n";
          }
        }

    }
  /// отправить сигнал тем кто на него подписан
}






//      QByteArray qbr;
//      qbr.append("Udp_sock_wrap::readPendingDatagrams");
//      udp_serv.writeDatagram(QNetworkDatagram(qbr));
