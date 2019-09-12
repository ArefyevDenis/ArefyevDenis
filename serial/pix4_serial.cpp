#include "pix4_serial.h"

#include <iostream>
#include <streambuf>

#include <stddef.h>
#include <stdio.h>
#include<unistd.h>
#include <cstdlib>

#include <mavlink/common/mavlink.h>

#include <experimental/filesystem>

#include "factory_morf.h"

#include <QTextStream>

REGISTER_SERIALIZABLE(Pix4_serial);

#define dbg() std::cout << __PRETTY_FUNCTION__ << "\n";

namespace  {
  QString str_read;
}

Pix4_serial::Pix4_serial(QObject *parent)
  : QObject(parent)
{
  dbg();
  //emit serialPortStatusChanged(QObject::tr("Закрыт"));
}

Pix4_serial::~Pix4_serial(){
  for (auto& kvp: m_pix.toStdMap()) {
      connect(kvp.second, &QIODevice::readyRead, this, &Pix4_serial::read_From_Serial_Port);
      connect(kvp.second, &QSerialPort::errorOccurred, this, &Pix4_serial::print_Error);
      delete kvp.second;
    }

  dbg();
}

void Pix4_serial::set_Serial_Port(QString comName, int baudRate, int dataBits, int parity, int stopBits, int flowControl){

  m_pix[comName] = new QSerialPort;
  const char a = comName.back().toLatin1();
  m_pix_chan[m_pix[comName]] = std::atoi(&a);
  connect(m_pix[comName], &QIODevice::readyRead, this, &Pix4_serial::read_From_Serial_Port);
  connect(m_pix[comName], &QSerialPort::errorOccurred, this, &Pix4_serial::print_Error);

  m_pix[comName]->setPortName(comName);
  m_pix[comName]->setBaudRate(static_cast<QSerialPort::BaudRate>(baudRate));
  m_pix[comName]->setDataBits(static_cast<QSerialPort::DataBits>(dataBits));
  m_pix[comName]->setParity(static_cast<QSerialPort::Parity>(parity));
  m_pix[comName]->setStopBits(static_cast<QSerialPort::StopBits>(stopBits));
  m_pix[comName]->setFlowControl(static_cast<QSerialPort::FlowControl>(flowControl));

}

void Pix4_serial::b_apply(void *cmd){

  QString *str_cmd;

  if(cmd != nullptr)
      str_cmd = static_cast<QString*>(cmd);

  // 1. если это строка
  //  1.1. если это управляющая команда для класса Pix4_serial
  //  1.2. если это управляющая команда для одного из пиксов
  //

  // добавим символ завершения строки это важно
  // а в ардиинке вот так String s = Serial.readStringUntil('\n'); s += '\n'; Serial.write(s.c_str());

  str_cmd->append('\n');

  m_pix[*str_cmd]->write(str_cmd->toStdString().c_str(), str_cmd->size() );

}

void Pix4_serial::b_start(void *ptr){
  // параметры вынести в  настройки !!!!!!!!!!!!!!!!!!!!!!!!!!!!!

  if(ptr == nullptr)
    return;

  QString *st = static_cast<QString *>( ptr ) ;

  set_Serial_Port(*st, QSerialPort::Baud57600,  // скорость
                  QSerialPort::Data8,       // биты данных
                  QSerialPort::NoParity,    // бит чётности
                  QSerialPort::OneStop,     // стоп бит
                  QSerialPort::NoFlowControl);
  open_Serial_Port(*st);
}

void Pix4_serial::b_stop(void *){
  // думать может очистить всё сразу
}

void Pix4_serial::open_Serial_Port(QString name){
  close_Serial_Port(name);
  if (m_pix[name]->open(QIODevice::ReadWrite)) {
      str_read = name; // последний открытый порт будет отсылать принятые данные на БПЛА
      std::cout << __PRETTY_FUNCTION__ << " " << "Serial Open " << name.toStdString() << "\n";
    } else {
      std::cout << __PRETTY_FUNCTION__ << " " << "No Open " << name.toStdString() << "\n";
    }
}

