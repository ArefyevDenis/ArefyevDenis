#include "arduino_uno.h"

#include <iostream>

#include "factory_morf.h"
REGISTER_SERIALIZABLE(Arduino_UNO);
#define dbg() std::cout << __PRETTY_FUNCTION__ << "\n";

Arduino_UNO::Arduino_UNO(QObject *parent)
  : QObject(parent)
{
  connect(&m_serial, &QIODevice::readyRead, this, &Arduino_UNO::read_From_Serial_Port);
  connect(&m_serial, &QSerialPort::errorOccurred, this, &Arduino_UNO::print_Error);

  dbg();

  //emit serialPortStatusChanged(QObject::tr("Закрыт"));
}

Arduino_UNO::~Arduino_UNO(){
  dbg();
}

void Arduino_UNO::set_Serial_Port(QString comName, int baudRate, int dataBits, int parity, int stopBits, int flowControl){
  m_serial.setPortName(comName);
  m_serial.setBaudRate(static_cast<QSerialPort::BaudRate>(baudRate));
  m_serial.setDataBits(static_cast<QSerialPort::DataBits>(dataBits));
  m_serial.setParity(static_cast<QSerialPort::Parity>(parity));
  m_serial.setStopBits(static_cast<QSerialPort::StopBits>(stopBits));
  m_serial.setFlowControl(static_cast<QSerialPort::FlowControl>(flowControl));
}


void Arduino_UNO::b_apply(void *cmd){

  QString *str_cmd;

  if(cmd != nullptr)
      str_cmd = static_cast<QString*>(cmd);

  // добавим символ завершения строки это важно
  // а в ардуинке вот так String s = Serial.readStringUntil('\n'); s += '\n'; Serial.write(s.c_str());

  str_cmd->append('\n');

  m_serial.write(str_cmd->toStdString().c_str(), str_cmd->size() );

}

void Arduino_UNO::b_start(void *){
  /// параметры вынести в  настройки !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  set_Serial_Port(QString("/dev/ttyUSB0"),
                  QSerialPort::Baud115200,  // скорость
                  QSerialPort::Data8,       // биты данных
                  QSerialPort::NoParity,    // бит чётности
                  QSerialPort::OneStop,     // стоп бит
                  QSerialPort::NoFlowControl);
  open_Serial_Port();
}

void Arduino_UNO::b_stop(void *){
   close_Serial_Port();
}

void Arduino_UNO::open_Serial_Port(){
  close_Serial_Port();
  if (m_serial.open(QIODevice::ReadWrite))
   std::cout << __PRETTY_FUNCTION__ << " Serial Open /dev/ttyUSB0\n";
  else
   std::cout << __PRETTY_FUNCTION__ << " No Open /dev/ttyUSB0\n";
}

void Arduino_UNO::close_Serial_Port(){
  if (m_serial.isOpen())
    {
      m_serial.close();
      //emit serialPortStatusChanged(QObject::tr("%1 закрыт").arg(m_serial.portName()));
    }
}


void Arduino_UNO::read_From_Serial_Port(){
  static QByteArray b_data;

  const QByteArray ba(m_serial.readAll());

  for (int i = 0; i < ba.size(); i++){
      switch (ba.at(i)){
        case '\n':
          std::cout << "{" << QString(b_data).toStdString() << "}\n";
          b_data.clear();
          break;
        default:
          b_data.append(ba.at(i));
          break;
        }
    }

    //0D \r возврат каретки
    //0A \n перевод строки
}

void Arduino_UNO::print_Error(QSerialPort::SerialPortError error){
    if (error != QSerialPort::NoError) {
        qDebug("Serial port error: %s", m_serial.errorString().toStdString().c_str());
        close_Serial_Port();
    }
}
