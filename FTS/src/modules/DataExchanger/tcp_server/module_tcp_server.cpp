
#include <assert.h>
#include <iostream>

#include "../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../include/ifaces/main/logger_iface.h"
#include "../../../../include/ifaces/main/modules_service_iface.h"
#include "../../../../include/ifaces/main/settings_iface.h"

#include "tcp_server.h"

#include "module_tcp_server.h"



//==================================================================================================================//
const char* const BASE_SECTION                      = "TCP_SERVER";
const char* const CFG_LISTEN_IPv4_INTERFACE_ADDR    = "LISTEN_IPv4_INTERFACE_ADDR";
const char* const CFG_LISTEN_PORT                   = "LISTEN_PORT";

//==================================================================================================================//
ModuleTcpServer::ModuleTcpServer( void ):
    m_pCoreMainIfaces( 0 ),
    m_pTcpServer( 0 ),
    m_Ipv4ListenIface( "0.0.0.0" ),
    m_ListenPort( 0 ){
}

//==================================================================================================================//
ModuleTcpServer::~ModuleTcpServer( void ){
}

//==================================================================================================================//
void CALL_CONVERSION ModuleTcpServer::Initialize( FTS::Ifaces::ICoreMainIfaces* InCoreMainfaces ){
    assert( InCoreMainfaces );

    m_pCoreMainIfaces = InCoreMainfaces;

    // загрузку конфигов вызовем в инициализации, чтобы к моменту, когда кто-то запросит наш интерфейс у нас были
    // адресса, на которых поднимаем сервер
    LoadArguments();
    LoadConfiguration();
}

//==================================================================================================================//
void CALL_CONVERSION ModuleTcpServer::Start( void ){
    LoadExportedInterfaces();

//для отладки... Создавать будем, если кому-то будем нужны
//    if ( !m_pTcpServer ) {
//        m_pTcpServer = new TcpServer(m_pCoreMainIfaces, m_Ipv4ListenIface, m_ListenPort);
//    }

}

//==================================================================================================================//
void CALL_CONVERSION ModuleTcpServer::Stop( void ){
    if( m_pTcpServer ){
        delete m_pTcpServer;
        m_pTcpServer = 0;
    }
}

//==================================================================================================================//
FTS::Ifaces::IExportIface* CALL_CONVERSION ModuleTcpServer::GetExportedIface( const char* InIfaceId, const unsigned int InIfaceVersion ){
    FTS::Ifaces::IExportIface* res = 0;

    if ( m_pCoreMainIfaces ){
        if ( InIfaceId ){
            if ( QString ( InIfaceId ) == DATA_EXCHANGE_IFACE_ID && InIfaceVersion == DATA_EXCHANGE_IFACE_VERSION ){
                if( m_pTcpServer == 0 ){
                    m_pTcpServer = new TcpServer( m_pCoreMainIfaces, m_Ipv4ListenIface, m_ListenPort );
                }
                res = m_pTcpServer;
            }
        }
    }
    return res;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleTcpServer::Release( void ){
    delete this;
}

//==================================================================================================================//
void ModuleTcpServer::LoadArguments(){
    FTS::Ifaces::ISettings *args = m_pCoreMainIfaces->GetArgumentsGetterIface();
    if (args) {
        args->BeginGroup("");
        args->EndGroup();
        args->Sync();
    }
}

//==================================================================================================================//
void ModuleTcpServer::LoadConfiguration(){
    FTS::Ifaces::ISettings *cfg = m_pCoreMainIfaces->GetSettingsIface();
    assert( cfg );

    cfg->BeginGroup( BASE_SECTION );

    m_Ipv4ListenIface = cfg->Value( CFG_LISTEN_IPv4_INTERFACE_ADDR, m_Ipv4ListenIface ).toString();
    m_ListenPort = cfg->Value( CFG_LISTEN_PORT, m_ListenPort ).toUInt();

    cfg->SetValue( CFG_LISTEN_IPv4_INTERFACE_ADDR, m_Ipv4ListenIface );
    cfg->SetValue( CFG_LISTEN_PORT, m_ListenPort );

    cfg->EndGroup();

    cfg->Sync();

}

//==================================================================================================================//
void ModuleTcpServer::LoadExportedInterfaces(){
    /*
    FTS::Ifaces::IExportIface* exp_iface = 0;
    exp_iface = m_pCoreMainIfaces->GetModulesServiceIface()->GetExportIface();
    */
}

//==================================================================================================================//
