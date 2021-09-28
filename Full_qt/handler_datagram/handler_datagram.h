#ifndef HANDLER_DATAGRAM_H
#define HANDLER_DATAGRAM_H

#include <QObject>

#include "base_handler.h"

class QNetworkDatagram;

class Handler_datagram :
        public QObject
{
    Q_OBJECT
public:
    explicit Handler_datagram(QObject *parent = nullptr);

    ~Handler_datagram () override;

    void operator ()(QNetworkDatagram&) ;

signals:

public slots:

};

class Handler_dt
{
public:
    explicit Handler_dt();

    Handler_dt(const Handler_dt&);
    Handler_dt( Handler_dt&&);
    Handler_dt& operator = (const Handler_dt&);
    Handler_dt& operator = (Handler_dt&&);

    ~Handler_dt ();

    void operator ()(QNetworkDatagram&) ;

};

#endif // HANDLER_DATAGRAM_H
