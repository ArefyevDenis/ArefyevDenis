#include "udp_client.h"
#include "../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../include/ifaces/main/logger_iface.h"

#include <stdint.h>
#include <QTimer>
#include <iostream>


//==================================================================================================================//
UdpClient::UdpClient(FTS::Ifaces::ICoreMainIfaces *InCoreMainIfaces, QString host_src, unsigned int port_src, QString host_dst, unsigned int port_dst, bool mcast):
    QUdpSocket(),
    m_pCoreMainIfaces(InCoreMainIfaces),
    m_host_src(host_src),
    m_port_src(port_src),
    m_host_dst(host_dst),
    m_port_dst(port_dst),
    m_mcast(mcast){

    m_connection = false;
    m_pTimer = new QTimer();
    connect( m_pTimer, SIGNAL(timeout()), SLOT(slot_reconnect()), Qt::DirectConnection );
    connect ( this, SIGNAL ( readyRead() ), SLOT ( slot_readyRead() ) );
    connect ( this, SIGNAL ( error( QAbstractSocket::SocketError ) ), SLOT ( slot_error( QAbstractSocket::SocketError ) ) );
    setConnection();

}

//==================================================================================================================//
UdpClient::~UdpClient(){
    close();
}

//==================================================================================================================//
void CALL_CONVERSION UdpClient::setIDataReceiver(IDataReceiver *InIDataReceiver){
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
void CALL_CONVERSION UdpClient::delIDataReceiver( IDataReceiver *InIDataRceiver ){
    for( QList<IDataReceiver*>::iterator it = m_listIDataReceiver.begin(); it != m_listIDataReceiver.end(); it++ ) {
        if( (*it) == InIDataRceiver ) {
            it = m_listIDataReceiver.erase( it );
            break;
        }
    }
}

//==================================================================================================================//
bool CALL_CONVERSION UdpClient::isConnect(){
    return m_connection;
}

//==================================================================================================================//
unsigned int CALL_CONVERSION UdpClient::GetVersion(void){
    return DATA_EXCHANGE_IFACE_VERSION;
}

//==================================================================================================================//
const char * CALL_CONVERSION UdpClient::GetId(void){
    return DATA_EXCHANGE_IFACE_ID;
}

//==================================================================================================================//
bool UdpClient::setConnection(){
    bool res = false;
    if( !m_mcast ) {
        if( m_host_src.isEmpty() ) {
            res = bind( m_port_src, QUdpSocket::ShareAddress );
        } else {
            res = bind( QHostAddress(m_host_src), m_port_src, QUdpSocket::ShareAddress );
        }
    } else {
        if( !m_host_src.isEmpty() ) {
            res = bind(QHostAddress::AnyIPv4, m_port_src, QUdpSocket::ShareAddress );
            res = joinMulticastGroup(QHostAddress(m_host_src));
        }
    }
    if( res ){
        m_connection = true;
        m_pCoreMainIfaces->GetProtocolIface()->debug("Udp - порт успешно открыт на прослушивание IpV4 [%1] port [%2] multicast [%3]",
                                                 m_host_src.toStdString().c_str(), m_port_src, m_mcast);
    } else {
        m_pCoreMainIfaces->GetProtocolIface()->error("Udp - порт не открыт на прослушивание IpV4 [%1] port [%2] multicast [%3]",
                                                 m_host_src.toStdString().c_str(), m_port_src, m_mcast);
    }
    return res;
}

//==================================================================================================================//
void UdpClient::slot_readyRead(){
    //Проверяем - есть датаграммы готовые для чтения
    while( hasPendingDatagrams() ) {
        QByteArray bytes;
        QHostAddress sender;
        uint16_t portSender;
        //Выставляем размер датаграммы
        bytes.resize( pendingDatagramSize() );
        //Читаем датаграмму
        readDatagram( bytes.data(), bytes.size(), &sender, &portSender );
        if( m_port_dst == 0 ) {
            m_port_dst = portSender;
            if( m_host_dst.isEmpty() ) {
                m_host_dst = sender.toString();
            }
        }
        //Передаем на зарегистрированных клиентов
        for( int i = 0; i < m_listIDataReceiver.size(); i++ ) {
            m_listIDataReceiver[i]->setData( bytes.data(), bytes.size() );
        }
    }
}

//==================================================================================================================//
void UdpClient::slot_error(QAbstractSocket::SocketError error){
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

    m_pCoreMainIfaces->GetProtocolIface()->debug( "Ошибка, текст сообщения [%2]", err_str.toStdString().c_str() );
    m_connection = false;

    m_pTimer->start(2000);//Запускаем таймер переподключения
    if( !m_connection ) {
        for( int i = 0; i < m_listIDataReceiver.size(); i++ ) {
            m_listIDataReceiver[i]->Disconnect();
        }
    }
}

//==================================================================================================================//
void UdpClient::slot_connection(){
    m_connection = true;
    for( int i = 0; i < m_listIDataReceiver.size(); i++ ) {
        m_listIDataReceiver[i]->Connnect();
    }
}

//==================================================================================================================//
void UdpClient::slot_disconnection(){
    if( m_connection ) {
        for( int i = 0; i < m_listIDataReceiver.size(); i++ ) {
            m_listIDataReceiver[i]->Disconnect();
        }
    }
    m_connection = false;
    if( m_pTimer ) {
        if( !m_pTimer->isActive() )
            m_pTimer->start( 2000 );
    }
}

//==================================================================================================================//
void UdpClient::slot_reconnect(){
    if( m_pTimer ) {
        if( m_pTimer->isActive() )
            m_pTimer->stop();
    }
    setConnection();
}

//==================================================================================================================//
void CALL_CONVERSION UdpClient::write(const char* data, int size){
    if( m_connection ) {
        if( m_host_dst.isEmpty() ) {
            writeDatagram( data, size, QHostAddress::Broadcast, m_port_dst );
        } else {
            writeDatagram( data, size, QHostAddress(m_host_dst), m_port_dst );
        }
    }
}

//==================================================================================================================//

#include "udp_client.moc"
