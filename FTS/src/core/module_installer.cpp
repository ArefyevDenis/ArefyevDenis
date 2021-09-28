
#include <assert.h>
#include <iostream>
#include <stdexcept>

#include <QStringList>
#include <QString>

#include "../../include/ifaces/main/module_iface.h"
#include "../../include/ifaces/main/module_getter_info_iface.h"
#include "../../include/ifaces/main/builder_gui_handler_interface.h"

#include "../../include/ifaces/modules/isc/internal_system_control_controller_iface.h"
#include "../../include/ifaces/modules/gui/gui_widgets_manipulator_iface.h"

#include "../../include/factory/module_factory.h"
#include "../../include/common/config.h"
#include "../core/configs_pool.h"
#include "../core/modules_grabber.h"
#include "../core/settings.h"
#include "../core/cross_thread.h"
#include "../core/ics_controller_handler.h"
#include "../core/actions_pool.h"

#include "../utils/export_interfaces_describer.h"
#include "../utils/widget_info_describer.h"
#include "../utils/export_isc_parameter_describer.h"

#include "loggers_pool.h"

#include "module_installer.h"

//--------------------------------------------------------------------------
ModuleInstaller::ModuleInstaller( QString InModuleName, 
								LoggersPool* InLoggersPool, 
								ConfigsPool* InConfigsPool, 
								const ModulesGrabber* InModulesGrabber, 
                                const FTS::Ifaces::IAppService* InApplicationServiceIface,
								ICSControllerHandler* InICSControllerHandler,
								ActionsPool* InActionsPool,
                                FTS::Ifaces::IBuilderGuiHandler* InBuilderGuiInterfaceHandler,
								bool IsLogModule 
							):
	_ModuleConfigurator( 0 ),
	_ModuleInfo( 0 ),
	_Module( 0 ),
	_ModuleName( InModuleName ),
	_LoggersPool( InLoggersPool ),
	_ConfigsPool( InConfigsPool ),
	_ModulesGrabber( InModulesGrabber ),
	_ApplicationServiceIface( InApplicationServiceIface ),
	_ICSControllerHandler( InICSControllerHandler ),
	_ActionsPool( InActionsPool ),
	_BuilderGuiInterfaceHandler( InBuilderGuiInterfaceHandler ),
	_IsLogModule( IsLogModule ),
	_Factory( 0 )
{
	assert( _ModulesGrabber );
	assert( _ICSControllerHandler );
	assert( _ActionsPool );
#ifdef FTS_GUI
	assert( _BuilderGuiInterfaceHandler );
#endif
}
//--------------------------------------------------------------------------
ModuleInstaller::~ModuleInstaller()
{

}
//--------------------------------------------------------------------------
void CALL_CONVERSION ModuleInstaller::InstallModule( FTS::Ifaces::IModule* InModule ){
	assert( InModule );
	
	if( _IsLogModule == false )	{
        GetProtocolIface()->debug( "Модуль [%1] был проинсталлирован", GetModuleId().toStdString().c_str() );
	}
	_Module = InModule;
	try	{
		_Module->Initialize( this );
	}
	catch( std::exception& ex ){
		GetProtocolIface()->error( ex.what() );
	}
}
//--------------------------------------------------------------------------	
FTS::Ifaces::ISettings* CALL_CONVERSION ModuleInstaller::GetSettingsIface( void ){
    FTS::Ifaces::ISettings* settings_iface = _ConfigsPool->GetSettingsObjForModule( GetModuleId().toStdString().c_str() );
	if ( settings_iface == 0 ){
		QString str = QString( "Не удалось выдать интерфейс для настроек модуля [%1]" ).arg( GetModuleId() );
		_LoggersPool->CoreLogger()->error( str.toStdString().c_str() );
		throw std::logic_error( str.toStdString().c_str() );
	}
	return settings_iface;
}

//--------------------------------------------------------------------------
const FTS::Ifaces::ILogger* CALL_CONVERSION	ModuleInstaller::GetProtocolIface( void ){
	QString module_id = GetModuleId();
    const FTS::Ifaces::ILogger* logger_iface = _LoggersPool->LoggerForModule( module_id );
	
    if ( logger_iface == 0 ){
		QString str = QString( "Не удалось выдать интерфейс для протоколирования модуля [%1 - %2]" ).arg( module_id ).arg( GetModuleName() );
		_LoggersPool->CoreLogger()->error( str.toStdString().c_str() );
		throw std::logic_error( str.toStdString().c_str() );
	}
	return logger_iface;
}
//--------------------------------------------------------------------------
FTS::Ifaces::ISettings* ModuleInstaller::GetArgumentsGetterIface( void ){
	QString module_id = GetModuleId();
    FTS::Ifaces::ISettings* settings_iface = _ConfigsPool->GetArgumentsObjForModule( module_id.toStdString().c_str() );
    if ( settings_iface == 0 ){
		QString str = QString( "Не удалось выдать интерфейс для получения аргументов модуля [%1]" ).arg( module_id );
		_LoggersPool->CoreLogger()->error( str.toStdString().c_str() );
		throw std::logic_error( str.toStdString().c_str() );
	}
	return settings_iface;
}

