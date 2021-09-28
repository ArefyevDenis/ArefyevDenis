#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include <functional>
class Tcp_server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Tcp_server(QObject *parent = nullptr);

    ~Tcp_server()override;

    void add_listen(QHostAddress,unsigned short);
    void add_listen(QHostAddress,unsigned short,std::function<void (QTcpSocket*)>);

private:

signals:

public slots:

private slots:

    void new_connection();

};

//class Tcp_server : public QObject
//{
//    Q_OBJECT
//public:
//    explicit Tcp_server(QObject *parent = nullptr);

//private:

//    QTcpServer ts_;

//signals:

//public slots:


//};

#endif // TCP_SERVER_H
