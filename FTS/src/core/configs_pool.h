
#pragma once

#include <QtCore/QMap>
#include <QtCore/QString>

class Settings;

//==============================================================================================================//
/**
 * @brief Объявление типов данных для списка конфигураторов
 **/
typedef QMap< QString, Settings* > SettingsCont;
typedef SettingsCont::iterator SettingsContIter;
//==============================================================================================================//

/**
 * @brief Класс пулла объектов конфигурации
 **/
class ConfigsPool
{
public:
    ConfigsPool( const char* InProgramName );
    ~ConfigsPool( void );
	
public:
	/**
	 * @brief Получить объект конфигурации для всех модулей приложения
         * @param  ...
	 * @return Settings*
	 **/
        Settings* GetModulesSettingsObj( void );

	/**
	 * @brief Получить объект конфигурации для основных настроек приложения
         * @param  ...
	 * @return Settings*
         **///---------------------------------------------------------------
        Settings* GetApplicationSettingsObj( void );
	
	/**
	 * @brief Получить объект конфигурирования параметров для конкретного модуля
         * @param InModuleId идентфикатор модуля
	 * \remarks 
	 * В случае, если объект конфигурации отсутствует, то он создается принудительно
	 * @return Settings*
	 **/
        Settings* GetSettingsObjForModule( const char* InModuleId );
		
	/**
	 * @brief Получить объект для получения строки аргументов конкретного модуля
         * @param InModuleId идентфикатор модуля
	 * \remarks 
	 * В случае, если объект конфигурации отсутствует, то он создается принудительно
	 * @return Settings*
	 **/
        Settings* GetArgumentsObjForModule( const char* InModuleId );

private:

        QString	m_FullPathToConfigs;            //полный путь к файлам конфигурации
        QString	m_FullPathToArguments;          //Полный путь к файлам аргументов модулей
        Settings* m_ApplicationConfigurator;    //Объект для конфигурации основных параметров приложения
        Settings* m_ModulesConfigurator;        //Объект для конфигурирования параметров модулей
        SettingsCont m_AllSettings;             //Контейнер со всеми объектами конфигурации
        SettingsCont m_AllArguments;            //Контейнер со всеми объектами конфигурации
	
};
//==============================================================================================================//
