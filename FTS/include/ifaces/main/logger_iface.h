
#pragma once 

#pragma pack( push, 4 )

#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{
/**
 * @brief Интерфейс протоколирования, предоставляемый модулям
 **/
class ILogger
{
public:
	virtual void CALL_CONVERSION debug( const char* InMessage ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, const char* InArg1 ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, int InArg1 ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, const char* InArg1, const char* InArg2 ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, const char* InArg1, int InArg2 ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, int InArg1, const char* InArg2 ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, int InArg1, int InArg2 ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION debug( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const = 0;
	
	virtual void CALL_CONVERSION error( const char* InMessage ) const = 0;
	virtual void CALL_CONVERSION error( const char* InMessage, const char* InArg1 ) const = 0;
	virtual void CALL_CONVERSION error( const char* InMessage, int InArg1 ) const = 0;
	virtual void CALL_CONVERSION error( const char* InMessage, const char* InArg1, const char* InArg2 ) const = 0;
	virtual void CALL_CONVERSION error( const char* InMessage, const char* InArg1, int InArg2 ) const = 0;
	virtual void CALL_CONVERSION error( const char* InMessage, int InArg1, const char* InArg2 ) const = 0;
	virtual void CALL_CONVERSION error( const char* InMessage, int InArg1, int InArg2 ) const = 0; 
	virtual void CALL_CONVERSION error( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION error( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION error( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION error( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION error( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION error( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const = 0; 
	virtual void CALL_CONVERSION error( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION error( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const = 0;

	virtual void CALL_CONVERSION fatal( const char* InMessage ) const = 0;
	virtual void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1 ) const = 0; 
	virtual void CALL_CONVERSION fatal( const char* InMessage, int InArg1 ) const = 0; 
	virtual void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1, const char* InArg2 ) const = 0;
	virtual void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1, int InArg2 ) const = 0; 
	virtual void CALL_CONVERSION fatal( const char* InMessage, int InArg1, const char* InArg2 ) const = 0;
	virtual void CALL_CONVERSION fatal( const char* InMessage, int InArg1, int InArg2 ) const = 0; 
	virtual void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const = 0; 
	virtual void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION fatal( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION fatal( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION fatal( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION fatal( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const = 0;

	virtual void CALL_CONVERSION info( const char* InMessage ) const = 0;
	virtual void CALL_CONVERSION info( const char* InMessage, const char* InArg1 ) const = 0;
	virtual void CALL_CONVERSION info( const char* InMessage, int InArg1 ) const = 0;
	virtual void CALL_CONVERSION info( const char* InMessage, const char* InArg1, const char* InArg2 ) const = 0;
	virtual void CALL_CONVERSION info( const char* InMessage, const char* InArg1, int InArg2 ) const = 0;
	virtual void CALL_CONVERSION info( const char* InMessage, int InArg1, const char* InArg2 ) const = 0;
	virtual void CALL_CONVERSION info( const char* InMessage, int InArg1, int InArg2 ) const = 0; 
	virtual void CALL_CONVERSION info( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION info( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION info( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION info( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION info( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION info( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION info( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION info( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const = 0;

	virtual void CALL_CONVERSION trace( const char* InMessage ) const = 0;
	virtual void CALL_CONVERSION trace( const char* InMessage, const char* InArg1 ) const = 0;
	virtual void CALL_CONVERSION trace( const char* InMessage, int InArg1 ) const = 0;
	virtual void CALL_CONVERSION trace( const char* InMessage, const char* InArg1, const char* InArg2 ) const = 0; 
	virtual void CALL_CONVERSION trace( const char* InMessage, const char* InArg1, int InArg2 ) const = 0;
	virtual void CALL_CONVERSION trace( const char* InMessage, int InArg1, const char* InArg2 ) const = 0;
	virtual void CALL_CONVERSION trace( const char* InMessage, int InArg1, int InArg2 ) const = 0;
	virtual void CALL_CONVERSION trace( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION trace( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION trace( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION trace( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION trace( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION trace( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION trace( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION trace( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const = 0;

	virtual void CALL_CONVERSION warn( const char* InMessage ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, const char* InArg1 ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, int InArg1 ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, const char* InArg1, const char* InArg2 ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, const char* InArg1, int InArg2 ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, int InArg1, const char* InArg2 ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, int InArg1, int InArg2 ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const = 0;
	virtual void CALL_CONVERSION warn( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const = 0;
	
};

	};
};

#pragma pack( pop )
