
#pragma once 

#include "../../../ifaces/main/export_interface_iface.h"
#include "../../../common/config-win32.h"


#define LOG_IFACE_ID 		"log_iface"
#define LOG_IFACE_VERSION	1

namespace FTS{
        namespace Ifaces{
		class ILogger;
	};
};

/**
 * @brief Системный интерфейс логирования сообщений приложения
 **/
class ILog: public FTS::Ifaces::IExportIface
{
public:

    /**
     * @brief Получить объект протоколирования для указанной подсистемы
     *
     * @param InLoggerName наименование подсситемы
     * @return :Logger*
     **/
    virtual const FTS::Ifaces::ILogger* CALL_CONVERSION GetLogger( const char* InSystemName ) = 0;
	
};
