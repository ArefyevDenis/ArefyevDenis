#include "module_udp_client.h"

#include "../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../include/ifaces/main/logger_iface.h"
#include "../../../../include/ifaces/main/modules_service_iface.h"
#include "../../../../include/ifaces/main/settings_iface.h"

#include <iostream>


const QString CONNECT_PARAM_SECTION  = "PARAM_SECTION";
const QString UDP_DST_HOST           = "UDP_DST_HOST";
const QString UDP_DST_PORT           = "UDP_DST_PORT";
const QString UDP_SRC_HOST           = "UDP_SRC_HOST";
const QString UDP_SRC_PORT           = "UDP_SRC_PORT";
const QString UDP_MCAST              = "UDP_MCAST";

const QString INFO_SECTION          = "INFO_SECTION";
const QString INFO_TEXT             = "INFO_TEXT";
const QString TEXT                  = "Адресный прием данных - задаем UDP_SRC_HOST и UDP_SRC_PORT. "
                                      "BroadCast прием данных - задать UDP_SRC_PORT. "
                                      "Адресная передача данных - задаем UDP_DST_HOST и UDP_DST_PORT либо передача на отправителя инициализируется при получении данных при этом UDP_DST_HOST и _PORT не задаем. "
                                      "BroadCast передача данных - задаем тольно UDP_DST_PORT. UDP_MCAST - включает Multicast прием данных";


//==================================================================================================================//
ModuleUdpClient::ModuleUdpClient(){
    m_pCoreMainIfaces = 0;

    m_host_src = QString("");
    m_port_src = 0;
    m_host_dst = QString("");
    m_port_dst = 0;
    m_mcast = false;

    m_pUdpClient = 0;
}

//==================================================================================================================//
ModuleUdpClient::~ModuleUdpClient(){
    if( m_pUdpClient )
        delete m_pUdpClient;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleUdpClient::Initialize( FTS::Ifaces::ICoreMainIfaces* InCoreMainIfaces ){
    m_pCoreMainIfaces = InCoreMainIfaces;
    assert(m_pCoreMainIfaces);
    LoadArguments();
    LoadConfiguration();


}

//==================================================================================================================//
void CALL_CONVERSION ModuleUdpClient::Start( void ){
    LoadExportedInterfaces();

//для отладки... Создавать будем, если кому-то будем нужны
//    if( m_pUdpClient == 0 ){
//        m_pUdpClient  = new UdpClient(m_pCoreMainIfaces, m_host_src, m_port_src, m_host_dst, m_port_dst, m_mcast);
//    }

}

//==================================================================================================================//
void CALL_CONVERSION ModuleUdpClient::Stop( void ){
}

//==================================================================================================================//
FTS::Ifaces::IExportIface *ModuleUdpClient::GetExportedIface( const char* InIfaceId, const unsigned int InIfaceVersion ){
    FTS::Ifaces::IExportIface* res = 0;

    if ( m_pCoreMainIfaces ) {
        if ( InIfaceId ) {
            if ( QString ( InIfaceId ) == DATA_EXCHANGE_IFACE_ID && InIfaceVersion == DATA_EXCHANGE_IFACE_VERSION ) {
                if( m_pUdpClient == 0 )
                    m_pUdpClient = new UdpClient(m_pCoreMainIfaces, m_host_src, m_port_src, m_host_dst, m_port_dst, m_mcast);
                res = m_pUdpClient;
            }
        }
    }
    return res;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleUdpClient::Release( void ){
    delete this;
}

//==================================================================================================================//
void ModuleUdpClient::LoadArguments(){
/*    FTS::Interfaces::ISettings *args = m_pCoreMainIfaces->GetArgumentsGetterIface();
    if( args ) {

    }*/
}

//==================================================================================================================//
void ModuleUdpClient::LoadConfiguration(){
    FTS::Ifaces::ISettings *cfg = m_pCoreMainIfaces->GetSettingsIface();
    assert(cfg);

    cfg->BeginGroup( CONNECT_PARAM_SECTION );

    m_host_dst = cfg->Value(UDP_DST_HOST, m_host_dst).toString();
    m_port_dst = cfg->Value(UDP_DST_PORT, m_port_dst).toUInt();
    m_host_src = cfg->Value(UDP_SRC_HOST, m_host_src).toString();
    m_port_src = cfg->Value(UDP_SRC_PORT, m_port_src).toUInt();
    m_mcast = cfg->Value(UDP_MCAST, m_mcast).toBool();



    cfg->SetValue(UDP_DST_HOST, m_host_dst);
    cfg->SetValue(UDP_DST_PORT, m_port_dst);
    cfg->SetValue(UDP_SRC_HOST, m_host_src);
    cfg->SetValue(UDP_SRC_PORT, m_port_src);
    cfg->SetValue(UDP_MCAST, m_mcast);

    cfg->EndGroup();

    cfg->BeginGroup( INFO_SECTION );
    cfg->SetValue(INFO_TEXT, TEXT);
    cfg->EndGroup();

    cfg->Sync();
}

//==================================================================================================================//
void ModuleUdpClient::LoadExportedInterfaces(){
}

//==================================================================================================================//

