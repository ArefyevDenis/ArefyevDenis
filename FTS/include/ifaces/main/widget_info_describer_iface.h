#pragma once

#include "../../common/typedefs.h"
#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{
//-----------------------------------------------------------------------------
/**
 * @brief Интерфейс для описания экспортируемых виджетов из модуля
 **/
class IWidgetInfoDescriber
{
public:

    /**
     * @brief Добавить описание виджета в описатель
     *
     * @param InInfo описание
     * @return void
     **/
    virtual void CALL_CONVERSION AddWidgetInfo( FTS::BasesTypes::WidgetInfo* InInfo ) = 0;
	
    /**
     * @brief Очистить данные в описателе
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Clear( void ) = 0;
	
};
//-----------------------------------------------------------------------------
        }; // end namespace Ifaces{
};	// end namespace FTS
