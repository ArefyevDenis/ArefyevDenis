#include <QtCore/QTextCodec>

#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/version.hpp>
#include <fstream>
#include <string>

#include "../core/module_installer.h"

#include "../../include/common/config-win32.h"

#include "konsole_core.h"


#ifndef WIN32
#	include <locale.h>
#endif

#define INDX_PROGRAM_ID         1
#define ENV_TMP_DIR             "TMPDIR"
#define PREFIX_TO_PID_FILES     "FTS.apps"

//**************************************************************************************************************//
#	if BOOST_VERSION < 104900
#		define MY_BOOST_LIB_VERSION_EARLIER_1_49
#	elif BOOST_VERSION >= 104900 && BOOST_VERSION < 105000
#		define MY_BOOST_LIB_VERSION_IS_1_49
#	else
#		define MY_BOOST_LIB_VERSION_GREATER_1_49
#	endif
//**************************************************************************************************************//



//==============================================================================================================//
int main( int argc, char *argv[] ){
	
  // получаем идиентификатор программы...
  const char* program_id = argv[ INDX_PROGRAM_ID ];
  if ( program_id == 0 ){
      std::cerr << "Неверный входной аргумент PROGRAM_ID!" << std::endl;
      return 0;
    }

  std::cout << "PROGRAM_ID [" << program_id << "]" << std::endl;

  // создаем консольное ядро приложения
  KonsoleCore core( argc, argv, program_id );

  // создаем файл с PID текущего процесса в темповой директории системы
  const char* env_val = getenv( ENV_TMP_DIR );
  std::string pid_file_full_path;

  if ( env_val == 0 )	{
      std::cerr << "В Системе не выставлена переменная [" << ENV_TMP_DIR << "]" << std::endl;
    } else {
      std::string path_to_pid_files;
      path_to_pid_files.append( env_val );
      path_to_pid_files.append( "/" );
      path_to_pid_files.append( PREFIX_TO_PID_FILES );

      boost::filesystem::create_directories( path_to_pid_files );
      boost::filesystem::path app_name( argv[ 0 ] );

#	ifdef MY_BOOST_LIB_VERSION_EARLIER_1_49
      std::string arg_0( app_name.filename() );
#	endif	

#	ifdef MY_BOOST_LIB_VERSION_IS_1_49
      std::string arg_0( app_name.filename().c_str() );
#	endif

#	ifdef MY_BOOST_LIB_VERSION_GREATER_1_49
      std::string arg_0( app_name.filename().string() );
#	endif

      pid_file_full_path.append( path_to_pid_files );
      pid_file_full_path.append( "/" );

      pid_file_full_path.append( arg_0 );
      pid_file_full_path.append( "." );
      pid_file_full_path.append( program_id );
      pid_file_full_path.append( "." );
      pid_file_full_path.append( "lock" );

      qint64 pid = QCoreApplication::instance()->applicationPid();
      QString pid_str = QString( "%1" ).arg( pid );

      std::ofstream pid_file;
      pid_file.open( pid_file_full_path.c_str() );
      pid_file.write( pid_str.toStdString().c_str(), pid_str.length() );
      pid_file.close();
    }

  // выставляем тип кодека для строковых значений
  QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );

  if ( codec != 0 ){
#if QT_VERSION < 0x050000
      QTextCodec::setCodecForCStrings( codec );
      QTextCodec::setCodecForLocale( codec );
      QTextCodec::setCodecForTr( codec );
#else
      QTextCodec::setCodecForLocale( codec );
#endif
    }

#ifndef WIN32
  setlocale(LC_NUMERIC, "C");
#endif

  core.Initialize();
  core.Run();

  // а в конце "замочим" файл с pid
  boost::filesystem::remove( pid_file_full_path );

  // запускаем основной main-loop приложения
  return 0;/*a.exec();*/
}
//--------------------------------------------------------------------------------------
