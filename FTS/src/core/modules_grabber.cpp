
#include <assert.h>
#include <stdexcept>
#include <iostream>

#include <QString>
#include <QMutexLocker>

#include "../../include/common/config-win32.h"
#include "../../include/ifaces/main/builder_gui_handler_interface.h"

#include "configs_pool.h"
#include "loggers_pool.h"
#include "settings.h"
#include "module_installer.h"
#include "ics_controller_handler.h"
#include "actions_pool.h"

#include "modules_grabber.h"

//==============================================================================================================//
const QString BASE_SECTION 	= "MODULES_PARAMETERS";
const QString MODULES_LIST 	= "MODULES_LIST";
const QString CFG_MODULE	= "MODULE";

const QString SAMPLE_MODULE_LNX = "sample_module.so";
const QString SAMPLE_MODULE_WIN = "sample_module.dll";

const QString LOG_MODULE_NAME_LNX = "liblog.so";
const QString LOG_MODULE_NAME_WIN = "liblog.dll";
//==============================================================================================================//
ModulesGrabber::ModulesGrabber( ConfigsPool* InConfigsPool,
								LoggersPool* InLoggersPool, 
                                const FTS::Ifaces::IAppService* InApplicationServiceIface,
								ActionsPool* InActionsPool
  							):
    m_pConfigsPool( InConfigsPool ),
    m_pLoggersPool( InLoggersPool ),
    m_pAppServiceIface( InApplicationServiceIface ),
    m_pICSControllerHandler( 0 ),
    m_pSettings( 0 ),
    m_pWidgetsManipulator( 0 ),
    m_pActionsPool( InActionsPool ),
    m_pBuilderGuiInterfaceHandler( 0 ){
    m_pSettings = m_pConfigsPool->GetModulesSettingsObj();
    assert( m_pSettings );
    assert( m_pAppServiceIface );
    assert( m_pActionsPool );
}

//==============================================================================================================//
ModulesGrabber::~ModulesGrabber(){
	UnLoadModules();
	
    ModuleInstallerContIter it = m_Installers.begin();
    while ( it != m_Installers.end() ){
		( *it )->UnInstallModule();
		
		ModuleInstaller* installer = *it;
		delete installer;
		installer = 0;
		
		it++;
	}	
}

//==============================================================================================================//
void ModulesGrabber::LoadModules( void ){
	// построим список с перечислением модулей для загрузки в систему
 	BuildModulesListForLoading();
	
	// сразу на входе пишем пример в файл + все данные что загрузили
  	WriteSampleInformation();
	
	// загрузим модуль протоколирования
	LoadLogModule();	
	
	// загрузим все оставшиеся модули
	LoadAllModulesWithoutLog();
	
	// и теперь все модули проинсталлируем
	InstallAllModules();
}

//==============================================================================================================//
FTS::Ifaces::IExportIface* ModulesGrabber::GetExportIface( const char* InModuleId, const char* InIfaceId, unsigned int InIfaceVersion ) const throw(){

  FTS::Ifaces::IExportIface* res = 0;

  ModuleInstallerContCIter it = m_Installers.begin();

  while ( it != m_Installers.end() ){
      if ( ( *it )->IsMyModuleId( InModuleId ) == true ){
          IfaceStructDescriber iface_descr;
          iface_descr.interface_id 	= InIfaceId;
          iface_descr.minor_version 	= InIfaceVersion;

          if ( ( *it )->FillInterfaseDescriber( &iface_descr ) == true ){
              res = iface_descr.ptr_iface;
              break;
            }
        }
      it++;
    }

  if ( res == 0 ){
      QString str = QString( "В системе не выставлен интерфейс с параметрами [Модуль = %1; Интерфейс = %2; Версия = %3]" )
          .arg( InModuleId ).arg( InIfaceId ).arg( InIfaceVersion );

      m_pLoggersPool->CoreLogger()->error( str.toStdString().c_str() );
    }

  return res;
}

//==============================================================================================================//
unsigned int CALL_CONVERSION ModulesGrabber::GetModulesCount( void ) const{
    return ( unsigned int )m_Installers.size();
}

