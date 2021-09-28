
#pragma once

#include <list>
#include <QMutex>

#include <QStringList>

#include "../../include/ifaces/main/modules_service_iface.h"

namespace FTS{
        namespace Ifaces{
		class ISettings;
		class IWidgetsManipulator;
                class IAppService;
		class IBuilderGuiHandler;
	};
};
class ConfigsPool;
class LoggersPool;
class ModuleInstaller;
class ICSControllerHandler;
class ActionsPool;

//==============================================================================================================//
typedef std::list< ModuleInstaller* > ModuleInstallerCont;
typedef ModuleInstallerCont::iterator ModuleInstallerContIter;
typedef ModuleInstallerCont::const_iterator ModuleInstallerContCIter;
//==============================================================================================================//

/**
 * @brief Класс, инкапсулирующий в себе всю информацию о всех модулях
 **/
class ModulesGrabber: public FTS::Ifaces::IModulesService
{
public:
    ModulesGrabber( ConfigsPool* InConfigsPool,
                    LoggersPool* InLoggersPool,
                    const FTS::Ifaces::IAppService* InAppServiceIface,
                    ActionsPool* InActionsPool
                   );
    ~ModulesGrabber();

	
//--- IModulesService
public:

    /**
     * @brief Получить экспортируемый интерфейс
     *
     * @param InModuleId идентификатор модуля, который предположительно экспортирует интерфейс
     * @param InIfaceId идентфикатор интерфейса
     * @param InIfaceVersion версия интерфейса
     * @return :Interfaces::IExportInterface*
     **/
    FTS::Ifaces::IExportIface* CALL_CONVERSION GetExportIface( const char* InModuleId, const char* InIfaceId, unsigned int InIfaceVersion ) const throw();
	
    /**
     * @brief Получить количество модулей, установленных в Системе
     *
     * @param  ...
     * @return unsigned int количество модулей (от 0 до N)
     **/
    unsigned int CALL_CONVERSION GetModulesCount( void ) const;
	
    /**
     * @brief Получить идентификатор модуля по индексу
     *
     * @param InIndex индекс (от 0 до N)
     * @return const char* - результат (0 - при отсутствии)
     **/
    const std::string CALL_CONVERSION GetModuleIdByIndex( unsigned int InIndex ) const;
	
public:

    /**
     * @brief Установить интерфейс манипулирования виджетами
     *
     * @param InWidgetsManipulatorIface интерфейс манипулировани виджетами
     * @return void
     **/
    void SetWidgetsManipulatorIface( FTS::Ifaces::IWidgetsManipulator* InWidgetsManipulatorIface );
	
    /**
     * @brief Получить интерфейс управления виджетами
     *
     * @param  ...
     * @return :Interfaces::IWidgetsManipulator*
     **/
    FTS::Ifaces::IWidgetsManipulator* GetWidgetsManipulatorIface( void ) const;
	
    /**
     * @brief Установить обертку над Контроллером ВСК
     *
     * @param InICSControllerHandler ...
     * @return void
     **/
    void SetICSControllerHandler( ICSControllerHandler* InICSControllerHandler );
	
    /**
     * @brief Установить надстройку над модулем-построителем графического интерфейса Системы
     *
     * @param InBuilderGuiInterfaceHandler ...
     * @return void
     **/
    void SetBuilderGuiInterfaceHandler( FTS::Ifaces::IBuilderGuiHandler* InBuilderGuiInterfaceHandler );
	
public:

    /**
     * @brief Загрузить моудли
     *
     * @param  ...
     * @return void
     **/
    void LoadModules( void );
	
    /**
     * @brief Запустить процесс работы всех модулей
     *
     * @param  ...
     * @return void
     **/
    void StartModules( void );
	
    /**
     * @brief Остановить процесс работы всех модулей
     *
     * @param  ...
     * @return void
     **/
    void StopModules( void );
	
    /**
     * @brief Выгрузить моудли
     *
     * @param  ...
     * @return void
     **/
    void UnLoadModules( void );
	
private:

    /**
     * @brief Построить список модулей для загрузки
     *
     * @param  ...
     * @return void
     **/
    void BuildModulesListForLoading( void );
	
    /**
     * @brief Записать в файл пример конфигурации
     *
     * @param  ...
     * @return void
     **/
    void WriteSampleInformation( void );
	
    /**
     * @brief Удалить из загруженного списка пример конфигурации
     *
     * @param  ...
     * @return void
     **/
    void DeleteSampleInformation( void );
	
    /**
     * @brief Загрузить модуль протоколирования
     *
     * @param  ...
     * @return void
     **/
    void LoadLogModule( void );
	
    /**
     * @brief Загрузить все модули кроме модуля протоколирования
     *
     * @param  ...
     * @return void
     **/
    void LoadAllModulesWithoutLog( void );
	
    /**
     * @brief Инсталлировать все модули
     *
     * @param  ...
     * @return void
     **/
    void InstallAllModules( void );
	
private:

    ConfigsPool* m_pConfigsPool;                            //Пулл с объектами конфигурации
    LoggersPool* m_pLoggersPool;                            //Пулл с объектами протоколирования
    const FTS::Ifaces::IAppService* m_pAppServiceIface;     //Сервис получения информации о приложении
    ICSControllerHandler* m_pICSControllerHandler;          //Объект доступа к интерфейсу Контроллера ВСК
    FTS::Ifaces::ISettings* m_pSettings;                    //Объект для взаимодействия
    QStringList	m_ModulesLibrariesNames;                    //Перечень наименований библиотек для загрузки
    ModuleInstallerCont	m_Installers;                       //Список объектов для инсталляции модулей
    mutable QMutex m_Mutex;                                 //Объект синхронизации доступа к экземпляру объекта
    FTS::Ifaces::IWidgetsManipulator* m_pWidgetsManipulator;//Интерфейс управления виджетами
    ActionsPool* m_pActionsPool;                            //Пулл с Действиями
    FTS::Ifaces::IBuilderGuiHandler* m_pBuilderGuiInterfaceHandler;//Надстройка над модулем-построителем графического интерфейса Системы
};
//----------------------------------------------------------------------------

