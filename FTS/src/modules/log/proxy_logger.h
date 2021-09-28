
#pragma once

#include "../../../include/ifaces/main/logger_iface.h"

namespace Log4Qt{
	class Logger;
};

/**
 * @brief Промежуточный объект протоколирования
 **/
class ProxyLogger: public FTS::Ifaces::ILogger
{
public:
    ProxyLogger( const Log4Qt::Logger* InLogger );
    virtual ~ProxyLogger( void );
	
//--- ILogger
public:
	void CALL_CONVERSION debug( const char* InMessage ) const;
	void CALL_CONVERSION debug( const char* InMessage, const char* InArg1 ) const;
	void CALL_CONVERSION debug( const char* InMessage, int InArg1 ) const;
	void CALL_CONVERSION debug( const char* InMessage, const char* InArg1, const char* InArg2 ) const;
	void CALL_CONVERSION debug( const char* InMessage, const char* InArg1, int InArg2 ) const;
	void CALL_CONVERSION debug( const char* InMessage, int InArg1, const char* InArg2 ) const;
	void CALL_CONVERSION debug( const char* InMessage, int InArg1, int InArg2 ) const;
	void CALL_CONVERSION debug( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION debug( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const;
	void CALL_CONVERSION debug( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION debug( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const;
	void CALL_CONVERSION debug( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION debug( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const;
	void CALL_CONVERSION debug( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION debug( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const;
	
	void CALL_CONVERSION error( const char* InMessage ) const;
	void CALL_CONVERSION error( const char* InMessage, const char* InArg1 ) const;
	void CALL_CONVERSION error( const char* InMessage, int InArg1 ) const;
	void CALL_CONVERSION error( const char* InMessage, const char* InArg1, const char* InArg2 ) const;
	void CALL_CONVERSION error( const char* InMessage, const char* InArg1, int InArg2 ) const;
	void CALL_CONVERSION error( const char* InMessage, int InArg1, const char* InArg2 ) const;
	void CALL_CONVERSION error( const char* InMessage, int InArg1, int InArg2 ) const; 
	void CALL_CONVERSION error( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION error( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const;
	void CALL_CONVERSION error( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION error( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const;
	void CALL_CONVERSION error( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION error( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const; 
	void CALL_CONVERSION error( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION error( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const;

	void CALL_CONVERSION fatal( const char* InMessage ) const;
	void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1 ) const; 
	void CALL_CONVERSION fatal( const char* InMessage, int InArg1 ) const; 
	void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1, const char* InArg2 ) const;
	void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1, int InArg2 ) const; 
	void CALL_CONVERSION fatal( const char* InMessage, int InArg1, const char* InArg2 ) const;
	void CALL_CONVERSION fatal( const char* InMessage, int InArg1, int InArg2 ) const; 
	void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const;
	void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const; 
	void CALL_CONVERSION fatal( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const;
	void CALL_CONVERSION fatal( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION fatal( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const;
	void CALL_CONVERSION fatal( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION fatal( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const;

	void CALL_CONVERSION info( const char* InMessage ) const;
	void CALL_CONVERSION info( const char* InMessage, const char* InArg1 ) const;
	void CALL_CONVERSION info( const char* InMessage, int InArg1 ) const;
	void CALL_CONVERSION info( const char* InMessage, const char* InArg1, const char* InArg2 ) const;
	void CALL_CONVERSION info( const char* InMessage, const char* InArg1, int InArg2 ) const;
	void CALL_CONVERSION info( const char* InMessage, int InArg1, const char* InArg2 ) const;
	void CALL_CONVERSION info( const char* InMessage, int InArg1, int InArg2 ) const; 
	void CALL_CONVERSION info( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION info( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const;
	void CALL_CONVERSION info( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION info( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const;
	void CALL_CONVERSION info( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION info( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const;
	void CALL_CONVERSION info( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION info( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const;

	void CALL_CONVERSION trace( const char* InMessage ) const;
	void CALL_CONVERSION trace( const char* InMessage, const char* InArg1 ) const;
	void CALL_CONVERSION trace( const char* InMessage, int InArg1 ) const;
	void CALL_CONVERSION trace( const char* InMessage, const char* InArg1, const char* InArg2 ) const; 
	void CALL_CONVERSION trace( const char* InMessage, const char* InArg1, int InArg2 ) const;
	void CALL_CONVERSION trace( const char* InMessage, int InArg1, const char* InArg2 ) const;
	void CALL_CONVERSION trace( const char* InMessage, int InArg1, int InArg2 ) const;
	void CALL_CONVERSION trace( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION trace( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const;
	void CALL_CONVERSION trace( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION trace( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const;
	void CALL_CONVERSION trace( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION trace( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const;
	void CALL_CONVERSION trace( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION trace( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const;

	void CALL_CONVERSION warn( const char* InMessage ) const;
	void CALL_CONVERSION warn( const char* InMessage, const char* InArg1 ) const;
	void CALL_CONVERSION warn( const char* InMessage, int InArg1 ) const;
	void CALL_CONVERSION warn( const char* InMessage, const char* InArg1, const char* InArg2 ) const;
	void CALL_CONVERSION warn( const char* InMessage, const char* InArg1, int InArg2 ) const;
	void CALL_CONVERSION warn( const char* InMessage, int InArg1, const char* InArg2 ) const;
	void CALL_CONVERSION warn( const char* InMessage, int InArg1, int InArg2 ) const;
	void CALL_CONVERSION warn( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION warn( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const;
	void CALL_CONVERSION warn( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION warn( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const;
	void CALL_CONVERSION warn( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION warn( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const;
	void CALL_CONVERSION warn( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const;
	void CALL_CONVERSION warn( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const;
	
private:
	/**
	 * @brief Объект протоколирования
	 **/
	const Log4Qt::Logger*			_Logger;
	
};
