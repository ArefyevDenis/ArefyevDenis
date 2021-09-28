#pragma once

#include "../../../ifaces/main/export_interface_iface.h"
#include "../../../common/config-win32.h"

#define GUI_BUILDER_IFACE_ID 		"gui_builder_iface"
#define GUI_BUILDER_IFACE_VERSION	1

class QWidget;

//----------------------------------------------------------------------
/**
 * @brief Интерфейс построения графического интерфейса пользователя
 **/
class IGuiBuilderIface: public FTS::Ifaces::IExportInterface
{
public:
	/**
	 * @brief Инициализация построителя интерфейса 
	 *
	 * @param InScreenCount количество экранов
	 * @return void
	 **/
	virtual void CALL_CONVERSION InitializeGuiBuilder( unsigned int InScreenCount ) = 0;
	
	/**
	 * @brief Получить виджет для отображения на указанном экране 
	 *
	 * @param InScreenIndex индекс экрана
	 * \remarks  Индекс экрана нумеруется начиная с 0
	 * @param InParent "родитель" для создаваемого виджета
	 * 
	 * @return QWidget*
	 **/
	virtual QWidget* CALL_CONVERSION GetWidgetForScreen( unsigned int InScreenIndex, QWidget* InParent ) = 0;
	
	/**
	 * @brief Построить графический интерфейс пользователя
	 * \remarks Ядро уведомляет модуль, что все модули проинициализированы и запущены, что дает гарантию
	 * о том, что все виджеты уже созданы и можно окончательно сформировать ГИП
	 *
	 * @param  ...
	 * @return void
	 **/
	virtual void CALL_CONVERSION	BuildGui( void ) = 0;
	
};
//----------------------------------------------------------------------
