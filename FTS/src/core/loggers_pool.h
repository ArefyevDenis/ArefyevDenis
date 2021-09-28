
#pragma once

#include "../core/interface_struct.h"

#include "../../include/ifaces/modules/log/log_iface.h"
#include "../../include/ifaces/main/logger_iface.h"
#include "../../include/ifaces/main/export_interface_iface.h"

namespace FTS{
        namespace Ifaces{
		class IModulesService;
	}
}

//------------------------------------------------------------------
/**
 * @brief Пулл объектов протоколирования
 **/
class LoggersPool
{
public:

    LoggersPool( void );
    ~LoggersPool( void );

    /**
     * @brief Установить интерфейс доступа к сервисным функциям с модулями
     *
     * @param InModulesService ...
     * @return void
     **/
    void SetModuleServiceIface( FTS::Ifaces::IModulesService* InModulesService );
	
    /**
     * @brief Уведомление о том, что в систему загружен модуль протоколирования
     *
     * @param  ...
     * @return void
     **/
    void LogModuleIsLoaded( void );
	
    /**
     * @brief Получить объект протоколирования, выделенный для ядра
     *
     * @param  ...
     * @return const ILogger*
     **/
    const FTS::Ifaces::ILogger*	CoreLogger( void ) const;
	
    /**
     * @brief Получить объект протоколирования для модуля
     *
     * @param  ...
     * @return const ILogger*
     **/
    const FTS::Ifaces::ILogger*	LoggerForModule( QString InModuleName ) const;
	
	
private:
    /**
     * @brief Инициализировать подсистему протоколирования
     *
     * @param  ...
     * @return void
     **/
    void InitilizeLoggerSystem( void );
	
private:

    FTS::Ifaces::IModulesService* m_pModulesService;   //Сервис работы с модулями
    bool m_IsInitialized;                              //Признак того, что пулл с объектами протоколирования инициализирован
    const FTS::Ifaces::ILogger*	m_pSelfLoggerIface;    //Собственный интерфейс протоколирования
    ILog* m_pExportLogIface;                           //Интерфейс модуля протколирования
	
};
//------------------------------------------------------------------
