
#include <iostream>

#include <QCoreApplication>
#include <QDir>

#include <boost/filesystem.hpp>

#include "service_application_info.h"

//==============================================================================================================//
#define ENV_TMP_DIR             "TMPDIR"
#define PREFIX_TO_PID_FILES 	"FTS.apps"

//==============================================================================================================//
ServiceAppInfo::ServiceAppInfo( void ):
        m_CoreTempDirectoryPath( "" ){

}

//==============================================================================================================//
ServiceAppInfo::~ServiceAppInfo( void ){

}

//==============================================================================================================//
QString	CALL_CONVERSION ServiceAppInfo::GetAppBinaryPath( void ) const{
	return QCoreApplication::instance()->applicationDirPath();
}

//==============================================================================================================//
QString	CALL_CONVERSION ServiceAppInfo::GetAppExecutName( void ) const{
	return QCoreApplication::instance()->applicationName();
}

//==============================================================================================================//
QStringList	CALL_CONVERSION ServiceAppInfo::GetAppArguments( void ) const{
	return QCoreApplication::instance()->arguments();
}

//==============================================================================================================//
QString CALL_CONVERSION ServiceAppInfo::GetAppCaption( void ) const{
	return QCoreApplication::instance()->applicationName();
}

//==============================================================================================================//
qint64 CALL_CONVERSION ServiceAppInfo::GetAppPID( void ) const{
	return QCoreApplication::instance()->applicationPid();
}

//==============================================================================================================//
QString CALL_CONVERSION ServiceAppInfo::GetCoreTempDirectoryPath( void ) const{
    if( m_CoreTempDirectoryPath.length() != 0 ){
        return m_CoreTempDirectoryPath;
	}
	
	// создаем файл с PID текущего процесса в темповой директории системы
	const char* env_val = getenv( ENV_TMP_DIR );
	std::string pid_file_full_path;
	
	if ( env_val == 0 ){
		std::cerr << "В Системе не выставлена переменная [" << ENV_TMP_DIR << "]" << std::endl;
    } else {
        m_CoreTempDirectoryPath.append( env_val );
        m_CoreTempDirectoryPath.append( "/" );
        m_CoreTempDirectoryPath.append( PREFIX_TO_PID_FILES );
		
        QDir dir( m_CoreTempDirectoryPath );
        if( dir.exists() == false ){
            boost::filesystem::create_directories( m_CoreTempDirectoryPath.toStdString().c_str() );
		}
	}
	
    return m_CoreTempDirectoryPath;
}
//==============================================================================================================//
