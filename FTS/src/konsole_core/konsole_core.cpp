
#include <iostream>
#include <signal.h>
#include <QString>
#include <QStringRef>

#include "konsole_core.h"

//==============================================================================================================//
KonsoleCore::KonsoleCore( int argc, char** argv, const char* InProgramName ):
    QCoreApplication( argc, argv ),
    m_ConfigsPool( InProgramName ),
    m_ModulesGrabber( &m_ConfigsPool, &m_LoggersPool, &m_ServiceAppInfo, &m_ActionsPool ),
    m_ICSControllerHandler( &m_ModulesGrabber ){

	QString app_name( argv[ 0 ] );
	app_name.append( "." );
	app_name.append( InProgramName );

	if( app_name.contains( "/" ) == true ){
		QStringRef app_name_dest = app_name.rightRef( app_name.length() - app_name.lastIndexOf( "/" ) - 1 );
		setApplicationName( app_name_dest.toString() );
    } else {
         if( app_name.contains( "\\" ) == true ){
             QStringRef app_name_dest = app_name.rightRef( app_name.length() - app_name.lastIndexOf( "\\" ) - 1 );
             setApplicationName( app_name_dest.toString() );
         } else {
            setApplicationName( app_name );
         }
    }
	
    m_ModulesGrabber.SetICSControllerHandler( &m_ICSControllerHandler );

	signal( SIGINT, KonsoleCore::EndWork );
	
    m_LoggersPool.SetModuleServiceIface( &m_ModulesGrabber );
}

//==============================================================================================================//
KonsoleCore::~KonsoleCore( void ){
    m_ModulesGrabber.StopModules();
	
    m_ModulesGrabber.UnLoadModules();
	
    m_LoggersPool.CoreLogger()->debug( "Завершение работы приложения..." );
}

//==============================================================================================================//
void KonsoleCore::Initialize( void ){
    m_ModulesGrabber.LoadModules();
	
    m_ModulesGrabber.StartModules();
	
    m_LoggersPool.CoreLogger()->debug( "Создан и проинициализирован объект Консольное ядро" );
}

//==============================================================================================================//
void KonsoleCore::Run( void ){
    m_LoggersPool.CoreLogger()->debug( "Приложение запущено..." );
	QCoreApplication::exec();
}

//==============================================================================================================//
void KonsoleCore::EndWork( int InSignalType ){
	std::cerr << "Перехвачен сигнал SIGINT окончания работы программы..." << std::endl;
	QCoreApplication::exit( 0 );
}

//==============================================================================================================//

//#include "konsole_core.moc"
