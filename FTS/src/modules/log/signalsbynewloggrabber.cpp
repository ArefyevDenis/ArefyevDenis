#include <assert.h>
#include <iostream>

#include <signalappender.h>

#include "signalsbynewloggrabber.h"

//-----------------------------------------------------------------------------
SignalsByNewLogGrabber::SignalsByNewLogGrabber( Log4Qt::SignalAppender* InSignalAppender ):
    m_pSignalAppender( InSignalAppender )
{
    assert( m_pSignalAppender );

    Initialize();
}
//-----------------------------------------------------------------------------
SignalsByNewLogGrabber::~SignalsByNewLogGrabber( void )
{

}
//-----------------------------------------------------------------------------
bool 		SignalsByNewLogGrabber::RegisterLogMessagesGrabberIface( const ILogMessagesGrabber* InIface )
{
    assert( InIface );

    _LogMessagesGrabberPool.push_back( InIface );

    return true;
}
//-----------------------------------------------------------------------------
unsigned int CALL_CONVERSION		SignalsByNewLogGrabber::GetVersion( void )
{
    return LOG_MESSAGES_GRABBER_IFACE_VERSION;
}
//-----------------------------------------------------------------------------
const char* CALL_CONVERSION			SignalsByNewLogGrabber::GetId( void )
{
    return LOG_MESSAGES_GRABBER_IFACE_ID;
}
//-----------------------------------------------------------------------------
void            SignalsByNewLogGrabber::Initialize( void )
{
    connect( m_pSignalAppender, SIGNAL(appended(QString)), this, SLOT(OnNewLogMessage(QString)) );
}
//-----------------------------------------------------------------------------
void            SignalsByNewLogGrabber::OnNewLogMessage( const QString& InMessage )
{
    LogMessagesGrabberPoolCIter it = _LogMessagesGrabberPool.begin();

    for( ; it != _LogMessagesGrabberPool.end(); it++ )
    {
        ( *it )->ProcessLogMessage( InMessage );
    }
}
//-----------------------------------------------------------------------------

//#include "signalsbynewloggrabber.moc"
