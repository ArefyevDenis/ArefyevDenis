
#include <assert.h>
#include <stdio.h>

#include "../../utils/libraries_info_setter.h"
#include "../../../include/common/config.h"
#include "./buildnumber/buildnumber.h"
#include "minor_version.h"

#include "../../../include/ifaces/modules/log/log_iface.h"
#include "../../../include/ifaces/modules/log/log_messages_grabber_iface.h"

#include "my_module_defines.h"
#include "module_info.h"

const char* const MODULE_NAME = "Модуль протоколирования";

//==============================================================================================================//
ModuleInfo::ModuleInfo( void ){
	
}

//==============================================================================================================//
ModuleInfo::~ModuleInfo( void ){
	
}

//==============================================================================================================//
unsigned int CALL_CONVERSION ModuleInfo::GetMajorPartVersion( void ){
	return CORE_MAJOR_VERSION;
}
	
//==============================================================================================================//
unsigned int CALL_CONVERSION ModuleInfo::GetMinorPartVersion( void ){
	return MINOR_PART_VERSION;
}
	
//==============================================================================================================//
unsigned int CALL_CONVERSION ModuleInfo::GetBuildNumber( void ){
	return BUILDNUMBER;
}
	
//==============================================================================================================//
void CALL_CONVERSION ModuleInfo::FillVersionInfo( FTS::BasesTypes::ShortString* OutVersionInfo ){
	assert( OutVersionInfo );
	
    snprintf( OutVersionInfo->Data, FTS::Const::SIZE_SHORT_STRING, "%d.%d.%d",
			GetMajorPartVersion(),
			GetMinorPartVersion(),
			GetBuildNumber()
		);
}

//==============================================================================================================//
void CALL_CONVERSION ModuleInfo::FillModuleReadedName( FTS::BasesTypes::ShortString* OutReadedModuleName ){
    snprintf( OutReadedModuleName->Data, FTS::Const::SIZE_SHORT_STRING,
			MODULE_NAME
		);
}

//==============================================================================================================//
void CALL_CONVERSION ModuleInfo::FillModuleInfo( FTS::BasesTypes::FullString* OutModuleInfo ){
	assert( OutModuleInfo );
	
    snprintf( OutModuleInfo->Data, FTS::Const::SIZE_FULL_STRING, "%s",
			"Модуль протоколирования в системе. Основан на библиотеке log4qt"
		);
}
	
//==============================================================================================================//
unsigned int CALL_CONVERSION ModuleInfo::GetModuleType( void ){
    return FTS::ModuleTypes::SERVICE;
}
	
//==============================================================================================================//
void CALL_CONVERSION ModuleInfo::FillUsageExtendedLibraryDescriber( FTS::Ifaces::IUsageLibraryInfoDescriber* OutDescriber ){
	assert( OutDescriber );
    FTS::Utils::LibrariesInfoSetter info_setter( OutDescriber );
	info_setter.ModuleUsingQt();
}

//==============================================================================================================//
void CALL_CONVERSION ModuleInfo::FillExportingInterfacesDescriber( FTS::Ifaces::IExportInterfaceInfoDescriber* OutDescriber ){
	assert( OutDescriber );
	
    FTS::BasesTypes::ExportInterfaceInfo info;
	
    snprintf( info.InterfaceId.Data, FTS::Const::SIZE_SHORT_STRING, "%s", LOG_IFACE_ID );
	info.MinorVersion = LOG_IFACE_VERSION;
	OutDescriber->AddInterfaceInfo( &info );

    memset( info.InterfaceId.Data, 0, FTS::Const::SIZE_SHORT_STRING );

    snprintf( info.InterfaceId.Data, FTS::Const::SIZE_SHORT_STRING, "%s", LOG_MESSAGES_GRABBER_IFACE_ID );
    info.MinorVersion = LOG_MESSAGES_GRABBER_IFACE_VERSION;
    OutDescriber->AddInterfaceInfo( &info );
}

//==============================================================================================================//
void CALL_CONVERSION ModuleInfo::FillExportingWidgetsDescriber( FTS::Ifaces::IWidgetInfoDescriber* OutDescriber ){
	assert( OutDescriber );
	OutDescriber->Clear();
}
	
//==============================================================================================================//
void CALL_CONVERSION ModuleInfo::FillExportingActionsDescriber( FTS::Ifaces::IShortStringInfoDescriber* OutDescriber ){
	assert( OutDescriber );
	OutDescriber->Clear();
}
	
//==============================================================================================================//
void CALL_CONVERSION ModuleInfo::Release( void ){
	delete this;
}
