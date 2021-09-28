
#include <assert.h>
#include <stdlib.h>

#include <QTextCodec>

#include <ttcclayout.h>
#include <consoleappender.h>
#include <fileappender.h>
#include <signalappender.h>
#include <logmanager.h>

#include "../../../include/ifaces/main/core_main_interfaces_iface.h"
#include "../../../include/ifaces/main/application_info_service_iface.h"

#include "proxy_logger.h"

#include "signalsbynewloggrabber.h"

#include "log_system.h"

//==============================================================================================================//

#define ENV_TMP_DIR 		"TMPDIR"
#define PREFIX_TO_TMP_FILES	"FTS.apps"

//==============================================================================================================//
LogSystem::LogSystem():
        m_pCoreMainIfaces( 0 ),
        m_pTTCCLayout( 0 ),
        m_pConsoleAppender( 0 ),
        m_pFileAppender( 0 ),
        m_pSignalAppender( 0 ),
        m_pSignalsByNewLogGrabber( 0 ),
        m_pLogger( 0 ){
}

//==============================================================================================================//
LogSystem::~LogSystem(){
    ProxyLoggersContIter it = m_AllProxies.begin();
	
    while ( it != m_AllProxies.end() ){
		ProxyLogger* proxy_logger = ( *it ).second;

        if ( proxy_logger != 0 ){
			delete proxy_logger;
			proxy_logger = 0;
		}
		
		it++;
	}
    m_AllProxies.clear();
}

//==============================================================================================================//
void CALL_CONVERSION LogSystem::Initialize(FTS::Ifaces::ICoreMainIfaces *InCoreMainIfaces ){
    m_pCoreMainIfaces = InCoreMainIfaces;
    assert( InCoreMainIfaces );

	// выставление текстового кодека - UTF-8
	QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );

	if ( codec != 0 )
	{
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
		QTextCodec::setCodecForCStrings( codec );
		QTextCodec::setCodecForTr( codec );
#endif
        QTextCodec::setCodecForLocale( codec );
	}
	
	// создание объекта, форматирующего вывод сообщений
    m_pTTCCLayout = new Log4Qt::TTCCLayout( Log4Qt::TTCCLayout::ISO8601 );
    m_pTTCCLayout->setName( QLatin1String( "TTCCLayout" ) );
    m_pTTCCLayout->activateOptions();
	
	// создание объекта, выводящий сообщения в консоль
    m_pConsoleAppender = new Log4Qt::ConsoleAppender( m_pTTCCLayout, Log4Qt::ConsoleAppender::STDOUT_TARGET );
    m_pConsoleAppender->setName( QLatin1String( "ConsoleAppender" ) );
    m_pConsoleAppender->setEncoding( codec );
    m_pConsoleAppender->activateOptions();
	
	// создание объекта, выводящий сообщения в файл
    m_pFileAppender = new Log4Qt::FileAppender( m_pTTCCLayout, GetProtocolFileName() );
    m_pFileAppender->setName( QLatin1String( "FileAppender" ) );
    m_pFileAppender->setEncoding( codec );
    m_pFileAppender->activateOptions();

    m_pSignalAppender = new Log4Qt::SignalAppender();
    m_pSignalAppender->setName( QLatin1String( "SignalAppender" ) );
    m_pSignalAppender->setLayout( m_pTTCCLayout );
    m_pSignalAppender->activateOptions();
	
    m_pSignalsByNewLogGrabber = new SignalsByNewLogGrabber( m_pSignalAppender );

	// назначение корневому журналу сообщений выводящие объекты
    Log4Qt::LogManager::rootLogger()->addAppender( m_pConsoleAppender );
    Log4Qt::LogManager::rootLogger()->addAppender( m_pSignalAppender );
	
	// свой объект протоколирования
	std::string self_logger_name = "Подсистема протоколирования";
    m_pLogger = Log4Qt::LogManager::logger( self_logger_name.c_str() );
    assert( m_pLogger );
	
	// добавление в словрь своего логера
    m_AllLoggers[ self_logger_name ] = m_pLogger;
	
    m_pLogger->debug( "Создан объект протоколирования [%1]", self_logger_name.c_str() );
}

//==============================================================================================================//
void CALL_CONVERSION LogSystem::Start( void ){

}

//==============================================================================================================//
void CALL_CONVERSION LogSystem::Stop( void ){
	
}

//==============================================================================================================//
FTS::Ifaces::IExportIface* CALL_CONVERSION LogSystem::GetExportedIface( const char* InIfaceId, const unsigned int InIfaceVersion ){
    FTS::Ifaces::IExportIface* res = 0;
	
	if ( QString( InIfaceId ) == GetId() && InIfaceVersion == GetVersion() ){
		res = this;
    } else {
        if ( strcmp( LOG_MESSAGES_GRABBER_IFACE_ID, InIfaceId ) == 0 && InIfaceVersion == LOG_MESSAGES_GRABBER_IFACE_VERSION ){
            res = m_pSignalsByNewLogGrabber;
        }
    }
	return res;
}

//==============================================================================================================//
unsigned int CALL_CONVERSION LogSystem::GetVersion( void ){
	return LOG_IFACE_VERSION;
}

//==============================================================================================================//
const char* CALL_CONVERSION LogSystem::GetId( void ){
	return LOG_IFACE_ID;
}

//==============================================================================================================//
const FTS::Ifaces::ILogger* CALL_CONVERSION LogSystem::GetLogger( const char* InSystemName ){
    FTS::Ifaces::ILogger* res = 0;
	
	assert( InSystemName );
	
	std::string logger_name = InSystemName;
	
    ProxyLoggersContIter it_f = m_AllProxies.find( logger_name );
	
    if ( it_f == m_AllProxies.end() ){
		Log4Qt::Logger* need_logger = Log4Qt::LogManager::logger( logger_name.c_str() );
		assert( need_logger );
		
		// добавление в словрь своего логера
        m_AllLoggers[ logger_name ] = need_logger;
		
		// создание объекта-посредника
		ProxyLogger* proxy_logger = new ProxyLogger( need_logger );
        m_AllProxies[ logger_name ] = proxy_logger;
		
        m_pLogger->debug( "Создан объект протоколирования [%1]", logger_name.c_str() );
		
		//
		res = proxy_logger;
    } else {
		res = ( *it_f ).second;
	}
	
	return res;
}

//==============================================================================================================//
QString LogSystem::GetProtocolFileName( void ){
	const char* env_val = getenv( ENV_TMP_DIR );
	
	QString path_to_pid_files;
	path_to_pid_files.append( env_val );
	path_to_pid_files.append( "/" );
	path_to_pid_files.append( PREFIX_TO_TMP_FILES );
		
	
	path_to_pid_files.append( "/" );
	
    path_to_pid_files.append( m_pCoreMainIfaces->GetApplicationService()->GetAppExecutName() );
	path_to_pid_files.append( "." );
	path_to_pid_files.append( "log" );
	
	return path_to_pid_files;
}
//==============================================================================================================//
