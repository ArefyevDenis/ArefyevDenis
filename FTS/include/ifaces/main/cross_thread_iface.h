
#pragma once 

#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{

class ICrossThread
{
public:

    /**
     * @brief Зупустить поток
     *
     * @param  ...
     * @return bool
     **/
    virtual bool CALL_CONVERSION Start( void ) = 0;
	
    /**
     * @brief Остановить поток
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Stop( void ) = 0;
	
    /**
     * @brief Приостановить поток на величину в секундах
     *
     * @param InSeconds величина паузы в секундах
     * @return void
     **/
    virtual void CALL_CONVERSION SleepSec( const unsigned long InSeconds ) = 0;
	
    /**
     * @brief Приостановить поток на величину в секундах
     *
     * @param InMilliSeconds величина паузы в миллисекундах
     * @return void
     **/
    virtual void CALL_CONVERSION SleepMs( const unsigned long InMilliSeconds ) = 0;
	
    /**
     * @brief Приостановить поток на величину в секундах
     *
     * @param InMicroSeconds величина паузы в микросекундах
     * @return void
     **/
    virtual void CALL_CONVERSION SleepMcs( const unsigned long InMicroSeconds ) = 0;
	
    /**
     * @brief Получить признак возможности остановки
     *
     * @param  ...
     * @return bool
     **/
    virtual bool CALL_CONVERSION WannaStop( void ) = 0;
	
    /**
     * @brief Получить признак, остановлен ли поток
     *
     * @param  ...
     * @return bool
     **/
    virtual bool CALL_CONVERSION IsStoped( void ) = 0;
	
};
	};
};
