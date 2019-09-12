#ifndef TCP_SOCK_WRAP_H
#define TCP_SOCK_WRAP_H

#include <QTcpSocket>
#include <QVector>
#include <QTimer>

class Tcp_sock_wrap :
    public QTcpSocket
{
  Q_OBJECT
public:
  explicit Tcp_sock_wrap(QObject *parent = nullptr);

  Tcp_sock_wrap(const Tcp_sock_wrap&)               = delete;
  Tcp_sock_wrap(Tcp_sock_wrap&&)                    = delete;
  Tcp_sock_wrap& operator = (const Tcp_sock_wrap&)  = delete;
  Tcp_sock_wrap& operator = (Tcp_sock_wrap&&)       = delete;
  Tcp_sock_wrap(std::initializer_list<int> il)      = delete;
  ~Tcp_sock_wrap()                                  override;

  QTimer tmr;

signals:

public slots:  

  void slot_connected();

  void slot_read_data();

  void slot_error(QAbstractSocket::SocketError);

  void slot_write_Timeout();

};

#endif // TCP_SOCK_WRAP_H