//==============================================================================================================//
const std::string CALL_CONVERSION ModulesGrabber::GetModuleIdByIndex( unsigned int InIndex ) const{
    ModuleInstallerContCIter it = m_Installers.begin();
	unsigned int indx = 0;
	
    for ( ; it != m_Installers.end(); it++, indx++ ){
		if( indx == InIndex )
			return ( *it )->GetModuleId().toStdString();
	}
	
	return std::string();
}

//==============================================================================================================//
void ModulesGrabber::SetWidgetsManipulatorIface( FTS::Ifaces::IWidgetsManipulator* InWidgetsManipulatorIface ){
	if ( InWidgetsManipulatorIface != 0 ){
        m_pWidgetsManipulator = InWidgetsManipulatorIface;
	}
}

//==============================================================================================================//
FTS::Ifaces::IWidgetsManipulator* ModulesGrabber::GetWidgetsManipulatorIface( void ) const{
    return m_pWidgetsManipulator;
}

//==============================================================================================================//
void ModulesGrabber::SetICSControllerHandler( ICSControllerHandler* InICSControllerHandler ){
    m_pICSControllerHandler = InICSControllerHandler;
    assert( m_pICSControllerHandler );
}

//==============================================================================================================//
void ModulesGrabber::SetBuilderGuiInterfaceHandler( FTS::Ifaces::IBuilderGuiHandler* InBuilderGuiInterfaceHandler ){
    m_pBuilderGuiInterfaceHandler = InBuilderGuiInterfaceHandler;
    assert( m_pBuilderGuiInterfaceHandler );
}

//==============================================================================================================//
void ModulesGrabber::StartModules( void ){
    m_pLoggersPool->CoreLogger()->debug( "Запуск всех модулей" );
	
    ModuleInstallerContIter it = m_Installers.begin();
    while ( it != m_Installers.end() ){
		( *it )->StartWorkModule();
		it++;
	}

#ifdef FTS_GUI
	// если Ядро графическое, то уведомляем модуль, отвечающий за компоновку интерфейса 
	// о возможности его создания
    if( m_pBuilderGuiInterfaceHandler != 0 ){
        m_pBuilderGuiInterfaceHandler->BuildGui();
	}
#endif
}

//==============================================================================================================//
void ModulesGrabber::StopModules( void ){
    m_pLoggersPool->CoreLogger()->debug( "Остановка всех модулей" );
    ModuleInstallerContIter it = m_Installers.begin();
    while ( it != m_Installers.end() ){
		( *it )->StopWorkModule();
		it++;
	}
}

//==============================================================================================================//
void ModulesGrabber::UnLoadModules( void ){
    m_pLoggersPool->CoreLogger()->debug( "Выгрузка всех модулей" );
	
    ModuleInstallerContIter it = m_Installers.begin();
    while ( it != m_Installers.end() ){
		( *it )->UnLoadModule();
		it++;
	}
	
    m_ModulesLibrariesNames.clear();
}

//==============================================================================================================//
void ModulesGrabber::BuildModulesListForLoading( void ){
    m_ModulesLibrariesNames.clear();
    int modules_count = m_pSettings->BeginReadArray( MODULES_LIST );
	
	for( int i = 0; i < modules_count; i++ ){
        m_pSettings->SetArrayIndex( i );
        QString mod_name = m_pSettings->Value( CFG_MODULE, "" ).toString();
        m_ModulesLibrariesNames.append( mod_name );
	}
    m_pSettings->EndArray();
		
    if ( m_ModulesLibrariesNames.empty() == false ){
		DeleteSampleInformation();	
		
		// вывод перечня всех модулей для запуска...
        std::cout << "Ядро: Всего модулей для загрузки [" << m_ModulesLibrariesNames.size() << "]" << std::endl;
        for ( int i = 0; i < m_ModulesLibrariesNames.size(); i++ ){
            std::cout << i + 1 << ") " << m_ModulesLibrariesNames.at( i ).toStdString() << std::endl;
		}
    } else	{
// 		TODO: Выкинуть сообщение для оператора о некорректных параметрах конфигурации!!!
	}
}

