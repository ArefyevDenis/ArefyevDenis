
#include <assert.h>
#include <iostream>
#include <stdexcept>

#include <QString>
#include <QStringList>

#include "../../include/common/config-win32.h"

#include "loggers_pool.h"
#include "../../include/ifaces/main/modules_service_iface.h"

//==============================================================================================================//
LoggersPool::LoggersPool( void ):
        m_pModulesService( 0 ),
        m_pSelfLoggerIface( 0 ),
        m_pExportLogIface( 0 ){
	
}

//==============================================================================================================//
LoggersPool::~LoggersPool( void ){
	
}

//==============================================================================================================//
void LoggersPool::SetModuleServiceIface( FTS::Ifaces::IModulesService* InModulesService ){
    m_pModulesService = InModulesService;
}

//==============================================================================================================//
void LoggersPool::LogModuleIsLoaded( void ){
	InitilizeLoggerSystem();
}

//==============================================================================================================//
const FTS::Ifaces::ILogger*	LoggersPool::CoreLogger( void ) const{
    assert( m_pSelfLoggerIface );
	
    return m_pSelfLoggerIface;
}

//==============================================================================================================//
const FTS::Ifaces::ILogger*	LoggersPool::LoggerForModule( QString InModuleName ) const{
    assert( m_pExportLogIface );
	
    return m_pExportLogIface->GetLogger( InModuleName.toStdString().c_str() );
}

//==============================================================================================================//
void LoggersPool::InitilizeLoggerSystem( void ){
	bool correct_id 	= true;
	bool correct_vers 	= true;
    FTS::Ifaces::IExportIface* iface = 0;

    iface = m_pModulesService->GetExportIface( "liblog", LOG_IFACE_ID, LOG_IFACE_VERSION );
	
    if ( iface == 0 ){
        std::cout << "Ошибка загрузки библиотеки логирования" << std::endl;
        return;
    }

	if ( QString( iface->GetId() ) != LOG_IFACE_ID ){
		std::cerr << "Ядро не способно работать с интерфейсом протоколирования [" << iface->GetId() << "]. " <<
			"Требуется интерфейс [" << LOG_IFACE_ID << "]" << std::endl;
		correct_id = false;
	}
	
	if ( iface->GetVersion() != LOG_IFACE_VERSION ){
		std::cerr << "Ядро не способно работать с версией интерфейса протоколирования [" << iface->GetVersion() << "]. " <<
			"Требуется веррия интерфейса [" << LOG_IFACE_VERSION << "]" << std::endl;
		correct_vers = false;
	}
	
    m_pExportLogIface = dynamic_cast< ILog* >( iface );
	
    m_IsInitialized = correct_id && correct_vers && m_pExportLogIface;
		
    if ( m_IsInitialized == false ){
		std::cerr << "Ядро не способно работать с интерфейсом протоколирования!" << std::endl;
		return;
	}
	
    std::cout << "Попытка запроса интерфейса логирования для Ядра" << std::endl;

    m_pSelfLoggerIface = m_pExportLogIface->GetLogger( "Ядро" );
	
    if ( m_pSelfLoggerIface != 0 ){
        m_pSelfLoggerIface->debug( "Получен интерфейс протоколирования из модуля протоколирования" );
	}
}
//==============================================================================================================//