//--------------------------------------------------------------------------
FTS::Ifaces::IWidgetsManipulator* CALL_CONVERSION	ModuleInstaller::GetWidgetsManipulatorIface( void ){
	return this;
}

//--------------------------------------------------------------------------
const FTS::Ifaces::IModulesService* CALL_CONVERSION ModuleInstaller::GetModulesServiceIface( void ){
	return _ModulesGrabber;
}

//--------------------------------------------------------------------------
const FTS::Ifaces::IActionsService* CALL_CONVERSION ModuleInstaller::GetActionsServiceIface( void ){
	return this;
}

//--------------------------------------------------------------------------	
const FTS::Ifaces::IThreadService* CALL_CONVERSION ModuleInstaller::GetThreadService( void ){
	return this;
}

//--------------------------------------------------------------------------	
FTS::Ifaces::IInternalSystemControlService* CALL_CONVERSION	ModuleInstaller::GetInternalSystemControlService( void ){
    FTS::Ifaces::IInternalSystemControlService* res = 0;

	_LoggersPool->CoreLogger()->debug( "Модуль [%1] осуществил запрос интерфейса Контроллера ВСК...", GetModuleId().toStdString().c_str() );
	
	if ( _ICSControllerHandler->GetISCControllerIface() != 0 ){
		_LoggersPool->CoreLogger()->debug( "Результат: передан интерфейс Контроллера ВСК" );
		res = this;
    } else {
		_LoggersPool->CoreLogger()->warn( "Результат: интерфейс Контроллера ВСК не найден в системе!" );	
	}
	return res;
}

//--------------------------------------------------------------------------	
const FTS::Ifaces::IAppService* CALL_CONVERSION ModuleInstaller::GetApplicationService( void ){
	return _ApplicationServiceIface;
}

//--------------------------------------------------------------------------	
FTS::Ifaces::ICrossThread*	ModuleInstaller::GetThread( FTS::Ifaces::IThreadExecute* InExecuteObject ) const{
	assert( InExecuteObject );
	return new CrossThread( InExecuteObject );
}

//--------------------------------------------------------------------------	
void CALL_CONVERSION ModuleInstaller::DeleteThread( FTS::Ifaces::ICrossThread* InThread ) const{
    if ( InThread != 0 ){
		delete InThread;
		InThread = 0;
	}
}

//--------------------------------------------------------------------------	
bool CALL_CONVERSION ModuleInstaller::RegisterInternalSystemControlNode(
        const FTS::Ifaces::InternalSystemControl::IControlParameters* InControlParameters,
        const char* InKeyISCNode
        ){
 	assert( InControlParameters );
	assert( InKeyISCNode );
	assert( _ICSControllerHandler->GetISCControllerIface() );
	
    FTS::Utils::ExportISCParameterDescriber isc_parameters;
	_ModuleInfo->FillExportingISCParametersDescriber( &isc_parameters );
	
	bool res = false;
	
    if( isc_parameters.empty() == false ){
        const FTS::Containers::KeyStringCont* chain_virgin_data = 0;
		
		for( unsigned int i = 0; i < isc_parameters.size(); i++ ){
			if( QString( isc_parameters.at( i ).Key.Data ) == QString( InKeyISCNode ) ){
				chain_virgin_data = &( isc_parameters.at( i ).ChainNodesForParameter );
				break;
			}
		}
		
		std::string full_chain;
		if( chain_virgin_data != 0 ){
            FTS::Containers::KeyStringContCIter it = chain_virgin_data->begin();
            for( unsigned int i = 0; it != chain_virgin_data->end(); it++, i++ ){
				full_chain.append( ( *it ).Data );
                if( i + 1 != chain_virgin_data->size() ){
					// разделитель
					full_chain.append( "/" );
				}
			}
			
            res = _ICSControllerHandler->GetISCControllerIface()->RegisterISCProcessor(
                        InControlParameters,
                        GetModuleId().toStdString().c_str(),
                        InKeyISCNode,
                        full_chain
                        );
		}
	}
	return res;
}

