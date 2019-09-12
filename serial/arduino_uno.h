#ifndef ARDUINO_UNO_H
#define ARDUINO_UNO_H

#include <QObject>
#include <QSerialPort>

#include "base_factory.h"

class Arduino_UNO :
    public QObject,
    public Base_factory
{
    Q_OBJECT
public:
    explicit Arduino_UNO(QObject *parent = nullptr);

  ~Arduino_UNO()override ;

    void set_Serial_Port(QString comName,
                       int baudRate,
                       int dataBits,
                       int parity,
                       int stopBits,
                       int flowControl);


    virtual void b_apply(void *)  override;          ///применять, использовать
    virtual void b_start(void *)  override;
    virtual void b_stop(void *)   override;
    virtual const char* b_type_name() override{ return typeid (this).name(); }

    void open_Serial_Port();
    void close_Serial_Port();
private:
    QSerialPort m_serial;

private slots:
    void read_From_Serial_Port();
    void print_Error(QSerialPort::SerialPortError);
signals:
//    void positionReceived(bool located, double lon, double lat);
//    void serialPortStatusChanged(const QString &);
};


#endif // ARDUINO_UNO_H
