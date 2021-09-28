#pragma once

#include "../../common/typedefs.h"
#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{
/**
 * @brief Интерфейс для описания используемых библиотек и их версий в проекте
 **/
class IUsageLibraryInfoDescriber
{
public:

    /**
     * @brief Добавить описание используемой библиотеки в описатель
     *
     * @param InInfo описание библиотеки
     * @return void
     **/
    virtual void CALL_CONVERSION AddLibraryInfo( FTS::BasesTypes::LibraryInfo* InInfo ) = 0;
	
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
