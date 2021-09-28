
#pragma once

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/xtime.hpp>

namespace FTS{
        namespace Ifaces{
		class IThreadExecute;
	}
}

#include "../../include/ifaces/main/cross_thread_iface.h"

//--------------------------------------------------------------
class CrossThread: public FTS::Ifaces::ICrossThread
{
public:
    explicit CrossThread( FTS::Ifaces::IThreadExecute* InExecuteIface );
    ~CrossThread( void );

//--- ICrossThread
public:
	/**
	 * @brief Зупустить поток
	 *
	 * @param  ...
	 * @return bool
	 **/
	bool CALL_CONVERSION 		Start( void ); 
	
	/**
	 * @brief Остановить поток
	 *
	 * @param  ...
	 * @return void
	 **/
	void CALL_CONVERSION 		Stop( void );
	
	/**
	 * @brief Приостановить поток на величину в секундах
	 *
	 * @param InSeconds величина паузы в секундах
	 * @return void
	 **/
	void CALL_CONVERSION 		SleepSec( const unsigned long InSeconds );
	
	/**
	 * @brief Приостановить поток на величину в секундах
	 *
	 * @param InMilliSeconds величина паузы в миллисекундах
	 * @return void
	 **/
	void CALL_CONVERSION 		SleepMs( const unsigned long InMilliSeconds );
	
	/**
	 * @brief Приостановить поток на величину в секундах
	 *
	 * @param InMicroSeconds величина паузы в микросекундах
	 * @return void
	 **/
	void CALL_CONVERSION		SleepMcs( const unsigned long InMicroSeconds );
	
	/**
	 * @brief Получить признак возможности остановки
	 *
	 * @param  ...
	 * @return bool
	 **/
	bool CALL_CONVERSION 		WannaStop( void );
	
	/**
	 * @brief Получить признак, остановлен ли поток
	 *
	 * @param  ...
	 * @return bool
	 **/
	bool CALL_CONVERSION 		IsStoped( void );
	
private:
	void 						DoWork( void );
	
private:
        FTS::Ifaces::IThreadExecute* _Runable;
        volatile bool _StopReqested;
        boost::shared_ptr< boost::thread > _Thread;
        boost::mutex _Mutex;
};
//--------------------------------------------------------------
