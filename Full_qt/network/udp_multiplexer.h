#ifndef Udp_server_H
#define Udp_server_H

#include <QObject>
#include <QTimer>
#include <QUdpSocket>

#include <map>

class QNetworkDatagram;

class Udp_server :
        public QObject
{
    Q_OBJECT
public:
    explicit Udp_server(QObject *parent = nullptr);

    ~Udp_server()override;

    bool add_bind(unsigned short);
    bool add_bind(unsigned short,std::function<void (QNetworkDatagram&)>);

private:

    QUdpSocket  u_sock;
    QTimer      q_time;

    std::map<unsigned short,QUdpSocket*> map_sock;
    std::map<unsigned short,std::function<void (QNetworkDatagram&)>> map_action;


signals:

public slots:

    void received_datagram();

    void datagram_received(QByteArray dt,QHostAddress ha,unsigned short port);

    void send_datagram(QByteArray dt,QHostAddress ha,unsigned short port);

};

#endif // Udp_server_H
