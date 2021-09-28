#include "serial_port.h"

#include "../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../include/ifaces/main/logger_iface.h"

#include <QSerialPortInfo>
#include <QList>
#include <QTimer>
#include <QFile>
#include <QDateTime>

#include <iostream>
#include <stdio.h>

#define TIMER_REOPEN        3000


//==================================================================================================================//
SerialPort::SerialPort(FTS::Ifaces::ICoreMainIfaces *InCoreMainIfaces, QString name, unsigned int baud, unsigned int dbits, unsigned int sbits, unsigned int parity, unsigned int fctrl):
    QSerialPort(),
    m_pCoreMainIface(InCoreMainIfaces),
    m_name(name),
    m_baud(baud),
    m_dbits(dbits),
    m_sbits(sbits),
    m_parity(parity),
    m_fctrl(fctrl){

    assert(m_pCoreMainIface);
    m_pCoreMainIface->GetProtocolIface()->debug("Создание объекта работы с COM-портом [%1]", m_name.toStdString().c_str());

    connect( this, SIGNAL(readyRead()), SLOT(slot_readyRead()));
    connect( this, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(slot_error(QSerialPort::SerialPortError)) );

    m_pTimer= new QTimer();
    connect( m_pTimer, SIGNAL(timeout()), SLOT(slot_reconnect()));
    m_pTimer->start(TIMER_REOPEN);
}

SerialPort::~SerialPort(){
   if( isOpen() ) {
        close();
    }
}

//==================================================================================================================//
void CALL_CONVERSION SerialPort::setIDataReceiver(IDataReceiver *InIDataReceiver){
    //Сделаем проверку при добавлении, чтобы не повторялись интерфейсы
    for( QList<IDataReceiver*>::iterator it = m_listIDataReceiver.begin(); it != m_listIDataReceiver.end(); it++ ) {
        if( (*it) == InIDataReceiver )
            return;
    }
    if( this->isOpen() )
        InIDataReceiver->Connnect();
    else
        InIDataReceiver->Disconnect();
    m_listIDataReceiver.push_back( InIDataReceiver );
}

//==================================================================================================================//
bool CALL_CONVERSION SerialPort::isConnect(){
    return this->isOpen();
}

//==================================================================================================================//
unsigned int CALL_CONVERSION SerialPort::GetVersion(void){
    return DATA_EXCHANGE_IFACE_VERSION;
}

//==================================================================================================================//
const char * CALL_CONVERSION SerialPort::GetId(void){
    return DATA_EXCHANGE_IFACE_ID;
}


//==================================================================================================================//
bool SerialPort::setConnection(){

    //проверим, не открыт ли порт
    if (this->isOpen()){
        this->close();
    }

    //для начала получим список доступных портов
    QList <QSerialPortInfo> portList;
    portList = QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &info, portList) {
        if (info.portName().contains(m_name) && info.isBusy() == false){
            this->setPortName(info.portName());
            break;
        }
    }

    bool res = open(QIODevice::ReadWrite);
    //если удачно открыли, захуярим настройки
    if (res){
        this->setBaudRate( m_baud);
        this->setDataBits( (DataBits)m_dbits);
        this->setStopBits( (StopBits)m_sbits );
        this->setParity( (Parity)m_parity );
        this->setFlowControl( (FlowControl)m_fctrl );
        for( int i = 0; i < m_listIDataReceiver.size(); i++ ) {
            m_listIDataReceiver[i]->Connnect();
        }
    }
    return res;
}

//==================================================================================================================//
void SerialPort::slot_reconnect(){
    m_pTimer->stop();
    if ( this->setConnection() == false){
        m_pTimer->start(TIMER_REOPEN);
    }
}

//==================================================================================================================//
void SerialPort::slot_readyRead(){ 
    //Читаем все разом
    QByteArray bytes = readAll();
    //Передаем на зарегистрированных клиентов
    for( int i = 0; i < m_listIDataReceiver.size(); i++ ) {
        m_listIDataReceiver[i]->setData( bytes.data(), bytes.size() );
    }
    m_pCoreMainIface->GetProtocolIface()->debug("Read data [%1] bytes", bytes.size());
}

//==================================================================================================================//
void SerialPort::slot_error(QSerialPort::SerialPortError error){

    QString err_str( "" );

    switch( error ) {
    case NoError:
        return;
        break;
    case DeviceNotFoundError:
        err_str = " DeviceNotFoundError";
        this->close();
        break;
    case PermissionError:
        err_str = " PermissionError";
        this->close();
        break;
    case OpenError:
        err_str = " OpenError";
        this->close();
        break;
    case NotOpenError:
        err_str = " NotOpenError";
        break;
    case ParityError:
        err_str = " ParityError";
        break;
    case FramingError:
        err_str = " FramingError";
        break;
    case BreakConditionError:
        err_str = " FramingError";
        break;
    case WriteError:
        err_str = " WriteError";
        break;
    case ReadError:
        err_str = " ReadError";
        this->close();
        break;
    case ResourceError:
        err_str = " ResourceError";
        this->close();
        break;
    case UnsupportedOperationError:
        err_str = " UnsupportedOperationError";
        break;
    case TimeoutError:
        err_str = " TimeoutError";
        break;
    case UnknownError:
    default:
        err_str = " UnknownError";
        break;
    }

    if (err_str.isEmpty() == false){
        m_pCoreMainIface->GetProtocolIface()->error("Ошибка COM [%1] текст: [%2]",
                                                    this->portName().toStdString().c_str(),
                                                    err_str.toStdString().c_str());
    }

    //если после ошибки порт не отрыт, то еведомим об этом
    if( this->isOpen() == false ) {
        for( int i = 0; i < m_listIDataReceiver.size(); i++ ) {
            m_listIDataReceiver[i]->Disconnect();
        }
        //если таймер реконнекта не запущен, запускаем
        if (m_pTimer->isActive() == false){
            m_pTimer->start(TIMER_REOPEN);
        }
    }
}


//==================================================================================================================//
void CALL_CONVERSION SerialPort::write(const char* data, int size){
    if (this->isOpen()){
        writeData(data, size);
        waitForBytesWritten(5);
    }
}

#include "serial_port.moc"