void Pix4_serial::close_Serial_Port(QString name) {
  try {
    if (m_pix[name]->isOpen()) {
        m_pix[name]->close();
        //emit serialPortStatusChanged(QObject::tr("%1 закрыт").arg(m_serial.portName()));
      }
  } catch (std::exception &ex) {
      std::cout << __FILE__ << " " << __LINE__ << " " << ex.what() << "\n";
  }
}


int msg_pix4[16][256] ;
int count_msg = 0;

void Pix4_serial::read_From_Serial_Port() {

  static QByteArray b_data;

  QSerialPort *ts = static_cast<QSerialPort*>(sender());

  const QByteArray ba(ts->readAll());

  if(m_pix[str_read] == ts) {

      // map_obj.at("Fifo_mod")->b_apply((void *)&ba);

    }

  mavlink_message_t msg;
  mavlink_status_t status;
  int chan = m_pix_chan[ts]; ///  выбор канала
  uint8_t msgReceived;
  if(ba.size() != 0)
    {
      for(size_t iter=0; iter < static_cast<size_t>(ba.size()); ++iter)
        { ///  парсинг от мавлинка попрежнему самый надёжный
          msgReceived = mavlink_parse_char(chan, ba.at(iter), &msg, &status);
          if (msgReceived > 0)
            {

              switch(msg.msgid)
                {
                case MAVLINK_MSG_ID_VFR_HUD:
                  {
                    mavlink_vfr_hud_t hud;
                    mavlink_msg_vfr_hud_decode(&msg,&hud);

                    QTextStream t_str(stdout);
                    t_str << ts << " air :" << hud.airspeed <<  " ground :" << hud.groundspeed << " heading: " << hud.heading << " alt: " << hud.alt << " climb: " << hud.climb << "\n";

                  }
                  break;

                default:
                  break;
                }

              //              if(msg.msgid >= 0 &&  msg.msgid < 1024 ){
              //                  msg_pix4[chan][msg.msgid]++;
//                }else{
//                  std::cout << " error msg = " << msg.msgid  << "\n";
//                }
//              if(count_msg++%1024 == 0){
//                  std::stringstream s_str;
//
//                  t_str << ts << " ";
//                  for (uint ix=0;ix < 256; ix++) {
//                      if(msg_pix4[chan][ix] != 0){
//                          t_str << ix << " ";
//                        }
//                    }
//                 std::cout << t_str.readAll().toStdString() << "\n";
               //  for(uint ix=0;ix < 256; ix++){  std::printf("%4d%c", (msg_pix4[ix][] != 0) ? ix : 0 ," \n"[ix%16 == 15]);  }  std::printf("\n");
//                }
            }
        }
    }else{
      std::cout << " ba.size() = " << ba.size() << "\n";
    }

}



void Pix4_serial::parsing_mavlink(QSerialPort *ts){

//  mavlink_message_t msg;
//  mavlink_status_t status;
//  int chan = 0; ///
//  uint8_t msgReceived;

//  const QByteArray ba(ts->readAll());

//  if(ba.size() != 0)
//    {
//      for(size_t iter=0; iter < static_cast<size_t>(ba.size()); ++iter)
//        { ///  парсинг от мавлинка попрежнему самый надёжный
//          msgReceived = mavlink_parse_char(chan, ba.at(iter), &msg, &status);
//          if (msgReceived > 0)
//            {

//              if(msg.msgid >= 0 &&  msg.msgid < 1024 ){
//                  msg_pix4[chan][msg.msgid]++;
//                }else{
//                  std::cout << " error msg = " << msg.msgid  << "\n";
//                }

//              if(count_msg++%1024 == 0){
//                  for(uint ix=0;ix < 256; ix++){  std::printf("%4d%c", (msg_pix4[ix] != 0) ? ix : 0 ," \n"[ix%16 == 15]);  }  std::printf("\n");

//                }

//            }
//        }

//    }else{
//      std::cout << " ba.size() = " << ba.size() << "\n";
//    }



}



void Pix4_serial::print_Error(QSerialPort::SerialPortError error){

  QSerialPort *ts = static_cast<QSerialPort*>(sender());

  if (error != QSerialPort::NoError){

      qDebug("Serial port error: %s", ts->errorString().toStdString().c_str());

      for(auto kvp:  m_pix){
          // закрыть порт и отправить сигнал
        }

    }
}
