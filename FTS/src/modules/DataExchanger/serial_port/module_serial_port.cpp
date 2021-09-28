#include "module_serial_port.h"

#include "../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../include/ifaces/main/logger_iface.h"
#include "../../../../include/ifaces/main/modules_service_iface.h"
#include "../../../../include/ifaces/main/settings_iface.h"

#include <iostream>
#include <assert.h>


//==================================================================================================================//
const QString COM_PARAM_SECTION  = "COM_SECTION";
const QString COM_PORT           = "COM_PORT";
const QString COM_BAUD           = "COM_BAUD";
const QString COM_DATABITS       = "COM_DATABITS";
const QString COM_STOPBITS       = "COM_STOPBITS";
const QString COM_PARITY         = "COM_PARITY";
const QString COM_FLOW_CONTROL   = "COM_FLOW_CONTROL";
//==================================================================================================================//


//==================================================================================================================//
ModuleSerialPort::ModuleSerialPort(){
    m_pCoreMainIfaces = 0;

    m_pSerialPort = 0;
    m_name = QString("/dev/tty");
    m_baud = 115200;
    m_dbits = 8;
    m_sbits = 1;
    m_parity = 0;
    m_fctrl = 0;

}

//==================================================================================================================//
ModuleSerialPort::~ModuleSerialPort(){
    if( m_pSerialPort )
        delete m_pSerialPort;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleSerialPort::Initialize( FTS::Ifaces::ICoreMainIfaces* InCoreMainIfaces ){
    m_pCoreMainIfaces = InCoreMainIfaces;
    assert(m_pCoreMainIfaces);
    LoadArguments();
    LoadConfiguration();
}

//==================================================================================================================//
void CALL_CONVERSION ModuleSerialPort::Start( void ){
    LoadExportedInterfaces();

//для отладки... Создавать будем, если кому-то будем нужны
    if ( m_pSerialPort == 0 ){
        m_pSerialPort = new SerialPort(m_pCoreMainIfaces, m_name, m_baud, m_dbits, m_sbits, m_parity, m_fctrl);
    }
}

//==================================================================================================================//
void CALL_CONVERSION ModuleSerialPort::Stop( void ){
}

//==================================================================================================================//
FTS::Ifaces::IExportIface* CALL_CONVERSION ModuleSerialPort::GetExportedIface( const char* InIfaceId, const unsigned int InIfaceVersion ){
    FTS::Ifaces::IExportIface* res = 0;

    if ( m_pCoreMainIfaces ) {
        if ( InIfaceId ) {
            if ( QString ( InIfaceId ) == DATA_EXCHANGE_IFACE_ID && InIfaceVersion == DATA_EXCHANGE_IFACE_VERSION ) {
                if( m_pSerialPort == 0 )
                    m_pSerialPort = new SerialPort(m_pCoreMainIfaces, m_name, m_baud, m_dbits, m_sbits, m_parity, m_fctrl);
                res = m_pSerialPort;
            }
        }
    }
    return res;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleSerialPort::Release( void ){
    delete this;
}

//==================================================================================================================//
void ModuleSerialPort::LoadArguments(){
}

//==================================================================================================================//
void ModuleSerialPort::LoadConfiguration(){
    FTS::Ifaces::ISettings *cfg = m_pCoreMainIfaces->GetSettingsIface();
    assert(cfg);

    cfg->BeginGroup( COM_PARAM_SECTION );

    m_name = cfg->Value(COM_PORT, m_name).toString();
    m_baud = cfg->Value(COM_BAUD, m_baud).toUInt();
    m_dbits = cfg->Value(COM_DATABITS, m_dbits).toUInt();
    m_sbits = cfg->Value(COM_STOPBITS, m_sbits).toUInt();
    m_parity = cfg->Value(COM_PARITY, m_parity).toUInt();
    m_fctrl = cfg->Value(COM_FLOW_CONTROL, m_fctrl).toUInt();

    cfg->SetValue(COM_PORT, m_name);
    cfg->SetValue(COM_BAUD, m_baud);
    cfg->SetValue(COM_DATABITS, m_dbits);
    cfg->SetValue(COM_STOPBITS, m_sbits);
    cfg->SetValue(COM_PARITY, m_parity);
    cfg->SetValue(COM_FLOW_CONTROL, m_fctrl);

    cfg->EndGroup();

    cfg->Sync();
}

//==================================================================================================================//
void ModuleSerialPort::LoadExportedInterfaces(){
}

//==================================================================================================================//
