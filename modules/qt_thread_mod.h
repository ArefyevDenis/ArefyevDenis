#ifndef QT_THREAD_MOD_H
#define QT_THREAD_MOD_H

#include <QThread>
#include <QVector>

#include <QTimer>

//#define p_q_inst ((Qt_thread::p_instance()))
//#define r_q_inst(x) ((Qt_thread::r_instance(x)))

#include "udp_sock_wrap.h"
#include "tcp_server_wrap.h"
#include "tcp_sock_wrap.h"

#include "serial/serialport_wrap.h"
#include "serial/listen_std_out.h"
#include "serial/arduino_uno.h"
#include "serial/pix4_serial.h"
#include "serial/fifo_mod.h"

#include "base_factory.h"
#include "factory_morf.h"

//class Tcp_server_wrap;
//class Tcp_sock_wrap;
//class Udp_sock_wrap;

class Qt_thread :
    public QThread,
    public Base_factory
{
  Q_OBJECT

public:
  explicit Qt_thread( QObject *parent = nullptr);

  Qt_thread(const Qt_thread&)               = delete;
  Qt_thread(Qt_thread&&)                    = delete;
  Qt_thread& operator = (const Qt_thread&)  = delete;
  Qt_thread& operator = (Qt_thread&&)       = delete;
  Qt_thread(std::initializer_list<int> il)  = delete;

public:
  ~Qt_thread()                                      override;

  //  static Qt_thread& r_instance(QObject *parent){ static Qt_thread vp(parent); return vp; }
  //  static Qt_thread* p_instance(){ return self; }
  //  static Qt_thread* self;

  void run()                                        override;

  //  bool event(QEvent *event)                         override;
  //  bool eventFilter(QObject *watched, QEvent *event) override;
  //  void connectNotify(const QMetaMethod &signal)     override;
  //  void disconnectNotify(const QMetaMethod &signal)  override;

  Factory_Morf      fm;
  Tcp_server_wrap   *p_tsw{nullptr};
  Tcp_sock_wrap     *p_tcw{nullptr};
  Udp_sock_wrap     *p_usw{nullptr};
 // Serialport_wrap   *p_slw{nullptr};
 // Listen_std_in     *p_lsi{nullptr};
  Arduino_UNO         *p_aun{nullptr};
  Console_Reader    *p_crd{nullptr};
  Pix4_serial       *p_pix{nullptr};
  Fifo_mod          *p_fif{nullptr};

  virtual void b_apply(void *)  override{}             ///применять, использовать
  virtual void b_start(void *)  override;
  virtual void b_stop(void *)   override;
  virtual const char* b_type_name() override{return typeid (this).name(); }

private:

  QTimer        readTimer;

  QVector<QThread*>     vec_thread; //

  //void timerEvent(QTimerEvent *event) override;
  //void childEvent(QChildEvent *event) override;
  //void customEvent(QEvent *event)     override;

  void b_start_new_thread();
  void b_stop_thread();

signals:

public slots:

  void readTimeout();
};

#endif // QT_THREAD_MOD_H
