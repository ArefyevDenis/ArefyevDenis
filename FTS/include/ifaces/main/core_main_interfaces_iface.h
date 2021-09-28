#pragma once 

#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{
		
class ISettings;
class ILogger;
class IWidgetsManipulator;
class IModulesService;
class IActionsService;	
class IThreadService;
class IInternalSystemControlService;
class IAppService;

/**
 * @brief Интерфейс для получения основных программных интерфейсов ядра
 **/
class ICoreMainIfaces
{
public:
    /**
     * @brief Получить интерфейс для конфигурирования
     * @param  ...
     * @return const ISettings*
     **/
    virtual ISettings* CALL_CONVERSION GetSettingsIface( void ) = 0;
	
    /**
     * @brief Получить интерфейс для протоколирования
     * @param  ...
     * @return const IProtocol*
     **/
    virtual const ILogger* CALL_CONVERSION GetProtocolIface( void ) = 0;

    /**
     * @brief Получить интерфейс для получения аргументов модуля
     * @param  ...
     * @return const IArgumentsGetter*
     **/
    virtual ISettings* CALL_CONVERSION GetArgumentsGetterIface( void ) = 0;
	
    /**
     * @brief Получить интерфейс для управления виджетами
     * @param  ...
     * @return IWidgetsManipulator*
     **/
    virtual IWidgetsManipulator* CALL_CONVERSION GetWidgetsManipulatorIface( void ) = 0;

    /**
     * @brief Получить интерфейс для доступа к сервисным функциям с модулями
     * @return const IModulesService*
     **/
    virtual const IModulesService* CALL_CONVERSION GetModulesServiceIface( void ) = 0;
	
    /**
     * @brief Получить интерфейс для доступа к сервисным функциями с действиями
     * @return const IActionsService*
     **/
    virtual const IActionsService* CALL_CONVERSION GetActionsServiceIface( void ) = 0;
	
    /**
     * @brief Получить интерфейс для доступа к сервисным функциями с потоками
     * @return :Interfaces::IThreadService*
     **/
    virtual const IThreadService* CALL_CONVERSION GetThreadService( void ) = 0;

    /**
     * @brief Получить интерфейс сервиса Встроенной Системы Контроля (ВСК)
     * @return :Interfaces::IInternalSystemControlService*
     **/
    virtual IInternalSystemControlService* CALL_CONVERSION GetInternalSystemControlService( void ) = 0;
	
    /**
     * @brief Получить интерфейс доступа к информации о приложении
     * @return :Interfaces::IAppService*
     **/
    virtual const IAppService* CALL_CONVERSION GetApplicationService( void ) = 0;
	
};

	};
};
