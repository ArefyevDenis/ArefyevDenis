#include "serialport_wrap.h"

#include <iostream>
#include "factory_morf.h"

namespace  {

  QString   m_comName;
  int       m_baudRate;
  int       m_dataBits;
  int       m_parity;
  int       m_stopBits;
  int       m_flowControl;

}

REGISTER_SERIALIZABLE(Serialport_wrap);

#define dbg()   std::cout << __PRETTY_FUNCTION__ << "\n";


Serialport_wrap::Serialport_wrap(QObject *pr):
  QSerialPort (pr)
{
  dbg();
}

Serialport_wrap::~Serialport_wrap()     {

}

void Serialport_wrap::sl_start(QString nm, int br, int db, int pr, int sb, int fc)   {

  connect(this, &QIODevice::readyRead, this, &Serialport_wrap::read_From_Serial_Port);
  connect(this, &QSerialPort::errorOccurred, this, &Serialport_wrap::print_Error);

  setPortName(nm);
  setBaudRate(static_cast<QSerialPort::BaudRate>(br));
  setDataBits(static_cast<QSerialPort::DataBits>(db));
  setParity(static_cast<QSerialPort::Parity>(pr));
  setStopBits(static_cast<QSerialPort::StopBits>(sb));
  setFlowControl(static_cast<QSerialPort::FlowControl>(fc));

}

void Serialport_wrap::b_stop(void *)    {
  disconnect(this, &QIODevice::readyRead, this, &Serialport_wrap::read_From_Serial_Port);
  disconnect(this, &QSerialPort::errorOccurred, this, &Serialport_wrap::print_Error);
}

void Serialport_wrap::read_From_Serial_Port()
{
    static QByteArray gpsdata;

    const QByteArray ba(readAll());

    for (int i = 0; i < ba.size(); i++)
    {
        switch (ba.at(i))
        {
        case 0x0A:
            break;
        case 0x0D:
            //handleInfo(gpsdata);
            gpsdata.clear();
            break;
        default:
            gpsdata.append(ba.at(i));
            break;
        }
    }

    //0D \r возврат каретки
    //0A \n перевод строки
}

void Serialport_wrap::print_Error(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError)
    {
        //qDebug("Serial port error: %s", m_serial.errorString().toStdString().c_str());
        //closeSerialPort();
    }
}
