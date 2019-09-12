#ifndef SERIALPORT_WRAP_H
#define SERIALPORT_WRAP_H

#include <QSerialPort>

#include "base_factory.h"

class Serialport_wrap:
    public QSerialPort,
    public Base_factory
{
  Q_OBJECT
public:
  explicit Serialport_wrap(QObject *pr = nullptr);

  ~Serialport_wrap() override;

  virtual void b_apply(void *)  override{}             ///применять, использовать
  virtual void b_start(void *)  override{}
  virtual void b_stop(void *)   override;
  virtual const char* b_type_name() override{ return typeid (this).name(); }

  void sl_start(QString comName, int baudRate, int dataBits, int parity, int stopBits, int flowControl);

signals:

public slots:

  void read_From_Serial_Port();
  void print_Error(QSerialPort::SerialPortError);

};


//void	aboutToClose()
//void	bytesWritten(qint64 bytes)
//void	channelBytesWritten(int channel, qint64 bytes)
//void	channelReadyRead(int channel)
//void	readChannelFinished()
//void	readyRead()


//void	baudRateChanged(qint32 baudRate, QSerialPort::Directions directions)
//void	breakEnabledChanged(bool set)
//void	dataBitsChanged(QSerialPort::DataBits dataBits)
//void	dataTerminalReadyChanged(bool set)
//void	errorOccurred(QSerialPort::SerialPortError error)
//void	flowControlChanged(QSerialPort::FlowControl flow)
//void	parityChanged(QSerialPort::Parity parity)
//void	requestToSendChanged(bool set)
//void	stopBitsChanged(QSerialPort::StopBits stopBits)


#endif // SERIALPORT_WRAP_H
