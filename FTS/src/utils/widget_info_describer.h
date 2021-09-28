
#pragma once

#pragma once 

#include <vector>

#include "../../include/common/typedefs.h"
#include "../../include/ifaces/main/widget_info_describer_iface.h"

//----------------------------------------------------------------------
namespace FTS{
	namespace Utils{
//----------------------------------------------------------------------
class WidgetInfoDescriber: 
        public FTS::Containers::WidgetInfoCont,
        public FTS::Ifaces::IWidgetInfoDescriber
{
public:
	WidgetInfoDescriber( void );
	~WidgetInfoDescriber( void );
	
//--- FTS::Ifaces::IShortStringInfoDescriber
public:
        /**
	 * @brief Добавить описание виджета в описатель
	 *
	 * @param InInfo описание
	 * @return void
	 **/
        void CALL_CONVERSION AddWidgetInfo( FTS::BasesTypes::WidgetInfo* InInfo );
	
	/**
	 * @brief Очистить данные в описателе
	 *
	 * @param  ...
	 * @return void
	 **/
        void CALL_CONVERSION Clear( void );
	
};
//----------------------------------------------------------------------
	};
};
