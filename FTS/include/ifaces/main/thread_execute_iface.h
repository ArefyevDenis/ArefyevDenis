#pragma once

#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{

//-----------------------------------------------------------------------------
/**
 * @brief Интерфейс для выполнения потока
 **/
class IThreadExecute
{
public:
	/**
	 * @brief Исполняемый метод потока
	 *
	 * @param  ...
	 * @return void
	 **/
	virtual void CALL_CONVERSION	Execute( void ) = 0;
	
};
//-----------------------------------------------------------------------------
	};
};
