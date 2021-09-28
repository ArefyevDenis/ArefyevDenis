
#pragma once

#include "../../main/export_interface_iface.h"

#define VIDEO_SENDER_IFACE_ID 		"Video_sender_iface"
#define VIDEO_SENDER_IFACE_VERSION	1

class QImage;
class QString;

class IVideoSender : public FTS::Ifaces::IExportIface {

public:

    /**
     * @brief ChanhgeIpAddr - позволяет изменить адрес вещания
     * @param host - хост
     * @param port - порт
     * @return удачно или нет
     */
    virtual bool CALL_CONVERSION ChanhgeIpAddr (QString host, unsigned int port) = 0;

    /**
     * @brief SendCapture
     * @param image - кадр изображения
     */
    virtual void CALL_CONVERSION SendCapture(const QImage *image ) = 0;

    /**
     * @brief StartVideo - запускает процесс отправки видео
     * @return удачно или нет
     */
    virtual bool CALL_CONVERSION StartVideo() = 0;

    /**
     * @brief StopVideo
     */
    virtual void CALL_CONVERSION StopVideo() = 0;


};





