
#include <iostream>
#include <assert.h>

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QNetworkSession>

#include <QDateTime>

#include "../../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../../include/ifaces/main/logger_iface.h"

#include "tcp_server.h"


//==================================================================================================================//
TcpServer::TcpServer(FTS::Ifaces::ICoreMainIfaces *InCoreMainIfaces, QString InIpv4ListenInterface, unsigned int InListenPort ):
    QTcpServer(),
    m_pCoreMainIfaces( InCoreMainIfaces ),
    m_Ipv4ListenIface( InIpv4ListenInterface ),
    m_ListenPort( InListenPort ){

    listen( QHostAddress( m_Ipv4ListenIface ), m_ListenPort );
    if( isListening() ){
        m_pCoreMainIfaces->GetProtocolIface()->debug( "Создан объекта прослушивания входящих TCP-соединений, интерфейс [%1], порт [%2]...",
                                                        m_Ipv4ListenIface.toStdString().c_str(),
                                                        m_ListenPort
                                                        );
        connect( this, SIGNAL(newConnection()), this, SLOT(OnIncomingNewConnection()) );
    } else {
        m_pCoreMainIfaces->GetProtocolIface()->error( "Объект прослушивания входящих TCP-соединений не создан" );
        close();
    }

}

//==================================================================================================================//
TcpServer::~TcpServer(){

}

//==================================================================================================================//
void CALL_CONVERSION TcpServer::setIDataReceiver( IDataReceiver *InIDataReceiver ){
    //Сделаем проверку при добавлении, чтобы не повторялись интерфейсы
    DataReceiverContCIter it = m_DataReceivers.begin();
    for( ; it != m_DataReceivers.end(); it++ )
    {
        if( ( *it ) == InIDataReceiver )
            return;
    }
    m_DataReceivers.push_back( InIDataReceiver );
}

//==================================================================================================================//
bool CALL_CONVERSION TcpServer::isConnect(){
    if (m_ActualSocketConnections.size() > 0 )
        return true;
    return false;
}

//==================================================================================================================//
unsigned int CALL_CONVERSION TcpServer::GetVersion(void){
    return DATA_EXCHANGE_IFACE_VERSION;
}

//==================================================================================================================//
const char* CALL_CONVERSION TcpServer::GetId(void){
    return DATA_EXCHANGE_IFACE_ID;
}

//==================================================================================================================//
void TcpServer::OnIncomingNewConnection( void ){
    m_pCoreMainIfaces->GetProtocolIface()->debug( "Доступно новое входящее соединенение..." );
    if( hasPendingConnections() ){
        QTcpSocket* new_socket = nextPendingConnection();
        assert( new_socket );
        static int integral_index = 0;

        new_socket->setObjectName( QString( "soc_index_%1" ).arg( ++integral_index ) );

        m_ActualSocketConnections.push_back( new_socket );

        QString str = QString( "Параметры входящего соединения: ИНДЕКС [%1], IPv4 [%2], port [%3]" ).arg( integral_index ).arg( new_socket->peerAddress().toString() ).arg( new_socket->peerPort() );

        m_pCoreMainIfaces->GetProtocolIface()->debug( str.toStdString().c_str() );

        connect( new_socket, SIGNAL ( readyRead() ), SLOT ( OnReadyRead() ) );
        connect( new_socket, SIGNAL ( disconnected() ), SLOT ( OnDisconnection() ) );
        connect( new_socket, SIGNAL ( error( QAbstractSocket::SocketError ) ), SLOT ( OnError( QAbstractSocket::SocketError ) ) );

        //Передаем на зарегистрированных клиентов уведомление, что есть подключение
        DataReceiverContIter it = m_DataReceivers.begin();
        for( ; it != m_DataReceivers.end(); it++ ){
            ( *it )->Connnect();
        }

    } else {
        m_pCoreMainIfaces->GetProtocolIface()->warn( "НЕТ СОЕДИНЕНИЙ!" );
    }

}

//==================================================================================================================//
void TcpServer::OnReadyRead() {
    QTcpSocket* soc = qobject_cast< QTcpSocket* >( sender() );
    if( soc == 0 ) return;

    //Читаем все разом
    QByteArray bytes = soc->readAll();

    m_pCoreMainIfaces->GetProtocolIface()->debug( "Поступили данные от [%1], размер [%2 байт]", soc->objectName().toStdString().c_str(), bytes.size() );

    //Передаем на зарегистрированных клиентов
    DataReceiverContIter it = m_DataReceivers.begin();

    for( ; it != m_DataReceivers.end(); it++ ){
        ( *it )->setData( bytes.data(), bytes.size() );
    }
}

