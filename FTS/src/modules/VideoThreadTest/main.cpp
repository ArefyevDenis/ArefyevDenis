#include <assert.h>
#include "../../../../include/ifaces/main/module_getter_info_iface.h"
#include "../../../../include/ifaces/main/installer_module_iface.h"
#include "../../../../include/common/export_import_defs.h"
#include "module_info.h"
#include "module_VideoThreadTest.h"


//==================================================================================================================//
extern "C" FTS_EXPORT FTS::Ifaces::IModuleGetterInfo* CALL_CONVERSION GetModuleGetterInfoIface ( void ){
    return new ModuleInfo();
}

//==================================================================================================================//
extern "C" FTS_EXPORT void CALL_CONVERSION ServiceModuleInstallIface ( FTS::Ifaces::IInstallerModule* InInstallerIface ){
    assert ( InInstallerIface );
    ModuleVideoThreadTest* module = new ModuleVideoThreadTest();
    InInstallerIface->InstallModule ( module );
}
