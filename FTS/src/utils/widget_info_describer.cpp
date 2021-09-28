
#include <assert.h>

#include "widget_info_describer.h"

namespace FTS{
	namespace Utils{
//----------------------------------------------------------------------
WidgetInfoDescriber::WidgetInfoDescriber( void )
{

}
//----------------------------------------------------------------------
WidgetInfoDescriber::~WidgetInfoDescriber( void )
{
	Clear();
}
//----------------------------------------------------------------------
void CALL_CONVERSION WidgetInfoDescriber::AddWidgetInfo( FTS::BasesTypes::WidgetInfo* InInfo )
{
	assert( InInfo );
    FTS::Containers::WidgetInfoCont::push_back( *InInfo );
}
//----------------------------------------------------------------------	
void CALL_CONVERSION WidgetInfoDescriber::Clear( void )
{
    FTS::Containers::WidgetInfoCont::clear();
}
//----------------------------------------------------------------------
	};
};
