
#pragma once

#include <QAction>
#include "../../../include/common/config-win32.h"

namespace FTS{
        namespace Ifaces{
	
//--------------------------------------------------------
/**
 * @brief Интерфейс, предоставляющий сервисные функции для работы с Действиями
 **/
class IActionsService
{
public:
	/**
	 * @brief Добавить действие 
         * @param InActionId идентификатор действия
	 * @param InAction действие
	 * @return bool - результат добавления
	 **/
        virtual bool CALL_CONVERSION AddAction( const char* InActionId, const QAction* InAction ) = 0;
	
	/**
	 * @brief Проверить наличие Действия для указанных условий
         * @param InModuleId идентификатор модуля
	 * @param InActionId идентификатор Действия
	 * @return bool - признак наличия
	 **/
        virtual bool CALL_CONVERSION ActionInPresence( const char* InModuleId, const char* InActionId ) const = 0;
	
	/**
	 * @brief Получить количество действий, предоставляемых модулем
         * @param InModuleId идентификатор модуля
	 * @return unsigned int - количество (от 0 до N)
	 **/
	virtual unsigned int CALL_CONVERSION	GetCountActions( const char* InModuleId ) const = 0;
	
	/**
	 * @brief Получить Действие по индексу
	 *
	 * @param InModuleId идентификатор модуля, реализующий Действие
	 * @param InIndex индекс действия
	 * @return const QAction* - результат (0 при отсутствии Действия)
	 **/
	virtual const QAction* CALL_CONVERSION		GetActionByIndex( const char* InModuleId, unsigned int InIndex ) const = 0;
	
	/**
	 * @brief Получить Действие по его идентификатору
	 *
	 * @param InModuleId идентификатор модуля
	 * @param InActionId идентификатор Действия
	 * @return const QAction* - результат (0 при отсутствии Действия)
	 **/
	virtual const QAction* CALL_CONVERSION		GetActionById( const char* InModuleId, const char* InActionId ) const = 0;
	
};
//--------------------------------------------------------

        }; // end namespace Ifaces
}; // end namespace FTS
