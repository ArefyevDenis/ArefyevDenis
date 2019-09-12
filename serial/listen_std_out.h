#ifndef LISTEN_STD_OUT_H
#define LISTEN_STD_OUT_H

#include <QSocketNotifier>
#include <QIODevice>
#include <QObject>
#include <QFile>



#include "base_factory.h"
#include <iostream>

/// https://stackoverflow.com/questions/48734421/how-to-read-a-file-device-in-linux-using-qt
///

class Console_Reader :
    public QObject,
    public Base_factory
{
    Q_OBJECT
public:
    explicit Console_Reader(QObject *parent = 0);

  void b_apply(void *)  override{}             ///применять, использовать
  void b_start(void *)  override{}
  void b_stop(void *)   override{}
  const char* b_type_name() override{ return typeid (this).name(); }

signals:
    void textReceived(QString message);

public slots:
    void text();

private:
    QSocketNotifier notifier;
};



//==============================================================================================//


class Listen_std_in :
    public QObject,
    public Base_factory
{
  Q_OBJECT
public:
  explicit Listen_std_in(QObject *pr = nullptr);

  ~Listen_std_in() override;

   void b_apply(void *)  override{}             ///применять, использовать
   void b_start(void *)  override;
   void b_stop(void *)   override;
   const char* b_type_name() override{ return typeid (this).name(); }

  //void sl_start(QString comName, int baudRate, int dataBits, int parity, int stopBits, int flowControl);

   bool event(QEvent *event) override {
     std::cout << " Event: " << event << "\n";
     this->event(event);
     return true;
   }

  QFile fff;

signals:

public slots:

  void read_from_std_in();
  //void print_eError(QSerialPort::SerialPortError);

};


//==============================================================================================//

//class Joystick
//      : public QObject
//{
//    Q_OBJECT

//    QString fileName = "/dev/input/js0";
//    QSocketNotifier *notifier;
//    int fd;

//public:
//    explicit Joystick(QObject *parent = nullptr);
//    ~Joystick();

//signals:
//    void buttonPressed(quint8 number, qint16 value);
//    void axisMoved(quint8 number, qint16 value);


//public slots:
//    void handle_readNotification(int socket);
//};


#endif // LISTEN_STD_OUT_H
