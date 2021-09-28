#pragma once

#include "../../common/typedefs.h"
#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{
/**
 * @brief Интерфейс для описания экспортируемых данных типа "ShortString" из библиотеки
 **/
class IShortStringInfoDescriber
{
public:

    /**
     * @brief Добавить описание
     *
     * @param InInfo описание
     * @return void
     **/
    virtual void CALL_CONVERSION AddInfo( FTS::BasesTypes::ShortString* InInfo ) = 0;
	
    /**
     * @brief Очистить данные в описателе
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Clear( void ) = 0;
	
};
        }; // end namespace Ifaces{
};	// end namespace FTS
