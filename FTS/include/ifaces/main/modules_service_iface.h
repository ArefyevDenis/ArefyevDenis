#pragma once 

#include <exception>
#include <string>
#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{
		
class IExportIface;

//==============================================================================================================//
/**
 * @brief Сервисный класс взаимодействия с модулями
 **/
class IModulesService
{
public:

    /**
     * @brief Получить экспортируемый интерфейс
     *
     * @param InModuleId идентификатор модуля, который предположительно экспортирует интерфейс
     * @param InIfaceId идентфикатор интерфейса
     * @param InIfaceVersion версия интерфейса
     * @return :Interfaces::IExportInterface*
     **/
    virtual IExportIface* CALL_CONVERSION GetExportIface( const char* InModuleId, const char* InIfaceId, const unsigned int InIfaceVersion ) const throw() = 0;
	
    /**
     * @brief Получить количество модулей, установленных в Системе
     *
     * @param  ...
     * @return unsigned int количество модулей (от 0 до N)
     **/
    virtual unsigned int CALL_CONVERSION GetModulesCount( void ) const = 0;
	
    /**
     * @brief Получить идентификатор модуля по индексу
     *
     * @param InIndex индекс (от 0 до N)
     * @return const char* - результат (0 - при отсутствии)
     **/
    virtual const std::string CALL_CONVERSION GetModuleIdByIndex( unsigned int InIndex ) const = 0;
};
//==============================================================================================================//
        }
};
