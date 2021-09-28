#include "module_VideoThreadTest.h"

#include "../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../include/ifaces/main/logger_iface.h"
#include "../../../../include/ifaces/main/modules_service_iface.h"
#include "../../../../include/ifaces/main/settings_iface.h"
#include "../../../../include/ifaces/main/widgets_manipulator_iface.h"
#include <stdio.h>

#include"../../../../include/ifaces/modules/DataExchanger/data_exchange_iface.h"


//==================================================================================================================//
ModuleVideoThreadTest::ModuleVideoThreadTest() {
    m_pCoreMainIfaces = 0;
    m_pVideoThreadTest = 0;

}

ModuleVideoThreadTest::~ModuleVideoThreadTest() {
}

//==================================================================================================================//
void CALL_CONVERSION ModuleVideoThreadTest::Initialize (FTS::Ifaces::ICoreMainIfaces *InCoreMainIfaces ) {
    /*
     * Данная функция вызывается во время установки модуля в ядро, не рекомендую здесь выполнять какие-либо действия
     * лучше их выполнить во время старта модуля
     */
    m_pCoreMainIfaces = InCoreMainIfaces;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleVideoThreadTest::Start ( void ) {
    /*
     * Желательно загрузку аргументов и конфигураций делать именно во время старта модуля и именно в этом порядке, настоятельно не рекомендую
     * перетаскивать эти функции в функцию инициализации модуля, но в исключительных случаях может пригодится ( будьте внимательны )
     * функции желательно вызывать непосредственно перед создание объекта
     */
    LoadArguments();
    LoadConfiguration();
    LoadExportedInterfaces();
    if( !m_pVideoThreadTest ){
        m_pVideoThreadTest = new VideoThreadTest(m_pCoreMainIfaces);
        m_pVideoThreadTest->init_and_start();
    }

}

//==================================================================================================================//
void CALL_CONVERSION ModuleVideoThreadTest::Stop ( void ) {
    /*
     * Функция будет вызвына ядром при получении сигнала завершения работы, перед вызовом Release
     * для коректного завершения модуля рекомендуется все необходимые действия выполнить здесь
     * (очень удобно, если класс реализует потоки, которые необходимо закрыть, перед выходом из проги)
     */

}

//==================================================================================================================//
FTS::Ifaces::IExportIface *ModuleVideoThreadTest::GetExportedIface( const char* InIfaceId, const unsigned int InIfaceVersion ) {
    /*
     * Тело данной функции будет вызываться в момент, когда сторонний модуль попытается получить объект класса, который реализует
     * нужный интерфейс
     */
    if ( m_pCoreMainIfaces ) {
        if ( InIfaceId ) {
            if ( QString ( InIfaceId ) == VIDEO_THREAD_TEST_IFACE_ID && InIfaceVersion == VIDEO_THREAD_TEST_IFACE_VERSION ) {
                if( !m_pVideoThreadTest ){
                    m_pVideoThreadTest = new VideoThreadTest(m_pCoreMainIfaces);
                }
                return m_pVideoThreadTest;
            }
        }
    }
    return NULL;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleVideoThreadTest::Release ( void ) {
    delete this;
}

//==================================================================================================================//
void ModuleVideoThreadTest::LoadArguments() {
/*
 * получать список аргументов можно и внутри реализуемого класса, так как вы передаёте в него (в идеале)
 * интерфейс ядра, который предоставляет возможность получить весь нужный инструментарий
 * чаще всего это даже будет правильнее
 */

  FTS::Ifaces::ISettings *args = m_pCoreMainIfaces->GetArgumentsGetterIface();
    if (args) {
        args->BeginGroup("");
        args->EndGroup();
        args->Sync();
    }
}

//==================================================================================================================//
void ModuleVideoThreadTest::LoadConfiguration() {
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
void ModuleVideoThreadTest::LoadExportedInterfaces() {
    /*
     * получать интерфейсы дугих модулей можно и внутри реализуемого класса, так как вы передаёте в него (в идеале)
     * интерфейс ядра, который предоставляет возможность получить весь нужный инструментарий
     * чаще всего это даже будет правильнее
     */

    FTS::Ifaces::IExportIface* exp_iface = 0;
}
