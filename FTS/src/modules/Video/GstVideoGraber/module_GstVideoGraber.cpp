#include "module_GstVideoGraber.h"

#include "../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../include/ifaces/main/logger_iface.h"
#include "../../../../include/ifaces/main/modules_service_iface.h"
#include "../../../../include/ifaces/main/settings_iface.h"
#include "../../../../include/ifaces/main/widgets_manipulator_iface.h"

#include <stdio.h>
#include <assert.h>

//==================================================================================================================//



//==================================================================================================================//
ModuleGstVideoGraber::ModuleGstVideoGraber() {
    m_pCoreMainIfaces = 0;
    m_pGstVideoGraber = 0;

}

ModuleGstVideoGraber::~ModuleGstVideoGraber() {
}

//==================================================================================================================//
void CALL_CONVERSION ModuleGstVideoGraber::Initialize (FTS::Ifaces::ICoreMainIfaces *InCoreMainIfaces ) {
    /*
     * Данная функция вызывается во время установки модуля в ядро, не рекомендую здесь выполнять какие-либо действия
     * лучше их выполнить во время старта модуля
     */
    m_pCoreMainIfaces = InCoreMainIfaces;
    assert(m_pCoreMainIfaces);
}

//==================================================================================================================//
void CALL_CONVERSION ModuleGstVideoGraber::Start ( void ) {
    /*
     * Желательно загрузку аргументов и конфигураций делать именно во время старта модуля и именно в этом порядке, настоятельно не рекомендую
     * перетаскивать эти функции в функцию инициализации модуля, но в исключительных случаях может пригодится ( будьте внимательны )
     * функции желательно вызывать непосредственно перед создание объекта
     */
    LoadArguments();
    LoadConfiguration();
    LoadExportedInterfaces();
    if( !m_pGstVideoGraber ){
        m_pGstVideoGraber = new GstVideoGraber(m_pCoreMainIfaces);
        m_pGstVideoGraber->init();
    }

}

//==================================================================================================================//
void CALL_CONVERSION ModuleGstVideoGraber::Stop ( void ) {
    m_pGstVideoGraber->StopVideo();
    /*
     * Функция будет вызвына ядром при получении сигнала завершения работы, перед вызовом Release
     * для коректного завершения модуля рекомендуется все необходимые действия выполнить здесь
     * (очень удобно, если класс реализует потоки, которые необходимо закрыть, перед выходом из проги)
     */

}

//==================================================================================================================//
FTS::Ifaces::IExportIface *ModuleGstVideoGraber::GetExportedIface( const char* InIfaceId, const unsigned int InIfaceVersion ) {
    /*
     * Тело данной функции будет вызываться в момент, когда сторонний модуль попытается получить объект класса, который реализует
     * нужный интерфейс
     */
    if ( m_pCoreMainIfaces ) {
        if ( InIfaceId ) {
            if ( QString ( InIfaceId ) == VIDEO_RECEIVER_IFACE_ID && InIfaceVersion == VIDEO_RECEIVER_IFACE_VERSION ) {
                if( !m_pGstVideoGraber ){
                    m_pGstVideoGraber = new GstVideoGraber(m_pCoreMainIfaces);
                    m_pGstVideoGraber->init();
                }
                return m_pGstVideoGraber;
            }
        }
    }
    return NULL;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleGstVideoGraber::Release ( void ) {
    delete m_pGstVideoGraber;
    m_pGstVideoGraber = 0;
    delete this;
}

//==================================================================================================================//
void ModuleGstVideoGraber::LoadArguments() {
/*
 * получать список аргументов можно и внутри реализуемого класса, так как вы передаёте в него (в идеале)
 * интерфейс ядра, который предоставляет возможность получить весь нужный инструментарий
 * чаще всего это даже будет правильнее
 */
/*
    FTS::Ifaces::ISettings *args = m_pCoreMainIfaces->GetArgumentsGetterIface();
    if (args) {
        args->BeginGroup("");
        args->EndGroup();
        args->Sync();
    }
*/
}

//==================================================================================================================//
void ModuleGstVideoGraber::LoadConfiguration() {
    /*
     * получать список конфигураций можно и внутри реализуемого класса, так как вы передаёте в него (в идеале)
     * интерфейс ядра, который предоставляет возможность получить весь нужный инструментарий
     * чаще всего это даже будет правильнее
     */
/*
    FTS::Ifaces::ISettings* cfg = m_pCoreMainIfaces->GetSettingsIface();
    if ( cfg ) {
        cfg->BeginGroup("");
        cfg->EndGroup();
        cfg->Sync();
    }
*/
}

//==================================================================================================================//
void ModuleGstVideoGraber::LoadExportedInterfaces() {
    /*
     * получать интерфейсы дугих модулей можно и внутри реализуемого класса, так как вы передаёте в него (в идеале)
     * интерфейс ядра, который предоставляет возможность получить весь нужный инструментарий
     * чаще всего это даже будет правильнее
     */
/*
    FTS::Ifaces::IExportIface* exp_iface = 0;
*/
}