//--------------------------------------------------------------------------	
void CALL_CONVERSION ModuleInstaller::RegisterWidgetsGetter( FTS::Ifaces::IWidgetsGetter* InWidgetsGetter ){
#ifdef FTS_GUI
	assert( InWidgetsGetter );
	assert( _BuilderGuiInterfaceHandler->GetGuiWidgetsManipulator() );

	_LoggersPool->CoreLogger()->debug( "Модуль [%1] осуществил запрос на регистрацию интерфейса передачи виджетов", GetModuleId().toStdString().c_str() );
	
	// запрашиваю описатели виджетов...
    FTS::Utils::WidgetInfoDescriber info_describer;
	_ModuleInfo->FillExportingWidgetsDescriber( &info_describer );
	
	// передаю в модуль...
	if( info_describer.empty() == false ){
		_LoggersPool->CoreLogger()->debug( "В модуль построения графического интерфейса передается информация о виджетах из модуля [%1]", GetModuleId().toStdString().c_str() );
        _BuilderGuiInterfaceHandler->GetGuiWidgetsManipulator()->AddWidgetsInfo(
                    &info_describer,
                    GetModuleId().toStdString().c_str()
                    );
		
		_BuilderGuiInterfaceHandler->GetGuiWidgetsManipulator()->RegisterWidgetsGetter( 
                    InWidgetsGetter,
                    GetModuleId().toStdString().c_str()
                    );
    } else {
		_LoggersPool->CoreLogger()->warn( "Модуль [%1] не имеет виджетов!", GetModuleId().toStdString().c_str() );
	}
#endif
}

//--------------------------------------------------------------------------	
bool CALL_CONVERSION ModuleInstaller::AddAction( const char* InActionId, const QAction* InAction ){
	assert( InAction );
	assert( InActionId );
	
	bool res = false;
	
	QString act_id( InActionId );
	
	res = _ActionsPool->AddAction( GetModuleId(), act_id, InAction );
	
	_LoggersPool->CoreLogger()->debug( "Добавление Действия [%1] для модуля [%2] - Результат [%3]",
                                       act_id.toStdString().c_str(),
                                       GetModuleId().toStdString().c_str(),
                                       res
                                       );
	
	return res; 
}

//--------------------------------------------------------------------------	
bool CALL_CONVERSION ModuleInstaller::ActionInPresence( const char* InModuleId, const char* InActionId ) const{
	assert( InModuleId );
	return _ActionsPool->ActionInPresence( QString( InModuleId ), QString( InActionId ) );
}

//--------------------------------------------------------------------------	
unsigned int CALL_CONVERSION ModuleInstaller::GetCountActions( const char* InModuleId ) const{
	assert( InModuleId );
	return _ActionsPool->GetCountActions( QString( InModuleId ) );
}

//--------------------------------------------------------------------------	
const QAction* CALL_CONVERSION ModuleInstaller::GetActionByIndex( const char* InModuleId, unsigned int InIndex ) const{
	assert( InModuleId );
	return _ActionsPool->GetActionByIndex( QString( InModuleId ), InIndex );
}

//--------------------------------------------------------------------------	
const QAction*	ModuleInstaller::GetActionById( const char* InModuleId, const char* InActionId ) const{
	assert( InModuleId );
	assert( InActionId );
	return _ActionsPool->GetActionById( QString( InModuleId ), QString( InActionId ) );
}

//--------------------------------------------------------------------------		
bool ModuleInstaller::LoadModule( void ){
	bool res = false;
	
	if ( _Factory != 0 ){
		return res;
	}

	_Factory = new FTS::Factory::ModuleFactory( _ModuleName.toStdString().c_str() );

	if ( _Factory->LibraryIsLoad() == true ){
	    _ModuleInfo = _Factory->GetModuleGetterInfoIface();
	    assert( _ModuleInfo );

	    // заполним в соответствии с новой схемой инсталляции интерфейсов структуру с описанием интерфейсов...
	    FTS::Utils::ExportInterfacesDescriber  ifaces_describer;
	    _ModuleInfo->FillExportingInterfacesDescriber( &ifaces_describer );

	    if ( ifaces_describer.empty() == false ){
		for ( unsigned int i = 0; i < ifaces_describer.size(); i++ ){
		    bool can_install = false;
		    if ( _ModuleInfo->GetMajorPartVersion() == CORE_MAJOR_VERSION ){
			can_install = true;
		      } else {
			std::cerr << "Для модуля [" << GetModuleId().toStdString().c_str() << "] невозможно установить интерфейс [" << ifaces_describer.at( i ).InterfaceId.Data <<
			  "], поскольку не совпадают старшие части ядра [" << CORE_MAJOR_VERSION << "] " <<
			  "и модуля [" << _ModuleInfo->GetMajorPartVersion() << "]" << std::endl;
		      }

		    if ( can_install == true ){
			IfaceStructDescriber iface_descr;
			iface_descr.interface_id 	= ifaces_describer.at( i ).InterfaceId.Data;
			iface_descr.minor_version	= ifaces_describer.at( i ).MinorVersion;
			std::cout << "Модуль [" << GetModuleId().toStdString() << "] установил описатель интерфейса [" <<
			  iface_descr.interface_id.toStdString() <<
			  "] версии " << "[" << CORE_MAJOR_VERSION << "." << iface_descr.minor_version << "]" << std::endl;
			_Interfaces.push_back( iface_descr );
		      }
		  }
	      } else {
		// 			QString str = QString( "Модуль [%1] не экспортирует интерфейсы!" ).arg( GetModuleId() );
// 			_LoggersPool->CoreLogger()->error( str.toStdString().c_str() );
		}
    } else {
		std::cerr << "Модуль [" << GetModuleId().toStdString().c_str() << "] не удалось загрузить!!!" << std::endl;
	}
	return _Factory->LibraryIsLoad();
}

