
#pragma once

#include "../../main/export_interface_iface.h"

#define VIDEO_RECEIVER_IFACE_ID 		"Video_receiver_iface"
#define VIDEO_RECEIVER_IFACE_VERSION            1

class QImage;
class QString;

class IVideoReceiver : public FTS::Ifaces::IExportIface {

public:

    /**
     * @brief ChanhgeSource - изменить устройство
     * @param source
     * @return
     */
    virtual bool CALL_CONVERSION ChanhgeSource (QString source) = 0;

    /**
     * @brief GetCapture - Получить изображение
     * @return
     */
    virtual QImage CALL_CONVERSION GetCapture() = 0;

    /**
     * @brief StartVideo - запускает процесс захвата видео
     * @return удачно или нет
     */
    virtual bool CALL_CONVERSION StartVideo() = 0;

    /**
     * @brief StopVideo
     */
    virtual void CALL_CONVERSION StopVideo() = 0;


};





