#pragma once

#include "os_define.h"

#ifdef WIN32
#	define CALL_CONVERSION __stdcall
#else
#	define CALL_CONVERSION
#endif


//////////////////////////////////////////////////////////////////////////
#ifdef WIN32
#	ifdef __BORLANDC__
#	endif

#	ifdef _MSC_VER
#		ifndef WINVER                          // Specifies that the minimum required platform is Windows Vista.
#			define WINVER 0x0600           // Change this to the appropriate value to target other versions of Windows.
#		endif

#		ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
#			define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
#		endif

#		ifndef _WIN32_WINDOWS          // Specifies that the minimum required platform is Windows 98.
#			define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#		endif

#		ifndef _WIN32_IE                       // Specifies that the minimum required platform is Internet Explorer 7.0.
#			define _WIN32_IE 0x0700        // Change this to the appropriate value to target other versions of IE.
#		endif

#		define WIN32_LEAN_AND_MEAN
#		define _CRT_SECURE_NO_WARNINGS		//отключаем оповещения о старых методах CRT
#	endif

#	include <Windows.h>



#ifdef  _MSC_VER 
#pragma warning( disable : 4996 )
#endif

#endif
//////////////////////////////////////////////////////////////////////////
