
#pragma once

#include "../../../ifaces/main/export_interface_iface.h"
#include "../../../common/config-win32.h"
#include "../../../common/typedefs.h"

#define GUI_WIDGETS_MANIPULATOR_IFACE_ID 		"gui_widgets_manipulator_iface"
#define GUI_WIDGETS_MANIPULATOR_IFACE_VERSION           1
	
namespace FTS{
        namespace Ifaces{
		class IWidgetsGetter;
	}
}
	
//-------------------------------------------------------------------
/**
 * @brief Интерфейс манипулирования виджетами
 **/
class IGuiWidgetsManipulator: public FTS::Ifaces::IExportIface
{
public:
    /**
     * @brief Добавить информацию об экспортируемых из модуля виджетах
     * \remarks Данные необходимо скопировать, поскольку передается указатель на
     * временный объект, дабы не перегружать стек передачей большого объема данных!
     *
     * @param InWidgetInfoCont контейнер с описательной информацией о виджетах
     * @param InModuleId идентификатор модуля
     * @return void
     **/
    virtual void CALL_CONVERSION AddWidgetsInfo( const FTS::Containers::WidgetInfoCont* InWidgetInfoCont, const char* InModuleId ) = 0;
	
    /**
     * @brief Зарегистрировать объект для выдачи виджетов по запросу
     *
     * @param InWidgetsGetter объект для получения информации о виджетах в Системе
     * @param InModuleId идентификатор модуля
     * @return void
     **/
    virtual void CALL_CONVERSION RegisterWidgetsGetter( FTS::Ifaces::IWidgetsGetter* InWidgetsGetter, const char* InModuleId ) = 0;
	
};
//-------------------------------------------------------------------
