#pragma once

#include "../../common/typedefs.h"
#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{
/**
 * @brief Интерфейс для описания экспортируемых интерфейсов из библиотеки
 **/
class IExportInterfaceInfoDescriber
{
public:

    /**
     * @brief Добавить описание экспортируемого интерфейса в описатель
     *
     * @param InInfo описание библиотеки
     * @return void
     **/
    virtual void CALL_CONVERSION AddInterfaceInfo( FTS::BasesTypes::ExportInterfaceInfo* InInfo ) = 0;
	
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
