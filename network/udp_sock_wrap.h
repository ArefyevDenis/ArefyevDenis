#ifndef UDP_SOCK_WRAP_H
#define UDP_SOCK_WRAP_H

#include <QUdpSocket>
#include <QVector>
#include <QMap>

#include "base_factory.h"

class Udp_sock_wrap :
    public QObject,
    public Base_factory
{
  Q_OBJECT
public:

  explicit Udp_sock_wrap(QObject *parent = nullptr);

  Udp_sock_wrap(const Udp_sock_wrap&)               = delete;
  Udp_sock_wrap(Udp_sock_wrap&&)                    = delete;
  Udp_sock_wrap& operator = (const Udp_sock_wrap&)  = delete;
  Udp_sock_wrap& operator = (Udp_sock_wrap&&)       = delete;
  Udp_sock_wrap(std::initializer_list<int> il)      = delete;
  ~Udp_sock_wrap()                                   override;

  virtual void b_apply(void *)  override{}             ///применять, использовать
  virtual void b_start(void *)  override;
  virtual void b_stop(void *)   override;
  virtual const char* b_type_name() override{ return typeid (this).name(); }

private:

  QUdpSocket                  *udp_serv{nullptr};
  QVector<QUdpSocket*>        vec_serv;
  QMap<QString, QUdpSocket*>  map_serv;

signals:

public slots:
  void readPendingDatagrams();
};

#endif // UDP_SOCK_WRAP_H
