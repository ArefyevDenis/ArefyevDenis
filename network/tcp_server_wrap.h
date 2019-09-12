#ifndef TCP_SERVER_WRAP_H
#define TCP_SERVER_WRAP_H

#include <QTcpServer>
#include <QVector>

#include "base_factory.h"

class QTcpSocket;

class Tcp_server_wrap :
    public QTcpServer,
    public Base_factory
{
  Q_OBJECT
public:
  explicit Tcp_server_wrap(QObject *parent = nullptr);

  Tcp_server_wrap(const Tcp_server_wrap&)               = delete;
  Tcp_server_wrap(Tcp_server_wrap&&)                    = delete;
  Tcp_server_wrap& operator = (const Tcp_server_wrap&)  = delete;
  Tcp_server_wrap& operator = (Tcp_server_wrap&&)       = delete;
  Tcp_server_wrap(std::initializer_list<int> il)        = delete;
  ~Tcp_server_wrap()                                    override;

  QVector<QTcpSocket *> vec_sock; // отсерверный клиент

  void sv_start(QString str);
  void sv_stop();

  virtual void b_apply(void *)  override{}             ///применять, использовать
  virtual void b_start(void *)  override;
  virtual void b_stop(void *)   override;
  virtual const char* b_type_name() override{ return typeid (this).name(); }

signals:

public slots:

  void read_data();
  void slot_new_user();
  void slot_del_user();
  void slot_accept_error(QAbstractSocket::SocketError);

};

#endif // TCP_SERVER_WRAP_H
