#include "encapsulate.h"

#include <QNetworkDatagram>
#include <iostream>

#include <common/logger.h>
#include <handler_datagram/handler_datagram.h>

Encapsulate::Encapsulate(QObject *parent) : QObject(parent)
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
    for (unsigned short i= 20000; i < 20100;++i) {
        um_.add_bind(i,[](QNetworkDatagram nd){
            std::cout << __FILE__ << ' ' << __LINE__ << '\n';
            int dp = nd.destinationPort();
            int sp = nd.senderPort();
            std::cout << "Dest port: " << dp << " Send port: " << sp << '\n';
        });
    }

    for (unsigned short i= 30000; i < 30005;++i) {
        um_.add_bind(i,Handler_dt());
    }

}

Encapsulate ::~Encapsulate()
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
}
