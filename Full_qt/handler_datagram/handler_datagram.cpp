#include "handler_datagram.h"

#include <common/logger.h>

#include <vector>

Handler_datagram::Handler_datagram(QObject *parent) :
    QObject(parent)
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
}

Handler_datagram::~Handler_datagram ()
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
}

void Handler_datagram::operator ()(QNetworkDatagram&)
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
}



Handler_dt::Handler_dt()
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
}

Handler_dt::Handler_dt(const Handler_dt& hdt)
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
    *this = hdt;            //operator = (const Handler_dt&)
}

Handler_dt::Handler_dt( Handler_dt&& hdt)
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
    *this = std::move(hdt); //operator = (const Handler_dt&&)
}

Handler_dt& Handler_dt::operator = (const Handler_dt&hdt)
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
    if(this != &hdt){
      }
   return *this;
}
Handler_dt& Handler_dt::operator = (Handler_dt&&hdt)
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
    if(this != &hdt){

    }
    return *this;
}

Handler_dt::~Handler_dt ()
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
}

void Handler_dt::operator ()(QNetworkDatagram&)
{
    LOG_DEBUG(nullptr, __PRETTY_FUNCTION__);
}
