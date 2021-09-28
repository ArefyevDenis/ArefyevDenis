#include "module_info.h"
#include <stdio.h>
#include "../../../../include/common/config.h"
#include "../../../utils/libraries_info_setter.h"
#include "../../../../include/ifaces/modules/Video/video_sender_iface.h"
#include "buildnumber/buildnumber.h"



//==================================================================================================================//
ModuleInfo::ModuleInfo(){
}

//==================================================================================================================//
ModuleInfo::~ModuleInfo(){
}

//==================================================================================================================//
unsigned int CALL_CONVERSION ModuleInfo::GetMajorPartVersion ( void ){
    return CORE_MAJOR_VERSION;
}

//==================================================================================================================//
unsigned int CALL_CONVERSION ModuleInfo::GetMinorPartVersion ( void ){
    return CORE_MINOR_VERSION;
}

//==================================================================================================================//
unsigned int CALL_CONVERSION ModuleInfo::GetBuildNumber ( void ){
    return BUILDNUMBER;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleInfo::FillVersionInfo ( FTS::BasesTypes::ShortString* OutVersionInfo ){
    if ( OutVersionInfo )
        snprintf ( OutVersionInfo->Data, FTS::Const::SIZE_SHORT_STRING, "%d.%d.%d", GetMajorPartVersion(), GetMinorPartVersion(), GetBuildNumber() );
}

//==================================================================================================================//
void CALL_CONVERSION ModuleInfo::FillModuleReadedName ( FTS::BasesTypes::ShortString* OutReadedModuleName ){
    if ( OutReadedModuleName )
        snprintf ( OutReadedModuleName->Data, FTS::Const::SIZE_SHORT_STRING, "GstVideoSender - Оганизатор видео-потока" );
}

//==================================================================================================================//
void CALL_CONVERSION ModuleInfo::FillModuleInfo ( FTS::BasesTypes::FullString* OutModuleInfo ){
    if ( OutModuleInfo )
        snprintf ( OutModuleInfo->Data, FTS::Const::SIZE_FULL_STRING, "%s", "Реализует потоковую передачу видео средствами gstreamer" );
}

//==================================================================================================================//
unsigned int CALL_CONVERSION ModuleInfo::GetModuleType ( void ){
    return FTS::ModuleTypes::DATA_PROCESS;
}

//==================================================================================================================//
void CALL_CONVERSION ModuleInfo::FillUsageExtendedLibraryDescriber ( FTS::Ifaces::IUsageLibraryInfoDescriber* OutDescriber ){
    if ( OutDescriber )
        OutDescriber->Clear();
}

//==================================================================================================================//
void CALL_CONVERSION ModuleInfo::FillExportingInterfacesDescriber ( FTS::Ifaces::IExportInterfaceInfoDescriber* OutDescriber ){
    if ( OutDescriber ) {
        OutDescriber->Clear();
        FTS::BasesTypes::ExportInterfaceInfo iface_info;

        snprintf ( iface_info.InterfaceId.Data, FTS::Const::SIZE_SHORT_STRING, "%s", VIDEO_SENDER_IFACE_ID );
        iface_info.MinorVersion = VIDEO_SENDER_IFACE_VERSION;

        OutDescriber->AddInterfaceInfo ( &iface_info );
    }
}

//==================================================================================================================//
void CALL_CONVERSION ModuleInfo::FillExportingWidgetsDescriber ( FTS::Ifaces::IWidgetInfoDescriber* OutDescriber ){
    if ( OutDescriber )
        OutDescriber->Clear();
}

//==================================================================================================================//
void CALL_CONVERSION ModuleInfo::FillExportingActionsDescriber ( FTS::Ifaces::IShortStringInfoDescriber* OutDescriber ){
    if ( OutDescriber )
        OutDescriber->Clear();
}

//==================================================================================================================//
void CALL_CONVERSION ModuleInfo::FillExportingISCParametersDescriber ( FTS::Ifaces::IExportedISCParameters* OutDescriber ){
    if ( OutDescriber )
        OutDescriber->Clear();
}

//==================================================================================================================//
void CALL_CONVERSION ModuleInfo::Release ( void ){
    delete this;
}
//==================================================================================================================//
