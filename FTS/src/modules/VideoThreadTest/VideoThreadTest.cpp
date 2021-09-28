#include "VideoThreadTest.h"
#include "assert.h"
#include "../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../include/ifaces/main/logger_iface.h"
#include "../../../../include/ifaces/main/modules_service_iface.h"
#include "../../../../include/ifaces/main/settings_iface.h"

#include "../../../include/ifaces/modules/Video/video_receiver_iface.h"
#include "../../../include/ifaces/modules/Video/video_sender_iface.h"

#include <QString>
#include <QImage>
#include <QFile>
#include <QThread>

//==================================================================================================================//
const QString LIBS_SECTION      = "LIBS_SECTION";
const QString SENDER_LIB        = "SENDER_LIB";
const QString RECEIVER_LIB      = "RECEIVER_LIB";

const QString CONFIG_SECTION    = "CONFIG_SECTION";
const QString REFRESH_RATE      = "REFRESH_RATE";
const QString REFRESH_DEV_MS    = "REFRESH_DEV_MS";
const QString REBOOT_PIP_SEC    = "REBOOT_PIP_SEC";



//================================================== PBULIC ========================================================//
//==================================================================================================================//
VideoThreadTest::VideoThreadTest(FTS::Ifaces::ICoreMainIfaces *pCoreMainIface):
    m_pCoreMainIface(pCoreMainIface),
    m_pVideoReceiver(0),
    m_pVideoSender(0){
    assert(m_pCoreMainIface);

    m_libSender = QString("libVideoSender");
    m_libReceiver = QString("libVideoReceiver");

    m_rate = 25;

    m_base_dev = QString("/dev/video0");
    m_refDev = 1500;

    m_rebootTime = 5;

    m_pTimerRefresh = new QTimer(this);
    connect(m_pTimerRefresh, SIGNAL(timeout()), this, SLOT(refreshImage()));

    m_pTimerDev = new QTimer(this);
    connect(m_pTimerDev, SIGNAL(timeout()), this, SLOT(refreshDev()));

    m_pTimerReboot = new QTimer(this);
    connect(m_pTimerReboot,SIGNAL(timeout()), this, SLOT(rebootPipeline()));

    m_error = false;
}

VideoThreadTest:: ~VideoThreadTest() {
    if (m_pTimerReboot){
        m_pTimerReboot->stop();
    }
    delete m_pTimerReboot;
    m_pTimerReboot = 0;

    if(m_pTimerDev){
        m_pTimerDev->stop();
    }
    delete m_pTimerDev;
    m_pTimerDev = 0;

    if (m_pTimerRefresh){
        m_pTimerRefresh->stop();
    }
    delete m_pTimerRefresh;
    m_pTimerRefresh = 0;

    if (m_pVideoReceiver){
        m_pVideoReceiver->StopVideo();
    }

    if (m_pVideoSender){
        m_pVideoSender->StopVideo();
    }

}

//==================================================================================================================//
const char *CALL_CONVERSION VideoThreadTest::GetId(){
    return VIDEO_THREAD_TEST_IFACE_ID;
}

unsigned int CALL_CONVERSION VideoThreadTest::GetVersion() {
    return VIDEO_THREAD_TEST_IFACE_VERSION;
}

//==================================================================================================================//
void VideoThreadTest::init_and_start(){
    LoadArguments();
    LoadConfiguration();
    LoadExportedInterfaces();

    bool recive = false;
    bool send = false;
    if (m_pVideoReceiver){
        recive = m_pVideoReceiver->StartVideo();
    }
    if (m_pVideoSender){
        send = m_pVideoSender->StartVideo();
    }

    if (recive){
        m_pCoreMainIface->GetProtocolIface()->debug("Поток получения кадров запущен");
    } else {
        m_pCoreMainIface->GetProtocolIface()->error("Ошибка запуска потока получения видео");
    }

    if (send){
        m_pCoreMainIface->GetProtocolIface()->debug("Поток отправки кадров запущен");
    } else {
        m_pCoreMainIface->GetProtocolIface()->error("Ошибка запуска потока отправки видео");
    }

    if (send && recive){
        m_pCoreMainIface->GetProtocolIface()->debug("Запускаю обновление кадров %1/сек",m_rate);
    } else {
        m_pCoreMainIface->GetProtocolIface()->error("Один или несколько потоков не запущены");
    }

    m_pTimerRefresh->start(1000/m_rate);
    m_pTimerDev->start(m_refDev);
    m_pTimerReboot->start(m_rebootTime*1000);

    return;
}

