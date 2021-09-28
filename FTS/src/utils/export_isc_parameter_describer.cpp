
#include <assert.h>

#include "export_isc_parameter_describer.h"

namespace FTS   {
	namespace Utils{
		
	
ExportISCParameterDescriber::ExportISCParameterDescriber( void )
{

}

ExportISCParameterDescriber::~ExportISCParameterDescriber( void )
{
	Clear();
}

void CALL_CONVERSION		ExportISCParameterDescriber::AddISCParameterInfo( const FTS::BasesTypes::ExportIscParameter* InInfo )
{
	assert( InInfo );
	ExportIscParameterCont::push_back( *InInfo );
}

void CALL_CONVERSION		ExportISCParameterDescriber::Clear( void )
{
	ExportIscParameterCont::clear();
}

	};
};
