#ifndef		_UDP_CLIENT_H_
#define		_UDP_CLIENT_H_


#include "../../../../include/ifaces/modules/DataExchanger/data_exchange_iface.h"
#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QList>

namespace FTS {
    namespace Ifaces{
        class ICoreMainIfaces;
    }
}

class QTimer;



class UdpClient : public QUdpSocket, public IDataExchange
{
    Q_OBJECT
public:
    UdpClient(FTS::Ifaces::ICoreMainIfaces *InCoreMainIfaces, QString host_src, unsigned int port_src, QString host_dst, unsigned int port_dst, bool mcast);
    virtual ~UdpClient();

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
     * @brief удалить приемник данных
     *
     * @param InIDataReceiver - адрес приемника данных
     * @return void
     **/
    virtual void CALL_CONVERSION delIDataReceiver( IDataReceiver * InIDataReceiver );

    /**
     * @brief Возвращает состояние подключения
     *
     * @return true - соединение есть, false - неподключены
     **/
    virtual bool CALL_CONVERSION isConnect();

//--- FTS::Ifaces::IExportIface

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



public slots:
    void slot_readyRead();
    void slot_error(QAbstractSocket::SocketError error);
    void slot_reconnect();
    void slot_connection();
    void slot_disconnection();

private:

    bool setConnection();

private:

    FTS::Ifaces::ICoreMainIfaces* m_pCoreMainIfaces;
    QString m_host_src;
    unsigned int m_port_src;
    QString m_host_dst;
    unsigned int m_port_dst;
    bool m_mcast;

    /**
     * @brief Список указателей на интерфейсы получателей данных
     **/
    QList<IDataReceiver*> m_listIDataReceiver;
    /**
     * @brief m_pTimer - таймер переподключения
     **/
    QTimer *m_pTimer;
    /**
     * @brief m_connection - признак подключения к порту
     **/
    bool m_connection;

};

#endif		//_UDP_CLIENT_H_
