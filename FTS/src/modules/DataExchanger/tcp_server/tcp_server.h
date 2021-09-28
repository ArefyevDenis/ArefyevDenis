#ifndef		_TCP_SERVER_H_
#define		_TCP_SERVER_H_

#pragma once

#include <list>

#include <QObject>
#include <QtNetwork/QTcpServer>

#include "../../../../include/ifaces/modules/DataExchanger/data_exchange_iface.h"

namespace FTS {
    namespace Ifaces{
        class ICoreMainIfaces;
    }
}

class QTimer;
class QTcpSocket;


//==================================================================================================================//
typedef std::list< IDataReceiver* > DataReceiverCont;
typedef DataReceiverCont::iterator DataReceiverContIter;
typedef DataReceiverCont::const_iterator DataReceiverContCIter;
//==================================================================================================================//
typedef std::list< QTcpSocket* > TcpSocketCont;
typedef TcpSocketCont::iterator TcpSocketContIter;
typedef TcpSocketCont::const_iterator TcpSocketContCIter;
//==================================================================================================================//

class TcpServer: public QTcpServer, public IDataExchange
{
    Q_OBJECT

public:
    TcpServer( FTS::Ifaces::ICoreMainIfaces* InCoreMainIfaces, QString InIpv4ListenInterface, unsigned int InListenPort );
    virtual ~TcpServer();

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

    void        OnReadyRead();
    void        OnDisconnection();
    void        OnError(QAbstractSocket::SocketError error);


private slots:

    void                    OnIncomingNewConnection( void );

private:

    FTS::Ifaces::ICoreMainIfaces*   m_pCoreMainIfaces;

    QString                         m_Ipv4ListenIface;

    unsigned int                    m_ListenPort;

    DataReceiverCont    m_DataReceivers; //Список указателей на интерфейсы получателей данных
    TcpSocketCont       m_ActualSocketConnections; //список актуальных подключений

};
//-----------------------------------------------------------------------------

#endif		//_TCP_SERVER_H_
