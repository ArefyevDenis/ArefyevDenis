#ifndef		_SERIAL_PORT_H_
#define		_SERIAL_PORT_H_

#include "../../../../include/ifaces/modules/DataExchanger/data_exchange_iface.h"
#include <QSerialPort>
#include <QList>

namespace FTS {
    namespace Ifaces{
        class ICoreMainIfaces;
    }
}


class QTimer;

class SerialPort : public QSerialPort, public IDataExchange
{
    Q_OBJECT
public:
    SerialPort(FTS::Ifaces::ICoreMainIfaces *InCoreMainIfaces, QString name, unsigned int baud, unsigned int dbits, unsigned int sbits, unsigned int parity, unsigned int fctrl);
    virtual ~SerialPort();

    /**
     * @brief Передача данных
     *
     * @param  data - данные
     * @param  size - размер массива данных
     * @return ...
     **/
    virtual void CALL_CONVERSION write(const char* data, int size);

    /**
     * @brief установить приёмник данных
     *
     * @param InIDataReceiver - приёмник данных
     * @return void
     **/
    virtual void CALL_CONVERSION setIDataReceiver( IDataReceiver * InIDataReceiver );

    /**
     * @brief Возвращает состояние подключения
     *
     * @return true - соединение есть, false - неподключены
     **/
    virtual bool CALL_CONVERSION isConnect();

    /**
     * @brief Получить версию интерфейса
     *
     * @param  ...
     * @return unsigned int
     **/
    virtual unsigned int CALL_CONVERSION GetVersion( void );

    /**
     * @brief Получить идентификатор интерфейса
     *
     * @param  ...
     * @return const char*
     **/
    virtual const char* CALL_CONVERSION	GetId( void );

protected:
    bool setConnection();

public slots:
    void slot_readyRead();
    void slot_error(QSerialPort::SerialPortError error);
    void slot_reconnect();

private:

    FTS::Ifaces::ICoreMainIfaces *m_pCoreMainIface;

    QString m_name;
    unsigned int m_baud;
    unsigned int m_dbits;
    unsigned int m_sbits;
    unsigned int m_parity;
    unsigned int m_fctrl;

    /**
     * @brief Список указателей на интерфейсы получателей данных
     **/
    QList<IDataReceiver*> m_listIDataReceiver;
    /**
     * @brief m_pTimer - таймер переподключения
     **/
    QTimer *m_pTimer;

};

#endif		//_SERIAL_PORT_H_
