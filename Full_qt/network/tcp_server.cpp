#include "tcp_server.h"


Tcp_server::Tcp_server(QObject *parent) :
    QTcpServer (parent)
{
    connect(this,&QTcpServer::newConnection,this,&Tcp_server::new_connection);
}


Tcp_server::~Tcp_server(){}

void Tcp_server::add_listen(QHostAddress,unsigned short){}

void Tcp_server::add_listen(QHostAddress,unsigned short,std::function<void (QTcpSocket*)>){}

void Tcp_server::new_connection()
{
    QTcpSocket *tcp_sock = nextPendingConnection
            ();
}

//Tcp_server::Tcp_server(QObject *parent) :
//    QObject(parent)
//{
//}
