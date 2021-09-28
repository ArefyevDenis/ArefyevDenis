
#pragma once

#include <QString>

#include "../../main/export_interface_iface.h"
#include "../../../common/config-win32.h"

//-------------------------------------------------------------------
#define LOG_MESSAGES_GRABBER_IFACE_ID       "log_messages_grabber_iface"
#define LOG_MESSAGES_GRABBER_IFACE_VERSION	1
//-------------------------------------------------------------------
/**
 * @brief Интерфейс получения и отработки сообщений из протокола приложения
  **/
class ILogMessagesGrabber
{
public:
    /**
     * @brief Обработать сообщение протокола работы приложения 
     * @param InMessage - текст сообщения
     **/
    virtual void 		ProcessLogMessage( const QString& InMessage ) const = 0;
  
};
//-------------------------------------------------------------------
/**
 * @brief Интерфейс пулла объектов дополнительной обработки сообщений о работе приложения
  **/
class ILogMessagesGrabbersPool: public FTS::Ifaces::IExportIface
{
public:
    /**
     * @brief Зарегистрировать обработчик сообщений протокола работы приложения 
     * @param ILogMessagesGrabber - объект обработки сообщений о работе приложения
     **/
    virtual bool 		RegisterLogMessagesGrabberIface( const ILogMessagesGrabber* InIface ) = 0;
	
};
//-------------------------------------------------------------------
