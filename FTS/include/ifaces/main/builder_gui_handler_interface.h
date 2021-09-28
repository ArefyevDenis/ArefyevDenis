#pragma once

class IGuiWidgetsManipulator;

namespace FTS{
        namespace Ifaces{
//-----------------------------------------------------------------------------
/**
 * @brief ВнутриЯдерный интерфейс построения GUI приложения
 **/
class IBuilderGuiHandler
{
public:
	/**
	 * @brief Получить интерфейс модуля-построителя интерфейса оператора
	 *
	 * @param  ...
	 * @return IGuiWidgetsManipulator*
	 **/
	virtual IGuiWidgetsManipulator*		GetGuiWidgetsManipulator( void ) = 0;
	
	/**
	 * @brief Построить интерфейс пользователя
	 *
	 * @param  ...
	 * @return void
	 **/
	virtual void 						BuildGui( void ) = 0;
};
//-----------------------------------------------------------------------------
	};
};
