#pragma once 

#include "../../common/config-win32.h"
#include "exported_widget_iface.h"

// class QWidget;

namespace FTS{
	namespace Ifaces{
		
//-----------------------------------------------------------------------
/**
 * @brief Интерфейс получения виджетов из модуля
 **/
class IWidgetsGetter
{
public:
	/**
	 * @brief Получить виджет по его уникальному идентификатору
	 *
	 * @param InId идентификатор виджета 
	 * \remarks Каждый модуль в своем описательном интерфейсе формирует 
	 * перечень виджетов, которые сам реализует и которые впоследствии у  него запрашиваются
	 * @return ExportedWidget*
	 **/
	virtual ExportedWidget* CALL_CONVERSION		GetWidgetById( const char* InId ) const = 0;
	
};
//-----------------------------------------------------------------------
	};	// end namespace Ifaces	
};	// end namespace FTS
