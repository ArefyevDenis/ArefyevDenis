#include "GstVideoGraber.h"
#include "../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../include/ifaces/main/logger_iface.h"
#include "../../../../include/ifaces/main/modules_service_iface.h"
#include "../../../../include/ifaces/main/settings_iface.h"
#include "../../../../include/ifaces/main/widgets_manipulator_iface.h"

#include <assert.h>
#include <QString>
#include <QImage>
#include <QMutexLocker>
#include <gst/gstsample.h>
#include <gst/gststructure.h>
#include <QFile>


//==================================================================================================================//
const QString   PARAM_SENDING_SECTION =     "PARAM_VIDEO_SECTION";
const QString   VIDEO_DEVICE =              "VIDEO_DEVICE";
const QString   FRAME_FORMAT =              "FRAME_FORMAT";
const QString   FRAME_WIDTH =               "FRAME_WIDTH";
const QString   FRAME_HEIGHT =              "FRAME_HEIGHT";

//================================================== PBULIC ========================================================//
//==================================================================================================================//
GstVideoGraber::GstVideoGraber(FTS::Ifaces::ICoreMainIfaces *pCoreMainIface):
    m_pCoreMainIface(pCoreMainIface) {
    assert(m_pCoreMainIface);
    m_pPipeline = 0;
    m_pSource = 0;

    m_mutex = new QMutex(QMutex::Recursive);

    m_dev = QString("/dev/video0");
    m_width = 640;
    m_height = 480;
    m_format = QString("image");


    // инициализируем gstreamer
    gst_init(0,0);

}

GstVideoGraber:: ~GstVideoGraber() {

    if (m_pPipeline){
        gst_element_set_state(m_pPipeline, GST_STATE_NULL);
        gst_object_unref(GST_OBJECT(m_pPipeline));
    }
    m_pPipeline = NULL;

    if (m_pSource){
        gst_object_unref(GST_OBJECT(m_pSource));
    }
    m_pSource = NULL;

    if (m_mutex){
        delete m_mutex;
    }
    m_mutex = NULL;

    gst_deinit();

}

//==================================================================================================================//
const char *CALL_CONVERSION GstVideoGraber::GetId(){
    return VIDEO_RECEIVER_IFACE_ID;
}

unsigned int CALL_CONVERSION GstVideoGraber::GetVersion() {
    return VIDEO_RECEIVER_IFACE_VERSION;
}


//============================================ из IVdideoReceiver============================================================//
//==========================================================================m_pSource========================================//
bool CALL_CONVERSION GstVideoGraber::ChanhgeSource(QString source){
    if (QFile::exists(source)){
        m_dev = source;
        m_pCoreMainIface->GetProtocolIface()->debug("Успешно изменено имя устройства [%1]",m_dev.toStdString().c_str());
        return true;
    }
    return false;
}

//==================================================================================================================//
 QImage CALL_CONVERSION GstVideoGraber::GetCapture(){
    QMutexLocker locker(m_mutex);
    if (!m_pSource)
        return m_capture;
    GstSample *sample = gst_base_sink_get_last_sample(GST_BASE_SINK(m_pSource));

    // пробуем получить кадр
    if (sample){
        int width = 0, height = 0;
        // получим описание
        GstCaps *caps = gst_sample_get_caps(sample);
        if (caps){
            GstStructure *strct = gst_caps_get_structure(caps,0);
            gst_structure_get_int(strct,"width", &width);
            gst_structure_get_int(strct,"height", &height);
        } else {
            return m_capture;
        }
        // если есть описание, вытяним буфер
        if (width > 0 && height >0 ){
            GstBuffer* buffer = gst_sample_get_buffer(sample);
            if (buffer){
                GstMapInfo info;
                if (gst_buffer_map(buffer, &info, GST_MAP_READ)){
                    if (info.data != 0 ){
                        if (m_format == "raw")
                            m_capture = QImage(info.data, width, height, QImage::Format_ARGB32);
                        if (m_format == "image")
                            m_capture.loadFromData(info.data,info.size,"JPEG");
                    } else {
                        m_pCoreMainIface->GetProtocolIface()->error("data == NULL or BAD SIZE");
                    }
                    gst_buffer_unmap(buffer, &info);
                }
            }
        }
        gst_sample_unref(sample);
    }
    return m_capture;
}

