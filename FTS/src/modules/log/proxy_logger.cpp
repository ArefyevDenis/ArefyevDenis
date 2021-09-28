
#include <assert.h>

#include <QString>
#include <logmanager.h>

#include "proxy_logger.h"

ProxyLogger::ProxyLogger( const Log4Qt::Logger* InLogger ): _Logger( InLogger )
{
	assert( _Logger );
}

ProxyLogger::~ProxyLogger( void )
{
}

void CALL_CONVERSION ProxyLogger::debug( const char* InMessage ) const
{
	_Logger->debug( InMessage );
}

void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, const char* InArg1 ) const
{
	_Logger->debug( InMessage, InArg1 );
}
void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, int InArg1 ) const
{
	_Logger->debug( InMessage, InArg1 );
}
void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, const char* InArg1, const char* InArg2 ) const
{
	_Logger->debug( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, const char* InArg1, int InArg2 ) const
{
	_Logger->debug( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, int InArg1, const char* InArg2 ) const
{
	_Logger->debug( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, int InArg1, int InArg2 ) const
{
	_Logger->debug( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const
{
	_Logger->debug( InMessage, QString( InArg1 ), QString( InArg2 ), QString( InArg3 ) );
}
void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const
{
	_Logger->debug( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const
{
	_Logger->debug( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const
{
	_Logger->debug( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const
{
	_Logger->debug( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const
{
	_Logger->debug( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const
{
	_Logger->debug( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::debug( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const
{
	_Logger->debug( InMessage, InArg1, InArg2, InArg3 );
}
	
	
void CALL_CONVERSION ProxyLogger::error( const char* InMessage ) const
{
	_Logger->error( InMessage );
}

void CALL_CONVERSION ProxyLogger::error( const char* InMessage, const char* InArg1 ) const
{
	_Logger->error( InMessage, InArg1 );
}
void CALL_CONVERSION ProxyLogger::error( const char* InMessage, int InArg1 ) const
{
	_Logger->error( InMessage, InArg1 );
}
void CALL_CONVERSION ProxyLogger::error( const char* InMessage, const char* InArg1, const char* InArg2 ) const
{
	_Logger->error( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::error( const char* InMessage, const char* InArg1, int InArg2 ) const
{
	_Logger->error( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::error( const char* InMessage, int InArg1, const char* InArg2 ) const
{
	_Logger->error( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::error( const char* InMessage, int InArg1, int InArg2 ) const
{
	_Logger->error( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::error( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const
{
	_Logger->error( InMessage, QString( InArg1 ), QString( InArg2 ), QString( InArg3 ) );
}
void CALL_CONVERSION ProxyLogger::error( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const
{
	_Logger->error( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::error( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const
{
	_Logger->error( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::error( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const
{
	_Logger->error( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::error( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const
{
	_Logger->error( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::error( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const
{
	_Logger->error( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::error( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const
{
	_Logger->error( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::error( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const
{
	_Logger->error( InMessage, InArg1, InArg2, InArg3 );
}


void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage ) const
{
	_Logger->fatal( InMessage );
}

void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, const char* InArg1 ) const
{
	_Logger->fatal( InMessage, InArg1 );
}
void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, int InArg1 ) const
{
	_Logger->fatal( InMessage, InArg1 );
}
void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, const char* InArg1, const char* InArg2 ) const
{
	_Logger->fatal( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, const char* InArg1, int InArg2 ) const
{
	_Logger->fatal( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, int InArg1, const char* InArg2 ) const
{
	_Logger->fatal( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, int InArg1, int InArg2 ) const
{
	_Logger->fatal( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const
{
	_Logger->fatal( InMessage, QString( InArg1 ), QString( InArg2 ), QString( InArg3 ) );
}
void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const
{
	_Logger->fatal( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const
{
	_Logger->fatal( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const
{
	_Logger->fatal( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const
{
	_Logger->fatal( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const
{
	_Logger->fatal( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const
{
	_Logger->fatal( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::fatal( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const
{
	_Logger->fatal( InMessage, InArg1, InArg2, InArg3 );
}

void CALL_CONVERSION ProxyLogger::info( const char* InMessage ) const
{
	_Logger->info( InMessage );
}

void CALL_CONVERSION ProxyLogger::info( const char* InMessage, const char* InArg1 ) const
{
	_Logger->info( InMessage, InArg1 );
}
void CALL_CONVERSION ProxyLogger::info( const char* InMessage, int InArg1 ) const
{
	_Logger->info( InMessage, InArg1 );
}
void CALL_CONVERSION ProxyLogger::info( const char* InMessage, const char* InArg1, const char* InArg2 ) const
{
	_Logger->info( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::info( const char* InMessage, const char* InArg1, int InArg2 ) const
{
	_Logger->info( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::info( const char* InMessage, int InArg1, const char* InArg2 ) const
{
	_Logger->info( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::info( const char* InMessage, int InArg1, int InArg2 ) const
{
	_Logger->info( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::info( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const
{
	_Logger->info( InMessage, QString( InArg1 ), QString( InArg2 ), QString( InArg3 ) );
}
void CALL_CONVERSION ProxyLogger::info( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const
{
	_Logger->info( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::info( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const
{
	_Logger->info( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::info( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const
{
	_Logger->info( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::info( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const
{
	_Logger->info( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::info( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const
{
	_Logger->info( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::info( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const
{
	_Logger->info( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::info( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const
{
	_Logger->info( InMessage, InArg1, InArg2, InArg3 );
}

//*****
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage ) const
{
	_Logger->trace( InMessage );
}

void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, const char* InArg1 ) const
{
	_Logger->trace( InMessage, InArg1 );
}
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, int InArg1 ) const
{
	_Logger->trace( InMessage, InArg1 );
}
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, const char* InArg1, const char* InArg2 ) const
{
	_Logger->trace( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, const char* InArg1, int InArg2 ) const
{
	_Logger->trace( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, int InArg1, const char* InArg2 ) const
{
	_Logger->trace( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, int InArg1, int InArg2 ) const
{
	_Logger->trace( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const
{
	_Logger->trace( InMessage, QString( InArg1 ), QString( InArg2 ), QString( InArg3 ) );
}
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const
{
	_Logger->trace( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const
{
	_Logger->trace( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const
{
	_Logger->trace( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const
{
	_Logger->trace( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const
{
	_Logger->trace( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const
{
	_Logger->trace( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::trace( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const
{
	_Logger->trace( InMessage, InArg1, InArg2, InArg3 );
}

void CALL_CONVERSION ProxyLogger::warn( const char* InMessage ) const
{
	_Logger->warn( InMessage );
}

void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, const char* InArg1 ) const
{
	_Logger->warn( InMessage, InArg1 );
}
void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, int InArg1 ) const
{
	_Logger->warn( InMessage, InArg1 );
}
void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, const char* InArg1, const char* InArg2 ) const
{
	_Logger->warn( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, const char* InArg1, int InArg2 ) const
{
	_Logger->warn( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, int InArg1, const char* InArg2 ) const
{
	_Logger->warn( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, int InArg1, int InArg2 ) const
{
	_Logger->warn( InMessage, InArg1, InArg2 );
}
void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, const char* InArg1, const char* InArg2, const char* InArg3 ) const
{
	_Logger->warn( InMessage, QString( InArg1 ), QString( InArg2 ), QString( InArg3 ) );
}
void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, const char* InArg1, const char* InArg2, int InArg3 ) const
{
	_Logger->warn( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, const char* InArg1, int InArg2, const char* InArg3 ) const
{
	_Logger->warn( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, const char* InArg1, int InArg2, int InArg3 ) const
{
	_Logger->warn( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, int InArg1, const char* InArg2, const char* InArg3 ) const
{
	_Logger->warn( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, int InArg1, const char* InArg2, int InArg3 ) const
{
	_Logger->warn( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, int InArg1, int InArg2, const char* InArg3 ) const
{
	_Logger->warn( InMessage, InArg1, InArg2, InArg3 );
}
void CALL_CONVERSION ProxyLogger::warn( const char* InMessage, int InArg1, int InArg2, int InArg3 ) const
{
	_Logger->warn( InMessage, InArg1, InArg2, InArg3 );
}
