
#pragma once


#include <QtCore/QString>

#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{
		class IWidgetsGetter;
	
//-------------------------------------------------------------------
/**
 * @brief Интерфейс манипулирования виджетами
 **/
class IWidgetsManipulator
{
public:
	/**
	 * @brief Зарегистрировать объект для выдачи виджетов по запросу
	 * \remarks Применять только в методе Start модуля!
         * @param InWidgetsGetter объект для получения информации о виджетах в Системе
	 * @return void
	 **/
        virtual void CALL_CONVERSION RegisterWidgetsGetter( FTS::Ifaces::IWidgetsGetter* InWidgetsGetter ) = 0;
	
};
//-------------------------------------------------------------------
	}
}
