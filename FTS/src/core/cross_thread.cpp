
#include <assert.h>
#include <boost/version.hpp>

#include "../../include/ifaces/main/thread_execute_iface.h"

#if defined(__USE_ISOC11) || BOOST_VERSION >= 105600
#	include <time.h>
#endif 

#include "cross_thread.h"

//--------------------------------------------------------------
CrossThread::CrossThread( FTS::Ifaces::IThreadExecute* InExecuteIface ):
		_Runable( InExecuteIface ),
		_StopReqested( false )
{
	assert( _Runable );
}
//--------------------------------------------------------------
CrossThread::~CrossThread( void )
{
	Stop();
}
//--------------------------------------------------------------
bool CALL_CONVERSION 		CrossThread::Start( void )
{
	boost::mutex::scoped_lock lck(_Mutex);

	if ( _Thread.get() != 0 )
		return false;

	_StopReqested = false;
	_Thread = boost::shared_ptr< boost::thread >( new boost::thread( boost::bind( &CrossThread::DoWork, this ) ) );
	
	return ( _Thread.get() != 0 );
}
//--------------------------------------------------------------	
void CALL_CONVERSION 		CrossThread::Stop( void )
{
	boost::mutex::scoped_lock lck( _Mutex );
	if ( _Thread )
	{
		_StopReqested = true;
		_Thread->interrupt();
		_Thread->join();
		_Thread.reset();
	}
}
//--------------------------------------------------------------
void CALL_CONVERSION 		CrossThread::SleepSec( const unsigned long InSeconds )
{
	if ( _Thread.get() == 0 )
			return;

	boost::xtime xt;
#if defined(__USE_ISOC11) || BOOST_VERSION >= 105600
    boost::xtime_get( &xt, boost::TIME_UTC_ );
#else
    boost::xtime_get( &xt, boost::TIME_UTC );
#endif
	xt.sec += InSeconds;
	_Thread->sleep( xt );
}
//--------------------------------------------------------------
void CALL_CONVERSION 		CrossThread::SleepMs( const unsigned long InMilliSeconds )
{
	if ( _Thread.get() == 0 )
		return;

	unsigned long secs = InMilliSeconds / 1e3;
	
	boost::xtime xt;
#if defined(__USE_ISOC11) || BOOST_VERSION >= 105600
    boost::xtime_get( &xt, boost::TIME_UTC_ );
#else
    boost::xtime_get( &xt, boost::TIME_UTC );
#endif
	xt.sec += secs;
	xt.nsec += ( InMilliSeconds - ( secs * 1e3 ) )  * 1e6;

	_Thread->sleep( xt );
}
//--------------------------------------------------------------
void CALL_CONVERSION		CrossThread::SleepMcs( const unsigned long InMicroSeconds )
{
	if ( _Thread.get() == 0 )
		return;

	unsigned long secs = InMicroSeconds / 1e6;
	
	boost::xtime xt;
#if defined(__USE_ISOC11) || BOOST_VERSION >= 105600
    boost::xtime_get( &xt, boost::TIME_UTC_ );
#else
    boost::xtime_get( &xt, boost::TIME_UTC );
#endif
	xt.sec += secs;
	xt.nsec += ( InMicroSeconds - ( secs * 1e6 ) )  * 1e3;

	_Thread->sleep( xt );
}
//--------------------------------------------------------------
bool CALL_CONVERSION 		CrossThread::WannaStop( void )
{
	return _StopReqested;
}
//--------------------------------------------------------------
bool CALL_CONVERSION 		CrossThread::IsStoped( void )
{
	boost::mutex::scoped_lock lck( _Mutex );
	return ( _Thread.get() == 0 );
}
//--------------------------------------------------------------
void 						CrossThread::DoWork( void )
{
	_Runable->Execute();
}
