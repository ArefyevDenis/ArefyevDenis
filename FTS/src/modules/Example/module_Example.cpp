#include "module_Example.h"

#include "../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../include/ifaces/main/logger_iface.h"
#include "../../../../include/ifaces/main/modules_service_iface.h"
#include "../../../../include/ifaces/main/settings_iface.h"
#include "../../../../include/ifaces/main/widgets_manipulator_iface.h"
#include <stdio.h>

#include"../../../../include/ifaces/modules/DataExchanger/data_exchange_iface.h"


//==================================================================================================================//
const char* const LIBS_SECTION = "LIBS_SERVER";

const char* const TCP_SERVER_LIB = "TCP_SERVER_LIB";
const char* const TCP_CLIENT_LIB = "TCP_CLIENT_LIB";




//==================================================================================================================//
ModuleExample::ModuleExample() {
    m_pCoreMainIfaces = 0;
    m_pExample = 0;

    //просто для примера
    m_libTcpServerDataExchanger = QString("libDataExchanger");
    m_libTcpClientDataExchanger = QString("libDataExchanger");
    m_pTcpServer = 0;
    m_pTcpClient = 0;
}

ModuleExample::~ModuleExample() {
}

//==================================================================================================================//
void CALL_CONVERSION ModuleExample::Initialize (FTS::Ifaces::ICoreMainIfaces *InCoreMainIfaces ) {
    /*
     * Данная функция вызывается во время установки модуля в ядро, не рекомендую здесь выполнять какие-либо действия
     * лучше их выполнить во время старта модуля
     */
    m_pCoreMainIfaces = InCoreMainIfaces;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleExample::Start ( void ) {
    /*
     * Желательно загрузку аргументов и конфигураций делать именно во время старта модуля и именно в этом порядке, настоятельно не рекомендую
     * перетаскивать эти функции в функцию инициализации модуля, но в исключительных случаях может пригодится ( будьте внимательны )
     * функции желательно вызывать непосредственно перед создание объекта
     */
    LoadArguments();
    LoadConfiguration();
    LoadExportedInterfaces();
}

//==================================================================================================================//
void CALL_CONVERSION ModuleExample::Stop ( void ) {
    /*
     * Функция будет вызвына ядром при получении сигнала завершения работы, перед вызовом Release
     * для коректного завершения модуля рекомендуется все необходимые действия выполнить здесь
     * (очень удобно, если класс реализует потоки, которые необходимо закрыть, перед выходом из проги)
     */

}

//==================================================================================================================//
FTS::Ifaces::IExportIface *ModuleExample::GetExportedIface( const char* InIfaceId, const unsigned int InIfaceVersion ) {
    /*
     * Тело данной функции будет вызываться в момент, когда сторонний модуль попытается получить объект класса, который реализует
     * нужный интерфейс
     */
    if ( m_pCoreMainIfaces ) {
        if ( InIfaceId ) {
            if ( QString ( InIfaceId ) == EXAMPLE_IFACE_ID && InIfaceVersion == EXAMPLE_IFACE_VERSION ) {
                if( !m_pExample )
                    m_pExample = new Example(m_pCoreMainIfaces);
                return m_pExample;
            }
        }
    }
    return NULL;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleExample::Release ( void ) {
    delete this;
}

//==================================================================================================================//
void ModuleExample::LoadArguments() {
/*
 * получать список аргументов можно и внутри реализуемого класса, так как вы передаёте в него (в идеале)
 * интерфейс ядра, который предоставляет возможность получить весь нужный инструментарий
 * чаще всего это даже будет правильнее
 */
  FTS::Ifaces::ISettings *args = m_pCoreMainIfaces->GetArgumentsGetterIface();
    if (args) {
        args->BeginGroup(LIBS_SECTION);

        //попробуем найти необходимое поле и его значение
        m_libTcpServerDataExchanger = args->Value(TCP_SERVER_LIB, m_libTcpServerDataExchanger).toString();
        m_libTcpClientDataExchanger = args->Value(TCP_CLIENT_LIB, m_libTcpClientDataExchanger).toString();

        // перезапишем
        args->SetValue(TCP_SERVER_LIB, m_libTcpServerDataExchanger);
        args->SetValue(TCP_CLIENT_LIB, m_libTcpClientDataExchanger);

        args->EndGroup();
        args->Sync();
    }

}

//==================================================================================================================//
void ModuleExample::LoadConfiguration() {
    /*
     * получать список конфигураций можно и внутри реализуемого класса, так как вы передаёте в него (в идеале)
     * интерфейс ядра, который предоставляет возможность получить весь нужный инструментарий
     * чаще всего это даже будет правильнее
     */

    FTS::Ifaces::ISettings* cfg = m_pCoreMainIfaces->GetSettingsIface();
    if ( cfg ) {
        cfg->BeginGroup("");
        cfg->EndGroup();
        cfg->Sync();
    }
}

//==================================================================================================================//
void ModuleExample::LoadExportedInterfaces() {
    /*
     * получать интерфейсы дугих модулей можно и внутри реализуемого класса, так как вы передаёте в него (в идеале)
     * интерфейс ядра, который предоставляет возможность получить весь нужный инструментарий
     * чаще всего это даже будет правильнее
     */

    FTS::Ifaces::IExportIface* exp_iface = 0;

    //Вытяним TcpServer
    exp_iface = m_pCoreMainIfaces->GetModulesServiceIface()->GetExportIface(m_libTcpServerDataExchanger.toStdString().c_str(), DATA_EXCHANGE_IFACE_ID, DATA_EXCHANGE_IFACE_VERSION);
    if (exp_iface){
        m_pTcpServer = dynamic_cast<IDataExchange*>(exp_iface);
        m_pCoreMainIfaces->GetProtocolIface()->debug("Успешно получен интерфейс [ %1 ] версии [ %2 ] из модуля [ %3 ]", DATA_EXCHANGE_IFACE_ID, DATA_EXCHANGE_IFACE_VERSION,
                                                     m_libTcpServerDataExchanger.toStdString().c_str());
    } else {
        m_pCoreMainIfaces->GetProtocolIface()->error("Не смог получить интерфейс [ %1 ] версии [ %2 ] из модуля [ %3 ]",DATA_EXCHANGE_IFACE_ID, DATA_EXCHANGE_IFACE_VERSION,
                                                     m_libTcpServerDataExchanger.toStdString().c_str());
    }
    //Вытяним TcpClient
    exp_iface = m_pCoreMainIfaces->GetModulesServiceIface()->GetExportIface(m_libTcpClientDataExchanger.toStdString().c_str(), DATA_EXCHANGE_IFACE_ID, DATA_EXCHANGE_IFACE_VERSION);
    if (exp_iface){
        m_pTcpClient = dynamic_cast<IDataExchange*>(exp_iface);
        m_pCoreMainIfaces->GetProtocolIface()->debug("Успешно получен интерфейс [ %1 ] версии [ %2 ] из модуля [ %3 ]", DATA_EXCHANGE_IFACE_ID, DATA_EXCHANGE_IFACE_VERSION,
                                                     m_libTcpClientDataExchanger.toStdString().c_str());
    } else {
        m_pCoreMainIfaces->GetProtocolIface()->error("Не смог получить интерфейс [ %1 ] версии [ %2 ] из модуля [ %3 ]",DATA_EXCHANGE_IFACE_ID, DATA_EXCHANGE_IFACE_VERSION,
                                                     m_libTcpClientDataExchanger.toStdString().c_str());
    }
}