//==============================================================================================================//
void ModulesGrabber::WriteSampleInformation( void ){
  QStringList all_modules = m_ModulesLibrariesNames;

#ifdef WIN32
  all_modules << SAMPLE_MODULE_WIN;
#else
  all_modules << SAMPLE_MODULE_LNX;
#endif

  m_pSettings->BeginWriteArray( MODULES_LIST );

  for( int i = 0; i < all_modules.size(); i++ ){
      m_pSettings->SetArrayIndex( i );
      m_pSettings->SetValue( CFG_MODULE, all_modules.at( i ) );
    }

  m_pSettings->EndArray();

  // и перезапишем принудительно
  m_pSettings->Sync();
}

//==============================================================================================================//
void ModulesGrabber::DeleteSampleInformation( void ){
#ifdef WIN32
    if ( m_ModulesLibrariesNames.contains( SAMPLE_MODULE_WIN ) == true ){
        m_ModulesLibrariesNames.removeAt( m_ModulesLibrariesNames.indexOf( SAMPLE_MODULE_WIN ) );
	}
#else
    if ( m_ModulesLibrariesNames.contains( SAMPLE_MODULE_LNX ) == true ){
        m_ModulesLibrariesNames.removeAt( m_ModulesLibrariesNames.indexOf( SAMPLE_MODULE_LNX ) );
	}
#endif
}

//==============================================================================================================//
void ModulesGrabber::LoadLogModule( void ){
	bool is_present_in_cfg = false;
	
#ifdef WIN32
    is_present_in_cfg = m_ModulesLibrariesNames.contains( LOG_MODULE_NAME_WIN );
#else
    is_present_in_cfg = m_ModulesLibrariesNames.contains( LOG_MODULE_NAME_LNX );
#endif
	
	if ( is_present_in_cfg == false ){
		return;
	}
	
	ModuleInstaller* modi_log = 0;
	
	bool res_load = false;
#ifdef WIN32
    modi_log = new ModuleInstaller( LOG_MODULE_NAME_WIN, m_pLoggersPool, m_pConfigsPool, this, m_pAppServiceIface, m_pICSControllerHandler, m_pActionsPool, m_pBuilderGuiInterfaceHandler, true );
	
	res_load = modi_log->LoadModule();
#else
    modi_log = new ModuleInstaller( LOG_MODULE_NAME_LNX, m_pLoggersPool, m_pConfigsPool, this, m_pAppServiceIface, m_pICSControllerHandler, m_pActionsPool, m_pBuilderGuiInterfaceHandler, true );
	
    res_load = modi_log->LoadModule();
#endif
	
	if ( res_load == true ){
        m_Installers.push_back( modi_log );
    } else {
		delete modi_log;
		modi_log = 0;
	}
}

//==============================================================================================================//
void ModulesGrabber::LoadAllModulesWithoutLog( void ){
  for ( int i = 0; i < m_ModulesLibrariesNames.size(); i++ ){
      bool is_log = false;

      QString current_lib_name = m_ModulesLibrariesNames.at( i );

#ifdef WIN32
      if ( current_lib_name == LOG_MODULE_NAME_WIN ){
          is_log = true;
        }
#else
      if ( current_lib_name == LOG_MODULE_NAME_LNX ){
          is_log = true;
        }
#endif
      if ( is_log == false ){
          ModuleInstaller* modi_current = new ModuleInstaller(
                current_lib_name,
                m_pLoggersPool,
                m_pConfigsPool,
                this,
                m_pAppServiceIface,
                m_pICSControllerHandler,
                m_pActionsPool,
                m_pBuilderGuiInterfaceHandler
                );

          bool res_load = modi_current->LoadModule();

          if ( res_load == true ){
              m_Installers.push_back( modi_current );
            } else {
              delete modi_current;
              modi_current = 0;
            }
        }
    }
}

//==============================================================================================================//
void ModulesGrabber::InstallAllModules( void ){
    ModuleInstallerContIter it = m_Installers.begin();
    while ( it != m_Installers.end() ){
		( *it )->InstallModule();
		it++;
	}
}

//==============================================================================================================//
