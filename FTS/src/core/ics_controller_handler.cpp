
#include <assert.h>

#include <QString>

#include "../../include/common/config-win32.h"

#include "../../include/ifaces/main/modules_service_iface.h"
#include "../../include/ifaces/modules/isc/internal_system_control_controller_iface.h"

#include "ics_controller_handler.h"

//==============================================================================================================//
const QString ISC_CONTROLLER_MODULE_NAME_LNX = "libISCController";
const QString ISC_CONTROLLER_MODULE_NAME_WIN = ISC_CONTROLLER_MODULE_NAME_LNX;

//==============================================================================================================//
ICSControllerHandler::ICSControllerHandler( FTS::Ifaces::IModulesService* InModulesService ):
		_ModulesService( InModulesService ){
	assert( _ModulesService );
}

//==============================================================================================================//
ICSControllerHandler::~ICSControllerHandler( void ){
	
}

//==============================================================================================================//
IISCController*	ICSControllerHandler::GetISCControllerIface( void ){

    IISCController* res = 0;
	
	QString module_id;
	
#ifdef WIN32
	module_id = ISC_CONTROLLER_MODULE_NAME_WIN;
#else
	module_id = ISC_CONTROLLER_MODULE_NAME_LNX;
#endif
	
    FTS::Ifaces::IExportIface* iface = _ModulesService->GetExportIface(
															module_id.toStdString().c_str(),
															ISC_CONTROLLER_IFACE_ID,
															ISC_CONTROLLER_IFACE_VERSION
														);
	
	res = dynamic_cast< IISCController* >( iface ); 
	
	return res;
}
//==============================================================================================================//


