
#pragma once 
#pragma pack( push, 4 )

#include <iostream>
#include "../common/config-win32.h"

#ifdef WIN32
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif

namespace FTS{
        namespace Ifaces{
		class IModuleGetterInfo;
		class IServiceModuleInstall;
		class IServiceModuleUnInstall;
		
		class IInstallerModule;
		class IModule;
	};
	
	namespace Factory{

/**
* @brief Класс фабрики модуля системы FTS
**/
class ModuleFactory
{
private:
    /*! Определение прототипов функций*/
    typedef FTS::Ifaces::IModuleGetterInfo* ( CALL_CONVERSION *dummyGetModuleGetterInfoIfaceFnc )( void );
    typedef void ( CALL_CONVERSION *dummyServiceModuleInstallIfaceFnc )( FTS::Ifaces::IInstallerModule* );
	
private:
    dummyGetModuleGetterInfoIfaceFnc GetModuleGetterInfoIfaceFnc;
    dummyServiceModuleInstallIfaceFnc ServiceModuleInstallIfaceFnc;
	
#ifdef WIN32
	HMODULE hDLL;
#else
    void*	hDLL;
#endif
	
private:
    bool Load( const char* InModuleName ){
        bool res = false;
        if ( InModuleName == 0 ){
            return res;
        }

#ifdef WIN32
		hDLL = LoadLibrary( InModuleName );
        if ( hDLL == 0 ) return res;
        
		GetModuleGetterInfoIfaceFnc 		= ( dummyGetModuleGetterInfoIfaceFnc) GetProcAddress( hDLL, "GetModuleGetterInfoIface" );
		ServiceModuleInstallIfaceFnc 		= ( dummyServiceModuleInstallIfaceFnc) GetProcAddress( hDLL, "ServiceModuleInstallIface" );
// 		ServiceModuleUnInstallIfaceFnc		= ( dummyServiceModuleUnInstallIfaceFnc) GetProcAddress( hDLL, "ServiceModuleUnInstallIface" );
#else
        hDLL = dlopen( InModuleName, RTLD_LAZY );
        if( hDLL == 0 ){
            return res;
        }
        GetModuleGetterInfoIfaceFnc = ( dummyGetModuleGetterInfoIfaceFnc) dlsym( hDLL, "GetModuleGetterInfoIface" );
        ServiceModuleInstallIfaceFnc = ( dummyServiceModuleInstallIfaceFnc) dlsym( hDLL, "ServiceModuleInstallIface" );
#endif

        res = ( GetModuleGetterInfoIfaceFnc != 0 && ServiceModuleInstallIfaceFnc != 0);
		
        return res;
    }
    
    void Free( void ){
#ifdef WIN32
		FreeLibrary( hDLL );
#else
        dlclose( hDLL );
#endif
        hDLL = 0;
    }

	
	
public:
	ModuleFactory( const char* InModuleName ): 
            GetModuleGetterInfoIfaceFnc( 0 ),
            ServiceModuleInstallIfaceFnc( 0 ),
            hDLL( 0 ){
            if ( Load( InModuleName ) == false ){
#ifdef WIN32
			std::cerr << "Ошибка при загрузке библиотеки [" << InModuleName << "] - [" << std::hex << GetLastError() << "]" << std::endl;
#else
                std::cerr << "Ошибка при загрузке библиотеки [" << InModuleName << "] - [" <<  dlerror() << "]" << std::endl;
#endif	
            }
	}
	
	~ModuleFactory( void )
	{
		Free();
	}
	
        bool LibraryIsLoad( void ) const {
                bool res = ( GetModuleGetterInfoIfaceFnc != 0 && ServiceModuleInstallIfaceFnc != 0 );
		return res;
	}
		
        FTS::Ifaces::IModuleGetterInfo* GetModuleGetterInfoIface( void ) const	{
            FTS::Ifaces::IModuleGetterInfo* res = 0;
            if ( GetModuleGetterInfoIfaceFnc != 0 ){
                res = GetModuleGetterInfoIfaceFnc();
            }
            return res;
	}
	
        void	ServiceModuleInstallIface( FTS::Ifaces::IInstallerModule* InInstallerIface ) const{
            if ( ServiceModuleInstallIfaceFnc != 0 ){
                ServiceModuleInstallIfaceFnc( InInstallerIface );
            }
	}
		
};


	};
};