//--------------------------------------------------------------------------	
bool ModuleInstaller::UnLoadModule( void ) {
    if ( _ModuleInfo != 0 ){
		_ModuleInfo->Release();
		_ModuleInfo = 0;
	}
	return true;
}

//--------------------------------------------------------------------------
bool ModuleInstaller::InstallModule( void ){
	if ( _Factory != 0 ){
		_Factory->ServiceModuleInstallIface( this );
		// ну и немного особы случай для модуля протоколирования...
		if ( _IsLogModule == true ){
			_LoggersPool->LogModuleIsLoaded();
		}
	}
	return ( _Factory != 0 );
}

//--------------------------------------------------------------------------	
bool ModuleInstaller::UnInstallModule( void ){
	bool res = ( _Module != 0 );
	
	if ( _Module != 0 ){
		try{
			_Module->Release();
		}
		catch( std::exception& ex ){
			GetProtocolIface()->error( ex.what() );
		}
		_Module = 0;
	}
    return res;
}

//--------------------------------------------------------------------------
bool ModuleInstaller::ModuleIsLoaded( void ) const{
	bool res = false;
	if ( _Factory != 0 ){
		res = _Factory->LibraryIsLoad();
	}
	return res;
}

//--------------------------------------------------------------------------
bool ModuleInstaller::StartWorkModule( void ){
	assert( _Module );
	try{
        GetProtocolIface()->debug( "Запуск модуля [%1]...", GetModuleId().toStdString().c_str() );
		_Module->Start();
	}
	catch( std::exception& ex ){
		GetProtocolIface()->error( ex.what() );
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------
bool ModuleInstaller::StopWorkModule( void ){
	assert( _Module );
	try{
        GetProtocolIface()->debug( "Останов модуля [%1]...", GetModuleId().toStdString().c_str() );
		_Module->Stop();
	}
	catch( std::exception& ex ){
		GetProtocolIface()->error( ex.what() );
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------
bool ModuleInstaller::IsMyModuleId( const char* InModuleId ) const{
	assert( InModuleId );
	bool res = false;
	QString in_mod_id( InModuleId );	
	res = ( in_mod_id == GetModuleId() );
	return res;
}

//--------------------------------------------------------------------------
bool ModuleInstaller::FillInterfaseDescriber(IfaceStructDescriber *InOutIfaceDescriber ) const{
	assert( InOutIfaceDescriber );
	assert( _Module );
	
	bool res = false;
    IfacesContCIter it = _Interfaces.begin();
    try {
		while ( it != _Interfaces.end() ){
            if ( ( *it ).interface_id == InOutIfaceDescriber->interface_id && ( *it ).minor_version == InOutIfaceDescriber->minor_version){
                InOutIfaceDescriber->ptr_iface = _Module->GetExportedIface(	InOutIfaceDescriber->interface_id.toStdString().c_str(), InOutIfaceDescriber->minor_version);
				res = ( InOutIfaceDescriber->ptr_iface != 0 );				
				break;
			}
			it++;
		}
	}
	catch( std::exception& ex ){
		_LoggersPool->CoreLogger()->error( ex.what() );
	}
	
	return res;
}

//--------------------------------------------------------------------------
QString ModuleInstaller::GetModuleId( void ) const{
	QString res = "";
	int pos_point = _ModuleName.indexOf( '.' );
	if ( pos_point >= 0 ){
		res = _ModuleName.left( pos_point );
    }
	return res;
}

//--------------------------------------------------------------------------
QString	ModuleInstaller::GetModuleName( void ) const{
	if ( _ModuleInfo == 0 ){
		QString str = QString( "Невозможно получить имя модуля [%1], поскольку не реализован интерфейс описания!" ).arg( GetModuleId() );
		_LoggersPool->CoreLogger()->error( str.toStdString().c_str() );
		
		throw std::logic_error( str.toStdString().c_str() );
	}
	
    FTS::BasesTypes::ShortString info;
	_ModuleInfo->FillModuleReadedName( &info );
	
	return info.Data;
}
//--------------------------------------------------------------------------
