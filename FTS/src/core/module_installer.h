
#pragma once

#include <list>
#include <QStringList>

#include "../../include/ifaces/main/installer_module_iface.h"
#include "../../include/ifaces/main/export_interface_iface.h"
#include "../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../include/ifaces/main/thread_service_iface.h"
#include "../../include/ifaces/main/internal_system_control_service_iface.h"
#include "../../include/ifaces/main/widgets_manipulator_iface.h"
#include "../../include/ifaces/main/action_service_iface.h"
#include "../core/interface_struct.h"

namespace FTS{
        namespace Ifaces{
		class ISettings;
		class IModuleGetterInfo;
		class IBuilderGuiHandler;
	}
	namespace Factory{
		class ModuleFactory;
	}
};
class LoggersPool;
class ConfigsPool;
class ModulesGrabber;
class ICSControllerHandler;
class ActionsPool;

//--------------------------------------------------------------------------
typedef std::list< IfaceStructDescriber > IfacesCont;
typedef IfacesCont::iterator IfacesContIter;
typedef IfacesCont::const_iterator IfacesContCIter;
//--------------------------------------------------------------------------
class ModuleInstaller: public FTS::Ifaces::IInstallerModule,
                       public FTS::Ifaces::ICoreMainIfaces,
                       public FTS::Ifaces::IThreadService,
                       public FTS::Ifaces::IWidgetsManipulator,
                       public FTS::Ifaces::IActionsService,
                       public FTS::Ifaces::IInternalSystemControlService
{
public:
    ModuleInstaller( QString InModuleName, 
					 LoggersPool* InLoggersPool, 
					 ConfigsPool* InConfigsPool, 
					 const ModulesGrabber* InModulesGrabber,
                                         const FTS::Ifaces::IAppService* InApplicationServiceIface,
					 ICSControllerHandler* InICSControllerHandler,
					 ActionsPool* InActionsPool,
                                         FTS::Ifaces::IBuilderGuiHandler* InBuilderGuiInterfaceHandler,
					 bool IsLogModule = false 
				   );
    virtual ~ModuleInstaller( void );

//--- FTS::Ifaces::IInstallerModule
public:

    /**
     * @brief Установить модуль в системе
     * @param InModule интерфейс модуля
     * @return void
     * \remarks
     * Интерфейс реализуется ядром и предоставляется для модуля при необходимотси инсталляции
     * \warning
     * Ядро проверяет версию модуля при установке!
     * Условия успешной установки:
     * 1) В модуле реализован интерфейс получения информации о модуле
     * 2) В реализованном интерфейсе методы получения иноформации о версии модуля выдают совместно ненулевые результаты
     * 3) Совпадает мажорная версия модуля и ядра
     * 4) Младшая часть версии модуля является информационной составляющей и не участвует в процессе установки
     * 5) Номер билда является информационной составляющей и не участвует в процессе установки
     * Например:
     * Ядро имеет версию 0.4
     * Модуль имеет версию:
     * 		- 0.4 - успех;
     * 		- 0.3 - успех;
     * 		- 1.0 - неудача;
     * 		- 0.5 - успех
     **/
    void CALL_CONVERSION InstallModule( FTS::Ifaces::IModule* InModule );
	
//--- ICoreMainIfaces
public:

    /**
     * @brief Получить интерфейс для конфигурирования
     *
     * @param  ...
     * @return const ISettings*
     **/
    FTS::Ifaces::ISettings* CALL_CONVERSION GetSettingsIface( void );
	
    /**
     * @brief Получить интерфейс для протоколирования
     *
     * @param  ...
     * @return const IProtocol*
     **/
    const FTS::Ifaces::ILogger* CALL_CONVERSION	GetProtocolIface( void );

    /**
     * @brief Получить интерфейс для получения аргументов модуля
     *
     * @param  ...
     * @return const IArgumentsGetter*
     **/
    FTS::Ifaces::ISettings* CALL_CONVERSION GetArgumentsGetterIface( void );
	
    /**
     * @brief Получить интерфейс для управления виджетами
     *
     * @param  ...
     * @return IWidgetsManipulator*
     **/
    FTS::Ifaces::IWidgetsManipulator* CALL_CONVERSION GetWidgetsManipulatorIface( void );

    /**
     * @brief Получить интерфейс для доступа к сервисным функциям с модулями
     *
     * @param  ...
     * @return const IModulesService*
     **/
    const FTS::Ifaces::IModulesService* CALL_CONVERSION	GetModulesServiceIface( void );
	
    /**
     * @brief Получить интерфейс для доступа к сервисным функциями с действиями
     *
     * @param  ...
     * @return const IActionsService*
     **/
    const FTS::Ifaces::IActionsService* CALL_CONVERSION	GetActionsServiceIface( void );
	
    /**
     * @brief Получить интерфейс для доступа к сервисным функциями с потоками
     *
     * @param  ...
     * @return :Interfaces::IThreadService*
     **/
    const FTS::Ifaces::IThreadService* CALL_CONVERSION GetThreadService( void );
	
    /** @brief Получить интерфейс сервиса Встроенной Системы Контроля (ВСК)
     *
     * @param  ...
     * @return :Interfaces::IInternalSystemControlService*
     **/
    FTS::Ifaces::IInternalSystemControlService* CALL_CONVERSION	GetInternalSystemControlService( void );
	
    /**
     * @brief Получить интерфейс доступа к информации о приложении
     *
     * @param  ...
     * @return :Interfaces::IAppService*
     **/
    const FTS::Ifaces::IAppService* CALL_CONVERSION GetApplicationService( void );
	
//--- IThreadService
public:

    /**
     * @brief Получить потоковый объект
     *
     * @param InExecuteObject объект, в котором объявлен потоковый метод для исполнения
     * @return ICrossThread*
     **/
    FTS::Ifaces::ICrossThread* CALL_CONVERSION GetThread( FTS::Ifaces::IThreadExecute* InExecuteObject ) const;
	
    /**
     * @brief Удалить поток
     *
     * @param InThread потокоый объект
     * @return void
     **/
    void CALL_CONVERSION DeleteThread( FTS::Ifaces::ICrossThread* InThread ) const;
	
//---  IInternalSystemControlService
public:

    /**
     * @brief Зарегистрировать узел ВСК в Системе
     *
     * @param InControlParameters интерфейс передачи параметров ВСК и их значений
     * @param InKeyISCNode ключ узла данных ВСК
     * @return bool - успешность регистрации параметра ВСК
     * \remarks Цепочка узлов 2го типа, к которой должен "клеиться" данный
     * узел с контролируемыми параметрами, выставляется каждым модулем
     * в описательном классе модуля (см. метод FillExportingISCParametersDescriber)
     * При несоотевтствии и в прочих ситуациях (несоотевтствие с конфигурационным файлов)
     * результат ошибочный
     **/
    bool CALL_CONVERSION RegisterInternalSystemControlNode(
                        const FTS::Ifaces::InternalSystemControl::IControlParameters* InControlParameters,
                        const char* InKeyISCNode
            );
public:

    /**
     * @brief Зарегистрировать объект для выдачи виджетов по запросу
     *
     * @param InWidgetsGetter объект для получения информации о виджетах в Системе
     * @return void
     **/
    void CALL_CONVERSION RegisterWidgetsGetter( FTS::Ifaces::IWidgetsGetter* InWidgetsGetter );
		
//--- IActionsService
public:

    /**
     * @brief Добавить действие
     *
     * @param InActionId идентификатор действия
     * @param InAction действие
     * @return bool - результат добавления
     **/
    bool CALL_CONVERSION AddAction( const char* InActionId, const QAction* InAction );
	
    /**
     * @brief Проверить наличие Действия для указанных условий
     *
     * @param InModuleId идентификатор модуля
     * @param InActionId идентификатор Действия
     * @return bool - признак наличия
     **/
    bool CALL_CONVERSION ActionInPresence( const char* InModuleId, const char* InActionId ) const;
	
    /**
     * @brief Получить количество действий, предоставляемых модулем
     *
     * @param InModuleId идентификатор модуля
     * @return unsigned int - количество (от 0 до N)
     **/
    unsigned int CALL_CONVERSION GetCountActions( const char* InModuleId ) const;
	
    /**
     * @brief Получить Действие по индексу
     *
     * @param InModuleId идентификатор модуля, реализующий Действие
     * @param InIndex индекс действия
     * @return QAction* - результат (0 при отсутствии Действия)
     **/
    const QAction* CALL_CONVERSION GetActionByIndex( const char* InModuleId, unsigned int InIndex ) const;
	
    /**
     * @brief Получить Действие по его идентификатору
     *
     * @param InModuleId идентификатор модуля
     * @param InActionId идентификатор Действия
     * @return QAction* - результат (0 при отсутствии Действия)
    **/
    const QAction* CALL_CONVERSION GetActionById( const char* InModuleId, const char* InActionId ) const;

	
public:

    /**
     * @brief Загрузить модуль в систему
     *
     * @param  ...
     * @return bool
     **/
    bool LoadModule( void );
	
    /**
     * @brief Выгрузить модуль из системы
     *
     * @param  ...
     * @return bool
     **/
    bool UnLoadModule( void );
	
    /**
     * @brief Инсталлировать модуль
     *
     * @param  ...
     * @return bool
     **/
    bool InstallModule( void );
	
    /**
     * @brief Деинсталлировать модуль
     *
     * @param  ...
     * @return bool
     **/
    bool UnInstallModule( void );
	
    /**
     * @brief Получить признак того, загружен ли модуль
     *
     * @param  ...
     * @return bool
     **/
    bool ModuleIsLoaded( void ) const;
	
    /**
     * @brief Запустить процесс работы модуля
     *
     * @param  ...
     * @return bool
     **/
    bool StartWorkModule( void );
	
    /**
     * @brief Запустить процесс работы модуля
     *
     * @param  ...
     * @return bool
     **/
    bool StopWorkModule( void );
	
    /**
     * @brief Получить признак, что входной аргумент "Идентфиикатор модуля" принадлежит данному инстансу
     *
     * @param InModuleId идентификатор модуля для проверки
     * @return bool
     **/
    bool IsMyModuleId( const char* InModuleId ) const;
	
    /**
     * @brief Заполнить объект с описанием интерфейса указателдем на сам интерфейс
     *
     * @param InOutIfaceDescriber входной/выходной параметр с описанием интерфейса
     * @return bool true - есть описатель с указанными параметрами интерфейса
     **/
    bool FillInterfaseDescriber( IfaceStructDescriber* InOutIfaceDescriber ) const;
	
public:
	
    /**
     * @brief Получить идентфикатор модуля
     *\remarks Идентфиикатор модуля получается путем вырезания из имени модуля расширения и знака "."
     * @param  ...
     * @return QString
     **/
    QString GetModuleId( void ) const;
	
    /**
     * @brief Получить имя модуля
     *\remarks Имя получается из экспортируемого из модуля интерфейса описания
     * @param  ...
     * @return QString
     **/
    QString GetModuleName( void ) const;
	
private:

    /**
     * @brief Перечень аргументов модуля
     **/
    QStringList	_Arguments;
	
    /**
     * @brief Объект конфигурации модуля
     **/
    FTS::Ifaces::ISettings* _ModuleConfigurator;
	
    /**
     * @brief Интерфейс для получения информации о модуле
     **/
    FTS::Ifaces::IModuleGetterInfo*	_ModuleInfo;
	
    /**
     * @brief Исполняемый интерфейс модуля
     **/
    FTS::Ifaces::IModule* _Module;
	
    /**
     * @brief Словарь с эксопртируемыми интерфейсами из модуля
     **/
    IfacesCont _Interfaces;
	
private:	

    /**
     * @brief Имя модуля
     **/
    QString _ModuleName;

    /**
     * @brief Пулл объектов протоколирования
     **/
    LoggersPool* _LoggersPool;
	
    /**
     * @brief Пулл объектов конфигурирования модулей
     **/
    ConfigsPool* _ConfigsPool;
	
    /**
     * @brief Объект с описанием всех инсталлированных модулей в системе
     **/
    const ModulesGrabber* _ModulesGrabber;

    /**
     * @brief Интерфейс доступа к сервисной информации о приложении
     **/
    const FTS::Ifaces::IAppService* _ApplicationServiceIface;
	
    /**
     * @brief Надстройка над Контроллером ВСК
     **/
    ICSControllerHandler* _ICSControllerHandler;
	
    /**
     * @brief Пулл с Действиями
     **/
    ActionsPool* _ActionsPool;

    /**
     * @brief Надстройка над модулем-построителем графического интерфейса Системы
     **/
    FTS::Ifaces::IBuilderGuiHandler* _BuilderGuiInterfaceHandler;
	
    /**
     * @brief Признак того, что загружается объект протколирования
     **/
    bool _IsLogModule;

private:

    /**
     * @brief Фабрика для загрузки параметров модулей
     **/
    FTS::Factory::ModuleFactory* _Factory;
	
};
//--------------------------------------------------------------------------
