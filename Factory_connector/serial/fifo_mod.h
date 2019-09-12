#ifndef FIFO_MOD_H
#define FIFO_MOD_H

#include <QSocketNotifier>
#include <QObject>
#include <QVector>
#include <QString>
#include <QMap>
#include <QFile>

#include "base_factory.h"

#include <QtCore/qcoreevent.h>
#include <iostream>

class mQSocketNotifier :
    public QSocketNotifier
{
public:
  mQSocketNotifier(qintptr socket, Type tt, QObject *parent = nullptr) :
    QSocketNotifier(socket,tt,parent)
  { std::cout << __PRETTY_FUNCTION__ << "\n"; }

  ~mQSocketNotifier() override = default;

  bool event(QEvent *ev) override {
    std::cout << __PRETTY_FUNCTION__ << " " << ev->type();
    QSocketNotifier::event(ev);
    return true;
  }
};


class Fifo_mod :
    public QObject,
    public Base_factory
{
public:

  explicit Fifo_mod(QObject *pr = nullptr);

  ~Fifo_mod() override ;

  virtual void b_apply(void *)  override;
  virtual void b_start(void *)  override;
  virtual void b_stop(void *)   override;
  virtual const char* b_type_name() override{ return typeid (this).name(); }

private:

  QVector<QFile*>       vec_fifo;
  QVector<int>          vec_fd;

  mQSocketNotifier *notifier_1{nullptr};
  //QSocketNotifier *notifier_2{nullptr};

//  int fd_from_bpla_to_pix{-1};
//  int fd_from_pix_to_bpla{-1};

  bool event(QEvent *event) override;

public slots:

  void from_bpla_to_pix(int fd);
  void from_pix_to_bpla(QByteArray *p);

signals:

};

#endif // FIFO_MOD_H