//==================================================================================================================//
bool CALL_CONVERSION GstVideoGraber::StartVideo(){
    QMutexLocker locker(m_mutex);
    // проверим, если уже создавали, то выйдем
    if (m_pPipeline){
        m_pCoreMainIface->GetProtocolIface()->error("Видеоконвеер был создан ранее");
        return false;
    }

    //создадим строку вещяния
    QString gst_str = QString("");
    if (m_format == "raw")
        gst_str = QString(" v4l2src device=%1 io-mode=2 ! video/x-raw, width=%2, height=%3 ! videoconvert ! video/x-raw, format=BGRA ! appsink name=mysink ").arg(m_dev).arg(m_width).arg(m_height);
    if (m_format == "image")
        gst_str = QString(" v4l2src device=%1 io-mode=2 ! image/jpeg, width=%2, height=%3 ! appsink name=mysink ").arg(m_dev).arg(m_width).arg(m_height);

    if (gst_str.isEmpty()){
        m_pCoreMainIface->GetProtocolIface()->error("Формат [%1] неизвестен для данного модуля",m_format.toStdString().c_str());
        return false;
    }

    GError *error = nullptr;
    //создадим конвеер
    m_pPipeline = gst_parse_launch((gchar*)gst_str.toStdString().c_str(), &error);


    //проверим наличие ошибок при создании конвеера
    if (error){
        m_pCoreMainIface->GetProtocolIface()->error("ошибка конвеера gstreamer: [%1] ", error->message);
    }
    if (!m_pPipeline){
        m_pCoreMainIface->GetProtocolIface()->error("Неудалось создать видеоконвеер");
        return false;
    }

    if (m_pSource){
        gst_object_unref(m_pSource);
        m_pSource = nullptr;
    }

    //попробуем получить наш источник, через который будем пихать кадры
    m_pSource = gst_bin_get_by_name(GST_BIN(m_pPipeline),"mysink");
    if (!m_pSource){
        m_pCoreMainIface->GetProtocolIface()->error("Ошибка получения элемента [appsrc]");
        return false;
    }

    //запердолим настрйоки для нашего источника
    gst_app_sink_set_max_buffers(GST_APP_SINK(m_pSource),1);
    gst_app_sink_set_drop(GST_APP_SINK(m_pSource),TRUE);

    //попробуем запустить конвеер
    m_pCoreMainIface->GetProtocolIface()->debug("Переводим конвеер в состояние [GST_STATE_READY]");
    GstStateChangeReturn ret = gst_element_set_state(m_pPipeline, GST_STATE_READY);
    switch (ret) {
    case GST_STATE_CHANGE_FAILURE:{
        m_pCoreMainIface->GetProtocolIface()->error("Ошибка запуска конвеера [GST_STATE_CHANGE_FAILURE]");
        return false;
    }
        break;
    case GST_STATE_CHANGE_SUCCESS:{
        m_pCoreMainIface->GetProtocolIface()->debug("Запуск конвеера [GST_STATE_CHANGE_SUCCESS]");
    }
        break;
    case GST_STATE_CHANGE_ASYNC:{
        m_pCoreMainIface->GetProtocolIface()->debug("Запуск конвеера [GST_STATE_CHANGE_ASYNC]");
    }
        break;
    case GST_STATE_CHANGE_NO_PREROLL:{
        m_pCoreMainIface->GetProtocolIface()->debug("Запуск конвеера [GST_STATE_CHANGE_NO_PREROLL]");
    }
        break;
    default:
        m_pCoreMainIface->GetProtocolIface()->warn("Неизвестное состояние конвеера");
        break;
    }
    m_pCoreMainIface->GetProtocolIface()->debug("Переводим конвеер в состояние [GST_STATE_PLAYING]");
    ret = gst_element_set_state(m_pPipeline, GST_STATE_PLAYING);
    switch (ret) {
    case GST_STATE_CHANGE_FAILURE:{
        m_pCoreMainIface->GetProtocolIface()->error("Ошибка запуска конвеера [GST_STATE_CHANGE_FAILURE]");
        return false;
    }
        break;
    case GST_STATE_CHANGE_SUCCESS:{
        m_pCoreMainIface->GetProtocolIface()->debug("Запуск конвеера [GST_STATE_CHANGE_SUCCESS]");
    }
        break;
    case GST_STATE_CHANGE_ASYNC:{
        m_pCoreMainIface->GetProtocolIface()->debug("Запуск конвеера [GST_STATE_CHANGE_ASYNC]");
    }
        break;
    case GST_STATE_CHANGE_NO_PREROLL:{
        m_pCoreMainIface->GetProtocolIface()->debug("Запуск конвеера [GST_STATE_CHANGE_NO_PREROLL]");
    }
        break;
    default:
        m_pCoreMainIface->GetProtocolIface()->warn("Неизвестное состояние конвеера");
        break;
    }

    return true;
}

//==================================================================================================================//
void CALL_CONVERSION GstVideoGraber::StopVideo(){
    QMutexLocker locker(m_mutex);
    //остановим конвеер и зачистим
    if (m_pPipeline){
        GstStateChangeReturn ret = gst_element_set_state(m_pPipeline, GST_STATE_NULL);
        switch (ret) {
        case GST_STATE_CHANGE_FAILURE:{
            m_pCoreMainIface->GetProtocolIface()->error("Ошибка остановки конвеера [GST_STATE_CHANGE_FAILURE]");
        }
            break;
        case GST_STATE_CHANGE_SUCCESS:{
            m_pCoreMainIface->GetProtocolIface()->debug("Остановка конвеера [GST_STATE_CHANGE_SUCCESS]");
        }
            break;
        default:
            m_pCoreMainIface->GetProtocolIface()->warn("Неизвестное состояние конвеера");
            break;
        }

        gst_object_unref(GST_OBJECT(m_pPipeline));
    }
    m_pPipeline = NULL;

    if (m_pSource){
        gst_object_unref(GST_OBJECT(m_pSource));
    }
    m_pSource = NULL;

    m_pCoreMainIface->GetProtocolIface()->debug("Конвеер успешно остановлен");
    return;
}

//==================================================================================================================//
void GstVideoGraber::init(){
    FTS::Ifaces::ISettings* cfg = m_pCoreMainIface->GetSettingsIface();
    if (cfg){
        cfg->BeginGroup(PARAM_SENDING_SECTION);

        m_dev = cfg->Value(VIDEO_DEVICE, m_dev).toString();
        m_format = cfg->Value(FRAME_FORMAT, m_format).toString();
        m_width = cfg->Value(FRAME_WIDTH, m_width).toUInt();
        m_height = cfg->Value(FRAME_HEIGHT, m_height).toUInt();

        cfg->SetValue(VIDEO_DEVICE, m_dev);
        cfg->SetValue(FRAME_FORMAT, m_format);
        cfg->SetValue(FRAME_WIDTH, m_width);
        cfg->SetValue(FRAME_HEIGHT, m_height);

        cfg->EndGroup();

        cfg->Sync();
    }
    m_capture = QImage(m_width,m_height,QImage::Format_ARGB32);
    return;
}
