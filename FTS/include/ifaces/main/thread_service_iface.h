
#pragma once

#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{

class ICrossThread;
class IThreadExecute;
	
/**
 * @brief Интерфейс сервисного взаимодействия с потоками
 **/
class IThreadService
{
public:
	/**
	 * @brief Получить потоковый объект
	 * @param InExecuteObject объект, в котором объявлен потоковый метод для исполнения
	 * @return ICrossThread*
	 **/
        virtual ICrossThread* CALL_CONVERSION GetThread( IThreadExecute* InExecuteObject ) const = 0;
	
	/**
         * @brief Удалить поток
	 * @param InThread потокоый объект
	 * @return void
	 **/
        virtual void CALL_CONVERSION DeleteThread( ICrossThread* InThread ) const = 0;
	
};

	}
};