//==================================================================================================================//
void TcpServer::OnError(QAbstractSocket::SocketError error){
    QTcpSocket* soc = qobject_cast< QTcpSocket* >( sender() );
    if( soc == 0 ) return;

    QString err_str( "" );

    switch( error ) {
    case QAbstractSocket::ConnectionRefusedError:
        err_str = "The connection was refused by the peer (or timed out)";
        break;
    case QAbstractSocket::RemoteHostClosedError:
        err_str = "The remote host closed the connection. Note that the client socket (i.e., this socket) will be closed after the remote close notification has been sent";
        break;
    case QAbstractSocket::HostNotFoundError:
        err_str =  "The host address was not found";
        break;
    case QAbstractSocket::SocketAccessError:
        err_str = "The socket operation failed because the application lacked the required privileges";
        break;
    case QAbstractSocket::SocketResourceError:
        err_str = "The local system ran out of resources (e.g., too many sockets)";
        break;
    case QAbstractSocket::SocketTimeoutError:
        err_str = "The socket operation timed out";
        break;
    case QAbstractSocket::DatagramTooLargeError:
        err_str = "The datagram was larger than the operating system's limit (which can be as low as 8192 bytes)";
        break;
    case QAbstractSocket::NetworkError:
        err_str = "An error occurred with the network (e.g., the network cable was accidentally plugged out)";
        break;
    case QAbstractSocket::AddressInUseError:
        err_str = "The address specified to QAbstractSocket::bind() is already in use and was set to be exclusive";
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        err_str = "The address specified to QAbstractSocket::bind() does not belong to the host";
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        err_str = "The requested socket operation is not supported by the local operating system (e.g., lack of IPv6 support)";
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        err_str = "The socket is using a proxy, and the proxy requires authentication";
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        err_str = "The SSL/TLS handshake failed, so the connection was closed (only used in QSslSocket)";
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        err_str = "Used by QAbstractSocketEngine only, The last operation attempted has not finished yet (still in progress in the background)";
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        err_str = "Could not contact the proxy server because the connection to that server was denied";
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        err_str = "The connection to the proxy server was closed unexpectedly (before the connection to the final peer was established)";
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        err_str = "The connection to the proxy server timed out or the proxy server stopped responding in the authentication phase";
        break;
    case QAbstractSocket::ProxyNotFoundError:
        err_str = "The proxy address set with setProxy() (or the application proxy) was not found";
        break;
    case QAbstractSocket::ProxyProtocolError:
        err_str = "The connection negotiation with the proxy server failed, because the response from the proxy server could not be understood";
        break;
    case QAbstractSocket::OperationError:
        err_str = "An operation was attempted while the socket was in a state that did not permit it";
        break;
    case QAbstractSocket::SslInternalError:
        err_str = "The SSL library being used reported an internal error. This is probably the result of a bad installation or misconfiguration of the library";
        break;
    case QAbstractSocket::SslInvalidUserDataError:
        err_str = "Invalid data (certificate, key, cypher, etc.) was provided and its use resulted in an error in the SSL library";
        break;
    case QAbstractSocket::TemporaryError:
        err_str = "A temporary error occurred (e.g., operation would block and socket is non-blocking)";
        break;
    case QAbstractSocket::UnknownSocketError:
        err_str = "An unidentified error occurred";
        break;
    default:
        err_str = "???";
        break;
    }

    m_pCoreMainIfaces->GetProtocolIface()->error("Ошибка от [%1], текст сообщения [%2]", soc->objectName().toStdString().c_str(), err_str.toStdString().c_str() );

}

//==================================================================================================================//
void TcpServer::OnDisconnection(){
    QTcpSocket* soc = qobject_cast< QTcpSocket* >( sender() );
    if( soc == 0 ) return;

    m_pCoreMainIfaces->GetProtocolIface()->debug( "Потеряно соединение с [%1]", soc->objectName().toStdString().c_str() );

    bool was_erase = false;

    TcpSocketContIter it = m_ActualSocketConnections.begin();
    for( ; it != m_ActualSocketConnections.end(); it++ ){
        if( ( *it )->objectName() == soc->objectName() ){
            disconnect( soc, SIGNAL ( readyRead() ), this, SLOT ( OnReadyRead() ) );
            disconnect( soc, SIGNAL ( disconnected() ), this, SLOT ( OnDisconnection() ) );
            disconnect( soc, SIGNAL ( error( QAbstractSocket::SocketError ) ), this, SLOT ( OnError( QAbstractSocket::SocketError ) ) );
            m_ActualSocketConnections.erase( it );
            was_erase = true;
            break;
        }
    }

    if( !was_erase ){
        m_pCoreMainIfaces->GetProtocolIface()->warn( "Сокет не найден в списке!" );
    }


    // если подключение больше нет
    if (m_ActualSocketConnections.size() == 0){
        //Передаем на зарегистрированных клиентов уведомление, что подключения отсутствуют
        DataReceiverContIter it = m_DataReceivers.begin();
        for( ; it != m_DataReceivers.end(); it++ ){
            ( *it )->Disconnect();
        }
    }
}

//==================================================================================================================//
void CALL_CONVERSION TcpServer::write(const char* data, int size){
    TcpSocketContIter it = m_ActualSocketConnections.begin();
    for( ; it != m_ActualSocketConnections.end(); it++ ){
        if( ( *it )->state() == QAbstractSocket::ConnectedState ){
            ( *it )->write( data, size );
        }
    }
}

//==================================================================================================================//

#include "tcp_server.moc"
