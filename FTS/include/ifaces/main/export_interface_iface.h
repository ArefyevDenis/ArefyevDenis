
#pragma once

#include "../../common/config-win32.h"

//-------------------------------------------------------------------------
namespace FTS{
        namespace Ifaces{
/**
 * @brief Чисто формальный класс экспортируемого из модуля интерфейса
 **/
class IExportIface
{
public:

    /**
     * @brief Получить версию интерфейса
     *
     * @param  ...
     * @return unsigned int
     **/
    virtual unsigned int CALL_CONVERSION GetVersion( void ) = 0;
	
    /**
     * @brief Получить идентификатор интерфейса
     *
     * @param  ...
     * @return const char*
     **/
    virtual const char* CALL_CONVERSION	GetId( void ) = 0;
	
};
//-------------------------------------------------------------------------
	};
};
