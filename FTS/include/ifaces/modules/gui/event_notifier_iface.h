
#pragma once

#include "../../../common/config-win32.h"

class QEvent;

//-----------------------------------------------------------------------------
/**
 * @brief Интерфейс передачи сообщений типа "событие"
 **/
class IEventNotifier
{
public:
	/**
	 * @brief Обработать "событие" от основного виджета
	 *
	 * @param InEvent ...
	 * @return void
	 **/
	virtual void CALL_CONVERSION			ProcessEventBaseWidget( QEvent* InEvent ) = 0;
};
//-----------------------------------------------------------------------------