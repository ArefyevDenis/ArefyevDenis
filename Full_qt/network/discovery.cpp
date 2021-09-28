#include "discovery.h"

#include <QByteArray>

namespace  {
    unsigned short b_port{31337};
}

Discovery::Discovery(QObject *parent) :
    QObject(parent)
{
    u_sock.bind(b_port);

    //connect(&u_sock, &QUdpSocket::readyRead, this, &Discovery::datagram_received);

    connect(&q_time, &QTimer::timeout, this, &Discovery::send_datagram);

}

void Discovery::datagram_received(QByteArray dt,QHostAddress ha,unsigned short port){
    u_sock.writeDatagram(dt,ha,port);
}

void Discovery::send_datagram(){

}
