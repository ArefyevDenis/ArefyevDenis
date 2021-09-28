#pragma once

#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{
		
class ICoreMainIfaces;
class IExportIface;

//==================================================================================================================//
/**
 * @brief Интерфейс модуля системы
 **/
class IModule
{
public:

    /**
     * @brief Инициализация модуля
     *
     * @param ICoreMainIfaces ядро главных интерфейсов
     * @return void
     **/
    virtual void CALL_CONVERSION Initialize( FTS::Ifaces::ICoreMainIfaces* InCoreMainIfaces ) = 0;
	
    /**
     * @brief Запуск работы модуля
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Start( void ) = 0;
	
    /**
     * @brief Стоп работы модуля
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Stop( void ) = 0;
	
    /**
     * @brief Получить интерфейс в соответствии с указанными параметрами
     *
     * @param InIfaceId идентификатор запрашиваемого интерфейса
     * @param InIfaceVersion версия запрашиваемого интерфейса
     * @return :Interfaces::IExportInterface*
     **/
    virtual FTS::Ifaces::IExportIface* CALL_CONVERSION GetExportedIface( const char* InIfaceId, const unsigned int InIfaceVersion ) = 0;
	
    /**
     * @brief Удаление объекта
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Release( void ) = 0;
};

//==================================================================================================================//
        };
};
