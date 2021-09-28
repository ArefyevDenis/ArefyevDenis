
#pragma once

#include "../../common/typedefs.h"
#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{
//-----------------------------------------------------------------------
/**
 * @brief Интерфейс для описания экспортируемых из модуля параметров ВСК
 **/
class IExportedISCParameters
{
public:

    /**
     * @brief Добавить описание параметра ВСК
     *
     * @param InInfo описание параметра
     * @return void
     **/
    virtual void CALL_CONVERSION AddISCParameterInfo( const FTS::BasesTypes::ExportIscParameter* InInfo ) = 0;
	
    /**
     * @brief Очистить данные
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Clear( void ) = 0;
	
};
//-----------------------------------------------------------------------
        }; // end namespace Ifaces{
};	// end namespace FTS
