
#pragma once

#include "../../include/ifaces/main/module_getter_info_iface.h"

/**
 * @brief Экземпляр класс информации о модуле
 **/
class ModuleInfo: public FTS::Ifaces::IModuleGetterInfo
{
public:
	ModuleInfo( void );
	virtual ~ModuleInfo( void );

public:
	/**
	 * @brief Получить старшую часть версии модуля
	 *
	 * @param  ...
	 * @return unsigned int
	 **/
    unsigned int CALL_CONVERSION GetMajorPartVersion( void );
	
	/**
	 * @brief Получить младшую часть версии модуля
	 *
	 * @param  ...
	 * @return unsigned int
	 **/
     unsigned int CALL_CONVERSION GetMinorPartVersion( void );
	
	/**
	 * @brief Получить информацию о номере сборки модуля
	 *
	 * @param  ...
	 * @return unsigned int
	 **/
     unsigned int CALL_CONVERSION GetBuildNumber( void );
	
	/**
	 * @brief Заполнить информацию о версии модуля
	 *
	 * @param OutVersionInfo структура для заполнения с описанием версии модуля
	 * @return void
     **/
     void CALL_CONVERSION FillVersionInfo( FTS::BasesTypes::ShortString* OutVersionInfo );
	 
	 /**
	 * @brief Заполнить описательную информацию о читаемом наименовании модуля
	 *
	 * @param OutReadedModuleName структура для заполнения с описанием наименования модуля
	 * @return void
	 **/
     void CALL_CONVERSION FillModuleReadedName( FTS::BasesTypes::ShortString* OutReadedModuleName );
	
	/**
	 * @brief Заполнить описательную информацию о модуле
	 *
	 * @param OutModuleInfo структура для заполнения с описанием информации о модуле
	 * @return void
	 **/
     void CALL_CONVERSION FillModuleInfo( FTS::BasesTypes::FullString* OutModuleInfo );
	 
	/**
	 * @brief Получить битовую маску с описанием типа модуля
	 *
	 * @param  ...
	 * @return unsigned int
	 **/
     unsigned int CALL_CONVERSION GetModuleType( void );
	
	/**
	 * @brief Заполнить описатель с информацией об используемых внешних библиотеках
	 *
	 * @param OutDescriber описатель, который необходимо заполнить
	 * @return void
	 **/
     void CALL_CONVERSION FillUsageExtendedLibraryDescriber( FTS::Ifaces::IUsageLibraryInfoDescriber* OutDescriber );
	 
	 /**
      * @brief Заполнить описатель с информацией об экспортируемых интерфейсах из библиотеки
      *
      * @param OutDescriber описатель, который необходимо заполнить
      * @return void
      **/
     void CALL_CONVERSION FillExportingInterfacesDescriber( FTS::Ifaces::IExportInterfaceInfoDescriber* OutDescriber );

	/**
	 * @brief Заполнить описатель с информацией об экспортируемых виджетах из библиотеки
	 *
	 * @param OutDescriber описатель, который необходимо заполнить
	 * @return void
     **/
     void CALL_CONVERSION FillExportingWidgetsDescriber( FTS::Ifaces::IWidgetInfoDescriber* OutDescriber );
	
	/**
	 * @brief Заполнить описатель с информацией об экспортируемых действиях из библиотеки
	 *
	 * @param OutDescriber описатель, который необходимо заполнить
	 * @return void
     **/
     void CALL_CONVERSION FillExportingActionsDescriber( FTS::Ifaces::IShortStringInfoDescriber* OutDescriber );
	 
	/**
	 * @brief Заполнить информацию об экспортиуремых из модуля параметрах ВСК
	 *
	 * @param OutDescriber описатель, который необходимо заполнить
	 * @return void
     **/
     void CALL_CONVERSION FillExportingISCParametersDescriber( FTS::Ifaces::IExportedISCParameters* OutDescriber ){};
	
	 /**
	 * @brief Удалить экземпляр класса
	 *
	 * @param  ...
	 * @return void
     **/
     void CALL_CONVERSION Release( void );
	 
private:
	
	
};
