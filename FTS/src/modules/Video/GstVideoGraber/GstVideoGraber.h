#ifndef _GST_VIDEO_GRABER_H_
#define _GST_VIDEO_GRABER_H_

#include "../../../../include/ifaces/main/module_iface.h"
#include "../../../../include/ifaces/modules/Video/video_receiver_iface.h"
#include <QtCore/QtGlobal>
#include <QObject>
#include <QImage>
#include <QMutex>
#include <QTimer>

#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <gst/gstbuffer.h>
#include <gst/gstcaps.h>

class GstVideoGraber: public QObject,
               public IVideoReceiver
{
    Q_OBJECT

public:


    GstVideoGraber(FTS::Ifaces::ICoreMainIfaces *pCoreMainIface);
    virtual ~GstVideoGraber();

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

    //============================================ из IVdideoReceiver =====================================================//

    /**
     * @brief ChanhgeSource - изменить устройство
     * @param source
     * @return
     */
    virtual bool CALL_CONVERSION ChanhgeSource (QString source);

    /**
     * @brief GetCapture - Получить изображение
     * @return
     */
    virtual QImage CALL_CONVERSION GetCapture();

    /**
     * @brief StartVideo - запускает процесс захвата видео
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
    GstElement *m_pSource;       //элемент чтения буфера

    QString m_dev;          //Устройство получения кадров
    unsigned int m_width;   //ширина запрашиваемого изображения
    unsigned int m_height;  //высота запрашиваемого изображения
    QString m_format;       //формат запрашиваемого изображения

    QImage m_capture;       //полученный кадр
    QMutex *m_mutex;        //объект сихронизации доступа


};



#endif // _GST_VIDEO_GRABER_H_
