#include "module_GstVideoSender.h"

#include "../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../include/ifaces/main/logger_iface.h"
#include "../../../../include/ifaces/main/modules_service_iface.h"
#include "../../../../include/ifaces/main/settings_iface.h"
#include "../../../../include/ifaces/main/widgets_manipulator_iface.h"

#include <stdio.h>
#include <assert.h>
#include <QThread>

//==================================================================================================================//



//==================================================================================================================//
ModuleGstVideoSender::ModuleGstVideoSender() {
    m_pCoreMainIfaces = 0;
    m_pGstVideoSender = 0;

}

ModuleGstVideoSender::~ModuleGstVideoSender() {
}

//==================================================================================================================//
void CALL_CONVERSION ModuleGstVideoSender::Initialize (FTS::Ifaces::ICoreMainIfaces *InCoreMainIfaces ) {
    /*
     * Данная функция вызывается во время установки модуля в ядро, не рекомендую здесь выполнять какие-либо действия
     * лучше их выполнить во время старта модуля
     */
    m_pCoreMainIfaces = InCoreMainIfaces;
    assert(m_pCoreMainIfaces);
}

//==================================================================================================================//
void CALL_CONVERSION ModuleGstVideoSender::Start ( void ) {
    /*
     * Желательно загрузку аргументов и конфигураций делать именно во время старта модуля и именно в этом порядке, настоятельно не рекомендую
     * перетаскивать эти функции в функцию инициализации модуля, но в исключительных случаях может пригодится ( будьте внимательны )
     * функции желательно вызывать непосредственно перед создание объекта
     */
    LoadArguments();
    LoadConfiguration();
    LoadExportedInterfaces();
    if( !m_pGstVideoSender ){
        m_pGstVideoSender = new GstVideoSender(m_pCoreMainIfaces);
        m_pGstVideoSender->init();
    }

}

//==================================================================================================================//
void CALL_CONVERSION ModuleGstVideoSender::Stop ( void ) {
    m_pGstVideoSender->StopVideo();
    /*
     * Функция будет вызвына ядром при получении сигнала завершения работы, перед вызовом Release
     * для коректного завершения модуля рекомендуется все необходимые действия выполнить здесь
     * (очень удобно, если класс реализует потоки, которые необходимо закрыть, перед выходом из проги)
     */

}

//==================================================================================================================//
FTS::Ifaces::IExportIface *ModuleGstVideoSender::GetExportedIface( const char* InIfaceId, const unsigned int InIfaceVersion ) {
    /*
     * Тело данной функции будет вызываться в момент, когда сторонний модуль попытается получить объект класса, который реализует
     * нужный интерфейс
     */
    if ( m_pCoreMainIfaces ) {
        if ( InIfaceId ) {
            if ( QString ( InIfaceId ) == VIDEO_SENDER_IFACE_ID && InIfaceVersion == VIDEO_SENDER_IFACE_VERSION ) {
                if( !m_pGstVideoSender ){
                    m_pGstVideoSender = new GstVideoSender(m_pCoreMainIfaces);
                    m_pGstVideoSender->init();
                }
                return m_pGstVideoSender;
            }
        }
    }
    return NULL;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleGstVideoSender::Release ( void ) {
    delete m_pGstVideoSender;
    m_pGstVideoSender = 0;
    delete this;
}

//==================================================================================================================//
void ModuleGstVideoSender::LoadArguments() {
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
void ModuleGstVideoSender::LoadConfiguration() {
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
void ModuleGstVideoSender::LoadExportedInterfaces() {
    /*
     * получать интерфейсы дугих модулей можно и внутри реализуемого класса, так как вы передаёте в него (в идеале)
     * интерфейс ядра, который предоставляет возможность получить весь нужный инструментарий
     * чаще всего это даже будет правильнее
     */
/*
    FTS::Ifaces::IExportIface* exp_iface = 0;
*/
}
