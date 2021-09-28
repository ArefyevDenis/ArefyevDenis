#include "udp_multiplexer.h"

#include <QByteArray>
#include <exception>
#include <QNetworkDatagram>

#include <common/logger.h>
#include <handler_datagram/handler_datagram.h>

#include <iostream>

namespace  {
    unsigned short b_port{31336};
}

Udp_server::Udp_server(QObject *parent) :
    QObject(parent)
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
}

Udp_server::~Udp_server()
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
}

bool Udp_server::add_bind(unsigned short port)
{
    auto ms = map_sock.insert({port,new QUdpSocket});
    if(ms.second){
        ms.first->second->bind(port);
        connect( ms.first->second, &QUdpSocket::readyRead, this, &Udp_server::received_datagram);
    }
    return ms.second;// была ли вставка
}

bool Udp_server::add_bind(unsigned short port,std::function<void (QNetworkDatagram&)> fn){
    auto ms = map_sock.insert({port,new QUdpSocket(this)});
    if(ms.second){
        auto ma = map_action.insert({port,fn});
        if(ma.second){
            ms.first->second->bind(port);
            connect( ms.first->second, &QUdpSocket::readyRead, this, &Udp_server::received_datagram);
        }
    }
    return ms.second;// была ли вставка
}

void Udp_server::received_datagram(){
    QUdpSocket* us = (QUdpSocket*)sender();
    try {
        while(us->hasPendingDatagrams()){
            QNetworkDatagram dt = us->receiveDatagram();
            int dp = dt.destinationPort();
            int sp = dt.senderPort();
            std::cout << "D port: " << dp << " S port: " << sp << '\n';
            map_action.at(dp)(dt);
        }
    } catch (std::exception &ex) {
        std::cout << __PRETTY_FUNCTION__ << ' ' << ex.what() << '\n';
    }
}

void Udp_server::datagram_received(QByteArray dt,QHostAddress ha,unsigned short port){

}

void Udp_server::send_datagram(QByteArray dt,QHostAddress ha,unsigned short port){
//    try {
//        auto it = map_sock.at(port);
//        it->writeDatagram(dt,ha,port);
//    } catch (std::exception &ex) {
//    }

}
