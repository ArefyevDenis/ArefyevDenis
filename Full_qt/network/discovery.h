#ifndef DISCOVERY_H
#define DISCOVERY_H

#include <QObject>
#include <QTimer>
#include <QUdpSocket>

class Discovery :
        public QObject
{
    Q_OBJECT
public:
    explicit Discovery(QObject *parent = nullptr);

private:

    QUdpSocket  u_sock;
    QTimer      q_time;

signals:

public slots:

    void datagram_received(QByteArray dt,QHostAddress ha,unsigned short port);

    void send_datagram();

};

#endif // DISCOVERY_H
