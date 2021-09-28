#include "GstVideoSender.h"
#include "../../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../../include/ifaces/main/logger_iface.h"
#include "../../../../include/ifaces/main/modules_service_iface.h"
#include "../../../../include/ifaces/main/settings_iface.h"
#include "../../../../include/ifaces/main/widgets_manipulator_iface.h"

#include <assert.h>
#include <QString>
#include <QImage>
#include <QMutexLocker>
#include <QBuffer>
#include <gst/gstsample.h>


//==================================================================================================================//
const QString   PARAM_SENDING_SECTION =     "PARAM_VIDEO_SECTION";
const QString   HOST_SENDING =              "HOST_SENDING";
const QString   PORT_SENDING =              "PORT_SENDING";
const QString   FPS_SENDING =               "FPS_SENDING";


const QString   PARAM_IMAGE_SECTION =       "PARAM_IMAGE_SECTION";
const QString   IMAGE_WIDTH =               "IMAGE_WIDTH";
const QString   IMAGE_HEIGHT =              "IMAGE_HEIGHT";

//================================================== PBULIC ========================================================//
//==================================================================================================================//
GstVideoSender::GstVideoSender(FTS::Ifaces::ICoreMainIfaces *pCoreMainIface):
    m_pCoreMainIface(pCoreMainIface) {
    assert(m_pCoreMainIface);
    m_pPipeline = 0;
    m_pSource = 0;

    m_mutex = new QMutex(QMutex::Recursive);

    m_host = QString("127.0.0.1");
    m_port = 9001;
    m_fps = 25;
    m_widht = 1024;
    m_height = 768;

    // инициализируем gstreamer
    gst_init(0,0);

}

