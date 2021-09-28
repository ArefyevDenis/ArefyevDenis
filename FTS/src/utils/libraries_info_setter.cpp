

#include <assert.h>
#include <stdio.h>

/*! \remarks Разработчик в своем проекте сам определяет данный файл! В нем указывает, 
 *по каким инклудникам по сути может шариться данный класс
 */
#include <my_module_defines.h>

#include "../../include/ifaces/main/usage_library_info_describer_iface.h"

#include "libraries_info_setter.h"


namespace FTS{
  namespace Utils{

    //==============================================================================================================//
    LibrariesInfoSetter::LibrariesInfoSetter( FTS::Ifaces::IUsageLibraryInfoDescriber* InDescriber ):
      _Describer( InDescriber ){
      assert( _Describer );
    }

    //==============================================================================================================//
    LibrariesInfoSetter::~LibrariesInfoSetter(){

    }

    //==============================================================================================================//
    bool LibrariesInfoSetter::ModuleUsingQt( void ){
      bool res = false;

#ifdef MY_MODULE_USE_QT
#include <QtGlobal>
      FTS::BasesTypes::LibraryInfo qt_info;
      snprintf( qt_info.LibraryName.Data, FTS::Const::SIZE_SHORT_STRING, "%s", "Qt by Nokia" );
      snprintf( qt_info.LibraryVersionInfo.Data, FTS::Const::SIZE_SHORT_STRING, "%s", qVersion() );

      _Describer->AddLibraryInfo( &qt_info );

      res = true;

#endif

      return res;
    }

    //==============================================================================================================//
    bool LibrariesInfoSetter::ModuleUsingBoost( void ){
      bool res = false;

#ifdef MY_MODULE_USE_BOOST
#include <boost/version.hpp>

      FTS::BasesTypes::LibraryInfo qt_info;
      snprintf( qt_info.LibraryName.Data, FTS::Const::SIZE_SHORT_STRING, "%s", "Boost" );
      snprintf( qt_info.LibraryVersionInfo.Data, FTS::Const::SIZE_SHORT_STRING, "%s", BOOST_LIB_VERSION );

      _Describer->AddLibraryInfo( &qt_info );

      res = true;
#endif	

      return res;
    }

    //==============================================================================================================//
    bool LibrariesInfoSetter::ModuleUsingQwt( void ){
      bool res = false;

#ifdef MY_MODULE_USE_QWT
      // TODO: реализовать для Qwt при необходимости!

      FTS::BasesTypes::LibraryInfo qt_info;
      snprintf( qt_info.LibraryName.Data, FST::Const::SIZE_SHORT_STRING, "%s", "TODO: реализовать для Qwt при необходимости!" );
      snprintf( qt_info.LibraryVersionInfo.Data, FTS::Const::SIZE_SHORT_STRING, "%s", "" );

      _Describer->AddLibraryInfo( &qt_info );

      res = true;
#endif	

      return res;
    }
    //==============================================================================================================//

  };
};
