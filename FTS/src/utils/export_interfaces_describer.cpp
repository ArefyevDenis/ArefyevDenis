
#include <assert.h>

#include "export_interfaces_describer.h"

namespace FTS{
	namespace Utils{
		
	
ExportInterfacesDescriber::ExportInterfacesDescriber( void )
{

}

ExportInterfacesDescriber::~ExportInterfacesDescriber( void )
{
	Clear();
}

void CALL_CONVERSION		ExportInterfacesDescriber::AddInterfaceInfo( FTS::BasesTypes::ExportInterfaceInfo* InInfo )
{
	assert( InInfo );
	ExportInterfaceInfoCont::push_back( *InInfo );
}
	
void CALL_CONVERSION		ExportInterfacesDescriber::Clear( void )
{
	ExportInterfaceInfoCont::clear();
}

	};
};