GstVideoSender:: ~GstVideoSender() {

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
const char *CALL_CONVERSION GstVideoSender::GetId(){
    return VIDEO_SENDER_IFACE_ID;
}

unsigned int CALL_CONVERSION GstVideoSender::GetVersion() {
    return VIDEO_SENDER_IFACE_VERSION;
}


//============================================ из IVdideoSender =====================================================//
//==========================================================================m_pSource========================================//
bool CALL_CONVERSION GstVideoSender::ChanhgeIpAddr (QString host, unsigned int port){
    m_host = host;
    m_port = port;
    return true;
}

//==================================================================================================================//
void CALL_CONVERSION GstVideoSender::SendCapture(const QImage *image ){
    QMutexLocker locker(m_mutex);
    if (image == NULL)
        return;

    if (image->isNull())
        return;

    if (m_pSource == 0)
        return;

    if (m_pPipeline == 0)
        return;


    m_capture = image->convertToFormat(QImage::Format_ARGB32);

    GstBuffer *buffer = gst_buffer_new_allocate(0,m_capture.byteCount(),0);
    if ( !buffer ){
        return;
    }
    GstMapInfo info;
    if (gst_buffer_map(buffer, &info, GstMapFlags(GST_MAP_WRITE)) == false){
        gst_buffer_unref(buffer);
        return;
    }

    memcpy(info.data, (guint8*)m_capture.bits(), m_capture.byteCount());
    gst_buffer_unmap(buffer,&info);
    GstCaps* caps = gst_caps_new_simple ("video/x-raw",
                                         "format", G_TYPE_STRING, "BGRA",
                                         "width", G_TYPE_INT, m_capture.width(),
                                         "height", G_TYPE_INT, m_capture.height(),
                                         "framerate", GST_TYPE_FRACTION, m_fps, 1,
                                         NULL);


    /*
    QByteArray im = QByteArray();
    QBuffer img_buf(&im);
    img_buf.open(QIODevice::WriteOnly);
    image->save(&img_buf, "JPEG");
    img_buf.close();

    GstBuffer *buffer = gst_buffer_new_allocate(0,im.size(),0);
    if ( !buffer ){
        return;
    }

    GstMapInfo info;
    if (gst_buffer_map(buffer, &info, GstMapFlags(GST_MAP_WRITE)) == false){
        gst_buffer_unref(buffer);
        return;
    }

    memcpy(info.data, (guint8*)im.data(), im.size());
    gst_buffer_unmap(buffer,&info);

    GstCaps* caps = gst_caps_new_simple ("image/jpeg",
                                         "width", G_TYPE_INT, image->width(),
                                         "height", G_TYPE_INT, image->height(),
                                         "framerate", GST_TYPE_FRACTION, m_fps, 1,
                                         NULL);

    */

    if (!caps){
        gst_buffer_unref(buffer);
        return;
    }
    GstSample *sample = gst_sample_new(buffer, caps, NULL, NULL);
    if (!sample){
        gst_buffer_unref(buffer);
        gst_caps_unref(caps);
        return;
    }
    gst_app_src_push_sample(GST_APP_SRC(m_pSource),sample);
    gst_sample_unref(sample);
    gst_buffer_unref(buffer);
    gst_caps_unref(caps);

    return;
}

//==================================================================================================================//
bool CALL_CONVERSION GstVideoSender::StartVideo(){
    QMutexLocker locker(m_mutex);

    // проверим, если уже создавали, то выйдем
    if (m_pPipeline){
        m_pCoreMainIface->GetProtocolIface()->error("Видеоконвеер был создан ранее");
        return false;
    }

    //создадим строку вещяния
    QString gst_str = QString(" appsrc name=mysrc ! videoscale ! video/x-raw, width=%1, height=%2 ! videoconvert ! x264enc speed-preset=ultrafast tune=zerolatency byte-stream=true threads=1 key-int-max=15 intra-refresh=true ! video/x-h264, profile=high ! rtph264pay ! udpsink async=false host=%3 port=%4")
                               .arg(m_widht).arg(m_height).arg(m_host).arg(m_port);

//    QString gst_str = QString(" appsrc name=mysrc ! jpegdec ! videoscale ! video/x-raw, width=%1, height=%2 ! x264enc speed-preset=ultrafast tune=zerolatency byte-stream=true threads=1 key-int-max=15 intra-refresh=true ! video/x-h264, profile=high ! rtph264pay ! udpsink async=false host=%3 port=%4")
//            .arg(m_widht).arg(m_height).arg(m_host).arg(m_port);


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
    m_pSource = gst_bin_get_by_name(GST_BIN(m_pPipeline),"mysrc");
    if (!m_pSource){
        m_pCoreMainIface->GetProtocolIface()->error("Ошибка получения элемента [appsrc]");
        return false;
    }

    gst_app_src_set_stream_type(GST_APP_SRC(m_pSource), GST_APP_STREAM_TYPE_STREAM);
    gst_app_src_set_size (GST_APP_SRC(m_pSource), -1);

    g_object_set(G_OBJECT(m_pSource), "format", GST_FORMAT_BUFFERS, NULL);
    g_object_set(G_OBJECT(m_pSource), "block", 1, NULL);
    g_object_set(G_OBJECT(m_pSource), "is-live", 0, NULL);

    //попробуем запустить конвеер
    GstStateChangeReturn ret = gst_element_set_state(m_pPipeline, GST_STATE_PLAYING);
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
void CALL_CONVERSION GstVideoSender::StopVideo(){
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

    gst_deinit();

    m_pCoreMainIface->GetProtocolIface()->debug("Конвеер успешно остановлен");
}

//==================================================================================================================//
void GstVideoSender::init(){
    FTS::Ifaces::ISettings* cfg = m_pCoreMainIface->GetSettingsIface();
    if (cfg){
        cfg->BeginGroup(PARAM_SENDING_SECTION);

        m_host = cfg->Value(HOST_SENDING, m_host).toString();
        m_port = cfg->Value(PORT_SENDING, m_port).toUInt();
        m_fps = cfg->Value(FPS_SENDING, m_fps).toUInt();

        cfg->SetValue(HOST_SENDING, m_host);
        cfg->SetValue(PORT_SENDING, m_port);
        cfg->SetValue(FPS_SENDING, m_fps);

        cfg->EndGroup();

        cfg->BeginGroup(PARAM_IMAGE_SECTION);

        m_widht = cfg->Value(IMAGE_WIDTH, m_widht).toUInt();
        m_height = cfg->Value(IMAGE_HEIGHT, m_height).toUInt();

        cfg->SetValue(IMAGE_WIDTH, m_widht);
        cfg->SetValue(IMAGE_HEIGHT, m_height);

        cfg->EndGroup();

        cfg->Sync();

        m_capture = QImage(m_widht,m_height, QImage::Format_ARGB32);
    }
}