//==================================================================================================================//
void VideoThreadTest::LoadArguments(){
    FTS::Ifaces::ISettings *args = m_pCoreMainIface->GetArgumentsGetterIface();
      if (args) {
          args->BeginGroup(LIBS_SECTION);

          m_libSender = args->Value(SENDER_LIB, m_libSender).toString();
          m_libReceiver = args->Value(RECEIVER_LIB, m_libReceiver).toString();

          args->SetValue(SENDER_LIB, m_libSender);
          args->SetValue(RECEIVER_LIB, m_libReceiver);

          args->EndGroup();
          args->Sync();
      }
}

//==================================================================================================================//
void VideoThreadTest::LoadConfiguration(){
    FTS::Ifaces::ISettings *cfg = m_pCoreMainIface->GetSettingsIface();
    cfg->BeginGroup(CONFIG_SECTION);

    m_rate = cfg->Value(REFRESH_RATE, m_rate).toUInt();
    m_refDev = cfg->Value(REFRESH_DEV_MS, m_refDev).toUInt();
    m_rebootTime = cfg->Value(REBOOT_PIP_SEC, m_rebootTime).toUInt();

    cfg->SetValue(REFRESH_RATE, m_rate);
    cfg->SetValue(REFRESH_DEV_MS, m_refDev);
    cfg->SetValue(REBOOT_PIP_SEC, m_rebootTime);

    cfg->EndGroup();

    cfg->Sync();

}

//==================================================================================================================//
void VideoThreadTest::LoadExportedInterfaces(){
    FTS::Ifaces::IExportIface *exp_iface = 0;

    exp_iface = m_pCoreMainIface->GetModulesServiceIface()->GetExportIface(m_libSender.toStdString().c_str(), VIDEO_SENDER_IFACE_ID, VIDEO_SENDER_IFACE_VERSION);
    if (exp_iface){
        m_pVideoSender = dynamic_cast<IVideoSender*>(exp_iface);
        m_pCoreMainIface->GetProtocolIface()->debug("получен интерфейс модуля отправителя видео [%1] версии [%2] из модуля [%3]",
                                                    VIDEO_SENDER_IFACE_ID,
                                                    VIDEO_SENDER_IFACE_VERSION,
                                                    m_libSender.toStdString().c_str());
    } else {
        m_pCoreMainIface->GetProtocolIface()->error("Не смог получить интерфейс модуля отправителя видео [%1] версии [%2] из модуля [%3]",
                                                    VIDEO_SENDER_IFACE_ID,
                                                    VIDEO_SENDER_IFACE_VERSION,
                                                    m_libSender.toStdString().c_str());
    }

    exp_iface = m_pCoreMainIface->GetModulesServiceIface()->GetExportIface(m_libReceiver.toStdString().c_str(), VIDEO_RECEIVER_IFACE_ID, VIDEO_RECEIVER_IFACE_VERSION);
    if (exp_iface){
        m_pVideoReceiver = dynamic_cast<IVideoReceiver*>(exp_iface);
        m_pCoreMainIface->GetProtocolIface()->debug("получен интерфейс модуля получателя видео [%1] версии [%2] из модуля [%3]",
                                                    VIDEO_RECEIVER_IFACE_ID,
                                                    VIDEO_RECEIVER_IFACE_VERSION,
                                                    m_libReceiver.toStdString().c_str());
    } else {
        m_pCoreMainIface->GetProtocolIface()->error("Не смог получить интерфейс модуля получателя видео [%1] версии [%2] из модуля [%3]",
                                                    VIDEO_RECEIVER_IFACE_ID,
                                                    VIDEO_RECEIVER_IFACE_VERSION,
                                                    m_libReceiver.toStdString().c_str());
    }
}

//==================================================================================================================//
void VideoThreadTest::refreshImage(){
    QImage img;
    if (m_pVideoReceiver){
        img = m_pVideoReceiver->GetCapture();
    }
    if (img.isNull())
        return;    

    if (m_pVideoSender){
        m_pVideoSender->SendCapture(&img);
    }
}

//==================================================================================================================//
void VideoThreadTest::refreshDev(){
    // если не обнаружили устройство
    if ( !QFile::exists(m_base_dev)){
        m_error = true;
    }
    if (m_error){
        m_pTimerRefresh->stop();
        if (m_pVideoReceiver){
            m_pVideoReceiver->StopVideo();
            for (int i = 0; i < 4; i ++){
                QString new_dev = QString("/dev/video%1").arg(i);
                if (m_pVideoReceiver->ChanhgeSource(new_dev)){
                    m_base_dev = new_dev;
                    if (m_pVideoReceiver->StartVideo()){
                        QThread::msleep(2000);
                        m_pTimerRefresh->start(1000/m_rate);
                        m_error = false;
                        break;
                    }
                }
            }
        }
    }
}

//==================================================================================================================//
void VideoThreadTest::rebootPipeline(){
    m_error = true;
}

