
#pragma once

#include <map>
#include <list>
#include <string>
 
#include "../../../include/ifaces/main/module_iface.h"
#include "../../../include/ifaces/modules/log/log_iface.h"

namespace Log4Qt{
  class TTCCLayout;
  class ConsoleAppender;
  class FileAppender;
  class SignalAppender;
  class Logger;
};
namespace FTS{
        namespace Ifaces{
                class ICoreMainIfaces;
	}
}

class ProxyLogger;
class SignalsByNewLogGrabber;

//==============================================================================================================//
/**
 * @brief Тип данных - словарь объектов протоколирования
 * \remarks
 * Ключ - наименование объекта (подсистемы по сути)
 * Значение - объект протоколирования
 **/
typedef std::map< std::string, Log4Qt::Logger* > LoggersMap;

//==============================================================================================================//
/**
 * @brief Тип данных - контейнер с объектами-переходниками объектов протоколирования
 **/
typedef std::map< std::string, ProxyLogger* > ProxyLoggersCont;
typedef ProxyLoggersCont::iterator ProxyLoggersContIter;

//==============================================================================================================//
/**
 * @brief Модуль, реализующий подсистему протоколирования
 **/
class LogSystem: public FTS::Ifaces::IModule, public ILog
{
public:
	LogSystem();
	virtual ~LogSystem();
	
//--- FTS::Ifaces::IModule
public:
	/**
	 * @brief Инициализация модуля 
	 *
	 * @param ICoreMainIfaces ядро главных интерфейсов
	 * @return void
	 **/
        void CALL_CONVERSION		Initialize( FTS::Ifaces::ICoreMainIfaces* InCoreMainIfaces );
	
	/**
	 * @brief Запуск работы модуля
	 *
	 * @param  ...
	 * @return void
	 **/
	void CALL_CONVERSION		Start( void );
	
	/**
	 * @brief Стоп работы модуля
	 *
	 * @param  ...
	 * @return void
	 **/
	void CALL_CONVERSION		Stop( void );
	
	/**
	 * @brief Получить интерфейс в соответствии с указанными параметрами
	 *
	 * @param InIfaceId идентификатор запрашиваемого интерфейса
	 * @param InIfaceVersion версия запрашиваемого интерфейса
	 * @return :Interfaces::IExportInterface*
	 **/
        FTS::Ifaces::IExportIface* CALL_CONVERSION GetExportedIface( const char* InIfaceId, const unsigned int InIfaceVersion );
	
	/**
	 * @brief Удаление объекта
	 *
	 * @param  ...
	 * @return void
	 **/
	void CALL_CONVERSION		Release( void ){ delete this; };
	
//--- IExportIface
public:
	/**
	 * @brief Получить версию интерфейса
	 *
	 * @param  ...
	 * @return unsigned int
	 **/
	unsigned int CALL_CONVERSION		GetVersion( void );
	
	/**
	 * @brief Получить идентификатор интерфейса
	 *
	 * @param  ...
	 * @return const char*
	 **/
	const char* CALL_CONVERSION			GetId( void );
	
//--- ILog
public:
	/**
	 * @brief Получить объект протоколирования для указанной подсистемы
	 *
	 * @param InLoggerName наименование подсситемы
	 * @return :Logger*
	 **/
        const FTS::Ifaces::ILogger*  CALL_CONVERSION		GetLogger( const char* InSystemName );
	
private: 
	/**
	 * @brief Получить имя файла протоколирования
	 *
	 * @param  ...
	 * @return QString
	 **/
	QString						GetProtocolFileName( void );

private:

    FTS::Ifaces::ICoreMainIfaces* m_pCoreMainIfaces;            //Фабрика интерфейсов ядра
    Log4Qt::TTCCLayout* m_pTTCCLayout;                          //Объект форматирования сообщений
    Log4Qt::ConsoleAppender* m_pConsoleAppender;                //Объект вывода сообщений в консоль
    Log4Qt::FileAppender* m_pFileAppender;                      //Объект вывода сообщений в файл
    Log4Qt::SignalAppender* m_pSignalAppender;                  //Объект уведомления о новых сообщениях в логе при помощи сигналов Qt
    SignalsByNewLogGrabber* m_pSignalsByNewLogGrabber;          //Объект для перехвата сигналов о генерации новых сообщений в протоколе работы приложения
    Log4Qt::Logger* m_pLogger;                                  //Объект протоколирования для собственных нужд модуля
    LoggersMap m_AllLoggers;                                    //Все объекты протоколирования
    ProxyLoggersCont m_AllProxies;                              //Все объекты-переходники
};
//-----------------------------------------------------------------------
