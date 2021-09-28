#ifndef		_TCP_CLIENT_H_
#define		_TCP_CLIENT_H_


#include "../../../../include/ifaces/modules/DataExchanger/data_exchange_iface.h"
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QList>

namespace FTS {
    namespace Ifaces{
        class ICoreMainIfaces;
    }
}


class QTimer;
class QTcpSocket;



class TcpClient : public QTcpSocket, public IDataExchange
{
    Q_OBJECT
public:
    TcpClient( FTS::Ifaces::ICoreMainIfaces* InCoreMainIfaces, QString Ipv4Host, unsigned int Port );
    virtual ~TcpClient();

    /**
     * @brief Передача данных
     *
     * @param  data - данные
     * @param  size - размер массива данных
     * @return ...
     **/
    void CALL_CONVERSION write(const char* data, int size);

    /**
     * @brief установить приёмник данных
     *
     * @param InIDataReceiver - приёмник данных
     * @return void
     **/
    void CALL_CONVERSION setIDataReceiver( IDataReceiver* InIDataReceiver );


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

    FTS::Ifaces::ICoreMainIfaces*   m_pCoreMainIfaces;
    QList<IDataReceiver*> m_listIDataReceiver;  //Список указателей на интерфейсы получателей данных
    QTimer *m_pTimer;                           //таймер переподключения
    bool m_connection;                          //статус подключения

    QString m_Ipv4Host;
    unsigned int m_port;


};

#endif		//_TCP_CLIENT_H_
