#ifndef _GST_VIDEO_SENDER_H_
#define _GST_VIDEO_SENDER_H_

#include "../../../../include/ifaces/main/module_iface.h"
#include "../../../../include/ifaces/modules/Video/video_sender_iface.h"
#include <QtCore/QtGlobal>
#include <QObject>
#include <QImage>
#include <QMutex>
#include <QTimer>

#include <gst/gst.h>
#include <gst/app/gstappsrc.h>
#include <gst/gstbuffer.h>
#include <gst/gstcaps.h>

class GstVideoSender: public QObject,
               public IVideoSender
{
    Q_OBJECT

public:


    GstVideoSender(FTS::Ifaces::ICoreMainIfaces *pCoreMainIface);
    virtual ~GstVideoSender();

    //===================================== из FTS::Ifaces::IExportIface ===============================================//

    /**
    * @brief Получить версию интерфейса
    *
    * @param  ...
    * @return unsigned int
    **/
    virtual unsigned int CALL_CONVERSION GetVersion( void );

    /**
    * @brief Получить идентификатор интерфейса
    *
    * @param  ...
    * @return const char*
    **/
    virtual const char* CALL_CONVERSION GetId( void );

    //============================================ из IVdideoSender =====================================================//

    /**
     * @brief ChanhgeIpAddr - позволяет изменить адрес вещания
     * @param host - хост
     * @param port - порт
     * @return удачно или нет
     */
    virtual bool CALL_CONVERSION ChanhgeIpAddr (QString host, unsigned int port);

    /**
     * @brief SendCapture
     * @param image - кадр изображения
     */
    virtual void CALL_CONVERSION SendCapture(const QImage *image );

    /**
     * @brief StartVideo - запускает процесс отправки видео
     * @return удачно или нет
     */
    virtual bool CALL_CONVERSION StartVideo();

    /**
     * @brief StopVideo
     */
    virtual void CALL_CONVERSION StopVideo();

    /**
     * @brief init - инициализация параметров вещания
     */
    void init();

private:

    FTS::Ifaces::ICoreMainIfaces *m_pCoreMainIface;
    GstElement *m_pPipeline;     //конвеер потока
    GstElement *m_pSource;       //элемент запихивания буфера

    QString m_host;         //хост вещания
    unsigned int m_port;    //порт вещания
    unsigned int m_fps;     //кадров в секунду
    unsigned int m_widht;   //ширина изображения
    unsigned int m_height;  //высота изображения

    QImage m_capture;       //Кадр который постоянно буде слать
    QMutex *m_mutex;         //объект сихронизации доступа

};



#endif // _GST_VIDEO_SENDER_H_
