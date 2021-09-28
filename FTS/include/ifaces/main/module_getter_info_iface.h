#pragma once

#include "../../common/typedefs.h"
#include "../../common/config-win32.h"

#include "usage_library_info_describer_iface.h"
#include "export_interfaces_describer_iface.h"
#include "short_string_describer_iface.h"
#include "widget_info_describer_iface.h"
#include "exported_internal_system_control_parameters_iface.h"

namespace FTS{
        namespace Ifaces{
/**
 * @brief Интерфейс для получения информации о модуле
 **/
class IModuleGetterInfo
{
public:

    /**
     * @brief Получить старшую часть версии модуля
     *
     * @param  ...
     * @return unsigned int
     **/
    virtual unsigned int CALL_CONVERSION GetMajorPartVersion( void ) = 0;
	
    /**
     * @brief Получить младшую часть версии модуля
     *
     * @param  ...
     * @return unsigned int
     **/
    virtual unsigned int CALL_CONVERSION GetMinorPartVersion( void ) = 0;
	
    /**
     * @brief Получить информацию о номере сборки модуля
     *
     * @param  ...
     * @return unsigned int
     **/
    virtual unsigned int CALL_CONVERSION GetBuildNumber( void ) = 0;
	
    /**
     * @brief Заполнить информацию о версии модуля
     *
     * @param OutVersionInfo структура для заполнения с описанием версии модуля
     * @return void
     **/
    virtual void CALL_CONVERSION FillVersionInfo( FTS::BasesTypes::ShortString* OutVersionInfo ) = 0;
	
    /**
     * @brief Заполнить описательную информацию о читаемом наименовании модуля
     *
     * @param OutReadedModuleName структура для заполнения с описанием наименования модуля
     * @return void
     **/
    virtual void CALL_CONVERSION FillModuleReadedName( FTS::BasesTypes::ShortString* OutReadedModuleName ) = 0;
	
    /**
     * @brief Заполнить описательную информацию о модуле
     *
     * @param OutModuleInfo структура для заполнения с описанием информации о модуле
     * @return void
     **/
    virtual void CALL_CONVERSION FillModuleInfo( FTS::BasesTypes::FullString* OutModuleInfo ) = 0;
	
    /**
     * @brief Получить битовую маску с описанием типа модуля
     *
     * @param  ...
     * @return unsigned int
     **/
    virtual unsigned int CALL_CONVERSION GetModuleType( void ) = 0;
	
    /**
     * @brief Заполнить описатель с информацией об используемых внешних библиотеках
     *
     * @param OutDescriber описатель, который необходимо заполнить
     * @return void
     **/
    virtual void CALL_CONVERSION FillUsageExtendedLibraryDescriber( FTS::Ifaces::IUsageLibraryInfoDescriber* OutDescriber ) = 0;
	
    /**
     * @brief Заполнить описатель с информацией об экспортируемых интерфейсах из библиотеки
     *
     * @param OutDescriber описатель, который необходимо заполнить
     * @return void
     **/
    virtual void CALL_CONVERSION FillExportingInterfacesDescriber( FTS::Ifaces::IExportInterfaceInfoDescriber* OutDescriber ) = 0;

    /**
     * @brief Заполнить описатель с информацией об экспортируемых виджетах из библиотеки
     *
     * @param OutDescriber описатель, который необходимо заполнить
     * @return void
     **/
    virtual void CALL_CONVERSION FillExportingWidgetsDescriber( FTS::Ifaces::IWidgetInfoDescriber* OutDescriber ) = 0;
	
    /**
     * @brief Заполнить описатель с информацией об экспортируемых действиях из библиотеки
     *
     * @param OutDescriber описатель, который необходимо заполнить
     * @return void
     **/
    virtual void CALL_CONVERSION FillExportingActionsDescriber( FTS::Ifaces::IShortStringInfoDescriber* OutDescriber ) = 0;
	
    /**
     * @brief Заполнить информацию об экспортиуремых из модуля параметрах ВСК
     *
     * @param OutDescriber описатель, который необходимо заполнить
     * @return void
     **/
    virtual void CALL_CONVERSION FillExportingISCParametersDescriber( FTS::Ifaces::IExportedISCParameters* OutDescriber ) = 0;
	
    /**
     * @brief Удалить экземпляр класса
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Release( void ) = 0;
	
};
        };	// end namespace Ifaces
};	// end FTS
