#ifndef PIX4_SERIAL_H
#define PIX4_SERIAL_H


#include <QObject>
#include <QVector>
#include <QMap>
#include <QSerialPort>

#include "base_factory.h"

class Pix4_serial :
    public QObject,
    public Base_factory
{
    Q_OBJECT
public:
    explicit Pix4_serial(QObject *parent = nullptr);

  ~Pix4_serial() override ;

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

    void open_Serial_Port(QString name);
    void close_Serial_Port(QString name );
private:

    QVector<QSerialPort*>       v_pix; // вектор пиксов
    QMap<QString,QSerialPort*>  m_pix;      // map пиксов
    QMap<QSerialPort*,int>      m_pix_chan; // map каналов для парсинга mavlink messages
    int                         chan{0};    // всего 16 каналов 16 пиксов

    void parsing_mavlink(QSerialPort*);

    //QSerialPort m_serial;

private slots:
    void read_From_Serial_Port();
    void print_Error(QSerialPort::SerialPortError);
signals:
//    void positionReceived(bool located, double lon, double lat);
//    void serialPortStatusChanged(const QString &);
};


#endif // PIX4_SERIAL_H
