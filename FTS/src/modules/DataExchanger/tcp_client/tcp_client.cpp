#include "tcp_client.h"


#include "../../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../../include/ifaces/main/logger_iface.h"

#include <QtNetwork/QTcpSocket>
#include <QTimer>
#include <QDateTime>
#include <iostream>

#define TIMEOUT_RECONNECT 2000 //2сек
#define TIMEOUT_CHECK_CONNECT 10000  //10сек

//==================================================================================================================//
TcpClient::TcpClient(FTS::Ifaces::ICoreMainIfaces *InCoreMainIfaces, QString Ipv4Host, unsigned int Port):
    QTcpSocket(),
    m_pCoreMainIfaces(InCoreMainIfaces),
    m_Ipv4Host(Ipv4Host),
    m_port(Port){

    //протягиваем связки сигнал - слот
    connect ( this, SIGNAL ( readyRead() ), SLOT ( slot_readyRead() ) );
    connect ( this, SIGNAL ( disconnected() ), SLOT ( slot_disconnection() ) );
    connect ( this, SIGNAL ( connected() ), SLOT( slot_connection() ) );
    connect ( this, SIGNAL ( error( QAbstractSocket::SocketError ) ), SLOT ( slot_error( QAbstractSocket::SocketError ) ) );

    // таймер реконектов
    m_pTimer = new QTimer();
    connect( m_pTimer, SIGNAL(timeout()), SLOT(slot_reconnect()), Qt::DirectConnection );

    m_connection = false;

    m_pCoreMainIfaces->GetProtocolIface()->debug("Создан Tcp-клиент подключения к IPv4 [%1] порт [%2]", m_Ipv4Host.toStdString().c_str(), m_port);
    setConnection();


}

//==================================================================================================================//
TcpClient::~TcpClient(){
    if (state() == QAbstractSocket::ConnectedState){
        disconnectFromHost();
    }
    close();
}

//==================================================================================================================//
void CALL_CONVERSION TcpClient::setIDataReceiver(IDataReceiver *InIDataReceiver){
    //Сделаем проверку при добавлении, чтобы не повторялись интерфейсы
    for( QList<IDataReceiver*>::iterator it = m_listIDataReceiver.begin(); it != m_listIDataReceiver.end(); it++ ) {
        if( (*it) == InIDataReceiver )
            return;
    }
    if( m_connection )
        InIDataReceiver->Connnect();
    else
        InIDataReceiver->Disconnect();
    m_listIDataReceiver.push_back( InIDataReceiver );
}

//==================================================================================================================//
bool CALL_CONVERSION TcpClient::isConnect(){
    return m_connection;
}

//==================================================================================================================//
unsigned int CALL_CONVERSION TcpClient::GetVersion(void){
    return DATA_EXCHANGE_IFACE_VERSION;
}

//==================================================================================================================//
const char * CALL_CONVERSION TcpClient::GetId(void){
    return DATA_EXCHANGE_IFACE_ID;
}

//==================================================================================================================//
bool TcpClient::setConnection(){
    if( state() == QAbstractSocket::UnconnectedState ) {
        connectToHost(m_Ipv4Host, m_port);
        return true;
    }
    return false;
}

//==================================================================================================================//
void TcpClient::slot_readyRead(){
    //Читаем все разом
    QByteArray bytes = readAll();
    //Передаем на зарегистрированных клиентов
    for( int i = 0; i < m_listIDataReceiver.size(); i++ ) {
        m_listIDataReceiver[i]->setData( bytes.data(), bytes.size() );
    }
}

//==================================================================================================================//
void TcpClient::slot_error(QAbstractSocket::SocketError error){
    if( !m_pTimer ) {
        return;
    }
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

    /////////////////////////////////////////// В Qt видемо есть баг - отключение кабеля не вызывает сигнала об ошибке либо дисконекта
    ///
    if( !m_connection ) {
        for( int i = 0; i < m_listIDataReceiver.size(); i++ ) {
            m_listIDataReceiver[i]->Disconnect();
        }
    }

    //
    m_pCoreMainIfaces->GetProtocolIface()->debug( "Ошибка, текст сообщения [%2]", err_str.toStdString().c_str() );
    m_connection = false;

    m_pTimer->start(2000);//Запускаем таймер переподключения
}

//==================================================================================================================//
void TcpClient::slot_connection(){
    m_pCoreMainIfaces->GetProtocolIface()->debug("Соединение с IPv4 [%1] port [%2] установлено", m_Ipv4Host.toStdString().c_str(), m_port);

    m_connection = true;
    for( int i = 0; i < m_listIDataReceiver.size(); i++ ) {
        m_listIDataReceiver[i]->Connnect();
    }
    m_pTimer->start(TIMEOUT_CHECK_CONNECT);//Запускаем таймер проверки состояния подключения
    /////////////////////////////////////////// В Qt видемо есть баг - отключение кабеля не вызывает сигнала об ошибке либо дисконекта
}

//==================================================================================================================//
void TcpClient::slot_disconnection(){
    m_pCoreMainIfaces->GetProtocolIface()->warn("Соединение с IPv4 [%1] port [%2] разорвано", m_Ipv4Host.toStdString().c_str(), m_port);

    if( m_connection ) {
        for( int i = 0; i < m_listIDataReceiver.size(); i++ ) {
            m_listIDataReceiver[i]->Disconnect();
        }
    }
    m_connection = false;
    slot_reconnect();
}

//==================================================================================================================//
void TcpClient::slot_reconnect(){
    m_pTimer->stop();
    if( m_connection && state() == QAbstractSocket::ConnectedState ) {
        m_pTimer->start(TIMEOUT_CHECK_CONNECT);//Запускаем таймер проверки состояния подключения
        /////////////////////////////////////////// В Qt видемо есть баг - отключение кабеля не вызывает сигнала об ошибке либо дисконекта
        return;
    }

    m_connection = false;
    setConnection();
}

//==================================================================================================================//
void CALL_CONVERSION TcpClient::write(const char* data, int size){
    if( m_connection && state() == QAbstractSocket::ConnectedState ) {
        writeData( data, size );
    }
}

//==================================================================================================================//

#include "tcp_client.moc"
