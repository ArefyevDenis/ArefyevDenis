#include "signal_handler.h"
#include <QCoreApplication>
#include<csignal>
#include "common/logger.h"

Signal_handler::Signal_handler(QObject *parent) : QObject(parent)
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
    ::signal(SIGINT,    &Signal_handler::exitQt);
    ::signal(SIGTERM,   &Signal_handler::exitQt);
    ::signal(SIGABRT,   &Signal_handler::exitQt);
}

Signal_handler::Signal_handler(std::initializer_list<int> il)
{
    for (auto kvs: il ) {
        ::signal(kvs,&Signal_handler::exitQt);
    }
}

Signal_handler::~Signal_handler()
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

void Signal_handler::exitQt(int sig)
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
    QCoreApplication::exit(0);
}
