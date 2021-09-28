
//==============================================================================================================//
#define MODULES_SETTINGS_ID 		"modules"
#define APPLICATION_SETTINGS_ID 	"application"

#define ENV_VAR_NAME 				"FTS_MODULES_CFG_PATH"
//==============================================================================================================//

#include <assert.h>
#include <stdlib.h>
#include <stdexcept>

#include "../../include/common/config.h"
#include "settings.h"

#include "configs_pool.h"

//==============================================================================================================//
ConfigsPool::ConfigsPool( const char* InProgramName ):
  m_ApplicationConfigurator( 0 ),
  m_ModulesConfigurator( 0 ){
  const char* env_val = getenv( ENV_VAR_NAME );
  if ( env_val == 0 ){
      QString str = QString( "Не выставлено системная переменная [%1]" ).arg( ENV_VAR_NAME );
      throw std::logic_error( str.toStdString().c_str() );
    }

  m_FullPathToConfigs = "";
  m_FullPathToConfigs.append( env_val );
  m_FullPathToConfigs.append( "/" );
  m_FullPathToConfigs.append( InProgramName );
  m_FullPathToConfigs.append( "/" );
  m_FullPathToConfigs.append( PREFIX_TO_ALL_CONFIGS );

  m_FullPathToArguments = "";
  m_FullPathToArguments.append( env_val );
  m_FullPathToArguments.append( "/" );
  m_FullPathToArguments.append( InProgramName );
  m_FullPathToArguments.append( "/" );
  m_FullPathToArguments.append( PREFIX_TO_MODULES_ARGUMENTS );

  QString modules_cfg_file_name;
  modules_cfg_file_name.append( m_FullPathToConfigs );
  modules_cfg_file_name.append( "/" );
  modules_cfg_file_name.append( MODULES_FILE_NAME );

  QString application_cfg_file_name;
  application_cfg_file_name.append( m_FullPathToConfigs );
  application_cfg_file_name.append( "/" );
  application_cfg_file_name.append( APPLICATION_FILE_NAME );

  m_ModulesConfigurator 	= new Settings( modules_cfg_file_name, CONFIG_FILE_EXT,  m_FullPathToConfigs );
  m_ApplicationConfigurator 	= new Settings( application_cfg_file_name, CONFIG_FILE_EXT, m_FullPathToConfigs );

  m_AllSettings[ MODULES_SETTINGS_ID ] 	= m_ModulesConfigurator;
  m_AllSettings[ APPLICATION_SETTINGS_ID ] = m_ApplicationConfigurator;
}

//==============================================================================================================//
ConfigsPool::~ConfigsPool( void ){
  // чистим все объекты для работы с параметрами конфигурации... {
  SettingsContIter it = m_AllSettings.begin();

  while ( it != m_AllSettings.end() ){
      Settings* cfg = it.value();
      if ( cfg != 0 ){
          cfg->Sync();
          delete cfg;
          cfg = 0;
        }
      it++;
    }

  m_AllSettings.clear();
  // }

  // чистим все объекты для работы с параметрами аргументов модулей {
  it = m_AllArguments.begin();

  while ( it != m_AllArguments.end() ){
      Settings* cfg = it.value();

      if ( cfg != 0 ){
          cfg->Sync();

          delete cfg;
          cfg = 0;
        }

      it++;
    }

  m_AllArguments.clear();
}

//==============================================================================================================//
Settings* ConfigsPool::GetModulesSettingsObj( void ){
    return m_ModulesConfigurator;
}

//==============================================================================================================//
Settings* ConfigsPool::GetApplicationSettingsObj( void ){
    return m_ApplicationConfigurator;
}

//---------------------------------------------------------------
Settings* ConfigsPool::GetSettingsObjForModule( const char* InModuleId ){
  assert( InModuleId );
  Settings* res = 0;
  QString key_to_find( InModuleId );
  SettingsContIter it_f = m_AllSettings.find( key_to_find );

  if ( it_f != m_AllSettings.end() ){
      res = it_f.value();
    }

  if ( res == 0 ){
      QString module_cfg_file_name;
      module_cfg_file_name.append( m_FullPathToConfigs );
      module_cfg_file_name.append( "/" );
      module_cfg_file_name.append( PREFIX_TO_MODULES_CONFIGS );
      module_cfg_file_name.append( "/" );
      module_cfg_file_name.append( InModuleId );

      res = new Settings( module_cfg_file_name, CONFIG_FILE_EXT, m_FullPathToConfigs );

      m_AllSettings[ InModuleId ] 	= res;
    }
  return res;
}

//==============================================================================================================//
Settings* ConfigsPool::GetArgumentsObjForModule( const char* InModuleId ){
	assert( InModuleId );
	
	Settings* res = 0;
	
	QString key_to_find( InModuleId );
	
    SettingsContIter it_f = m_AllArguments.find( key_to_find );
	
    if ( it_f != m_AllArguments.end() ){
		res = it_f.value();
	}
	
	if ( res == 0 ){
		QString module_cfg_file_name;
        module_cfg_file_name.append( m_FullPathToArguments );
		module_cfg_file_name.append( "/" );
        module_cfg_file_name.append( InModuleId );
		
        res = new Settings( module_cfg_file_name, ARGUMENTS_FILE_EXT, m_FullPathToConfigs );
		
        m_AllArguments[ InModuleId ] 	= res;
	}
	return res;
}

//==============================================================================================================//
