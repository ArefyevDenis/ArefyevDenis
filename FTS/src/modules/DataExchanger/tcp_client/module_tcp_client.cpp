#include "module_tcp_client.h"

#include "../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../include/ifaces/main/logger_iface.h"
#include "../../../../include/ifaces/main/modules_service_iface.h"
#include "../../../../include/ifaces/main/settings_iface.h"

#include <iostream>


//==================================================================================================================//
const QString CONNECT_PARAM_SECTION = "PARAM_SECTION";
const QString TCP_HOST              = "TCP_HOST";
const QString TCP_PORT              = "TCP_PORT";

//==================================================================================================================//
ModuleTcpClient::ModuleTcpClient(){
    m_pCoreMainIfaces = 0;
    m_pTcpClient = 0;
}

//==================================================================================================================//
ModuleTcpClient::~ModuleTcpClient(){
    if( m_pTcpClient )
        delete m_pTcpClient;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleTcpClient::Initialize(FTS::Ifaces::ICoreMainIfaces *InCoreMainIfaces ){
    m_pCoreMainIfaces = InCoreMainIfaces;

    // загрузку конфигов вызовем в инициализации, чтобы к моменту, когда кто-то запросит наш интерфейс у нас были
    // адресса, на которых поднимаем сервер
    LoadArguments();
    LoadConfiguration();
}

//==================================================================================================================//
void CALL_CONVERSION ModuleTcpClient::Start( void ){
    LoadExportedInterfaces();

//для отладки... Создавать будем, если кому-то будем нужны
//    if( m_pTcpClient == 0 ){
//        m_pTcpClient  = new TcpClient(m_pCoreMainIfaces, m_Ipv4Host, m_port);
//    }

}

//==================================================================================================================//
void CALL_CONVERSION ModuleTcpClient::Stop( void ){
}

//==================================================================================================================//
FTS::Ifaces::IExportIface *ModuleTcpClient::GetExportedIface( const char* InIfaceId, const unsigned int InIfaceVersion ){
    FTS::Ifaces::IExportIface* res = 0;

    if ( m_pCoreMainIfaces ) {
        if ( InIfaceId ) {
            if ( QString ( InIfaceId ) == DATA_EXCHANGE_IFACE_ID && InIfaceVersion == DATA_EXCHANGE_IFACE_VERSION ) {
                if( m_pTcpClient == 0 ){
                    m_pTcpClient  = new TcpClient(m_pCoreMainIfaces, m_Ipv4Host, m_port);
                }
                res = m_pTcpClient;
            }
        }
    }
    return res;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleTcpClient::Release( void ){
    delete this;
}

//==================================================================================================================//
void ModuleTcpClient::LoadArguments(){
}

//==================================================================================================================//
void ModuleTcpClient::LoadConfiguration(){
    FTS::Ifaces::ISettings *cfg = m_pCoreMainIfaces->GetSettingsIface();
    assert(cfg);

    cfg->BeginGroup( CONNECT_PARAM_SECTION );

    m_Ipv4Host = cfg->Value(TCP_HOST, m_Ipv4Host).toString();
    m_port = cfg->Value(TCP_PORT, m_port).toUInt();

    cfg->SetValue(TCP_HOST, m_Ipv4Host);
    cfg->SetValue(TCP_PORT, m_port);

    cfg->EndGroup();

    cfg->Sync();
}

//==================================================================================================================//
void ModuleTcpClient::LoadExportedInterfaces(){
}
