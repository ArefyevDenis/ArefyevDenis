
#pragma once

#include <QtGlobal>

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#   include <QWidget>
#else
#   include <QtWidgets/QWidget>
#endif

#include "../../common/config-win32.h"

#include "../modules/gui/event_notifier_iface.h"

//-----------------------------------------------------------------------------
/**
 * @brief Интерфейс, который необходимо реализовать каждому экспортируемому из модуля виджету
 **/
class IBuildGui: public IEventNotifier
{
public:
	/**
	 * @brief Построить интерфейс 
	 * \remarks При вызове данного метода виджета Ядро гарантирует, что у виджета будет выставлен корректный parent!
	 *
	 * @param  ...
	 * @return void
	 **/
	virtual void CALL_CONVERSION			BuildGui( void ) = 0;
};
//-----------------------------------------------------------------------------
/**
 * @brief Абстрактный класс экспортируемого из модуля виджета
 **/
class ExportedWidget: public QWidget,
						public IBuildGui
{
public:
	ExportedWidget( QWidget* InParent = 0 ): QWidget( InParent )
	{
	}
	
    virtual ~ExportedWidget(){;};
};
//-----------------------------------------------------------------------------
