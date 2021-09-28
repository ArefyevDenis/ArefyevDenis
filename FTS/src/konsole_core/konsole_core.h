
#pragma once

#include <QCoreApplication>

#include "../core/configs_pool.h"
#include "../core/module_installer.h"
#include "../core/modules_grabber.h"
#include "../core/loggers_pool.h"
#include "../core/service_application_info.h"
#include "../core/ics_controller_handler.h"
#include "../core/actions_pool.h"

//==============================================================================================================//
/**
 * @brief Основной класс консольного ядра
 **/
class KonsoleCore: public QCoreApplication
{
	Q_OBJECT	

public:

    KonsoleCore( int argc, char** argv, const char* InProgramName );
    ~KonsoleCore( void );
	

    /**
     * @brief Инициализация
     *
     * @param  ...
     * @return void
     **/
    void Initialize( void );
	
    /**
     * @brief Запуск приложения
     *
     * @param  ...
     * @return void
     **/
    void Run( void );
	
private:
	
    /**
     * @brief Корректная отработка завершения программы
     *
     * @param  ...
     * @return void
     **/
    static void EndWork( int InSignalType );
	
private:

    ConfigsPool m_ConfigsPool;          //Пулл с объектами конфигурации
    ModulesGrabber m_ModulesGrabber;    //Объект, инкапсулирующий в себе информацию о всех подключенных модулях в системе
    LoggersPool	m_LoggersPool;          //Пулл с объектами протоколирования
    ServiceAppInfo m_ServiceAppInfo;    //Объект предоставления сервисной информацию о приложении
    ActionsPool m_ActionsPool;          //Пул с действиями
    ICSControllerHandler m_ICSControllerHandler;            //Надстройка над Контроллером ВСК

};
//==============================================================================================================//
