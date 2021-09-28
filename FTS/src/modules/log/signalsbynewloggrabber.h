#pragma once

#include <QObject>
#include <QString>

#include <QList>

namespace Log4Qt{
    class SignalAppender;
}

#include "../../../include/ifaces/modules/log/log_messages_grabber_iface.h"

//==============================================================================================================//
typedef QList< const ILogMessagesGrabber* > LogMessagesGrabberPool;
typedef LogMessagesGrabberPool::iterator LogMessagesGrabberPoolIter;
typedef LogMessagesGrabberPool::const_iterator LogMessagesGrabberPoolCIter;
//==============================================================================================================//
/**
 * @brief Класс перехвата сигналов из дебрей SignalsAppender для отработки в системе
 */
class SignalsByNewLogGrabber: public QObject,
                                public ILogMessagesGrabbersPool
{
    Q_OBJECT

public:
    SignalsByNewLogGrabber( Log4Qt::SignalAppender* InSignalAppender );
    ~SignalsByNewLogGrabber();

//--- ILogMessagesGrabbersPool
public:
    /**
     * @brief Зарегистрировать обработчик сообщений протокола работы приложения
     * @param ILogMessagesGrabber - объект обработки сообщений о работе приложения
     **/
    bool 		RegisterLogMessagesGrabberIface( const ILogMessagesGrabber* InIface );

//--- IExportIface
public:
    /**
     * @brief Получить версию интерфейса
     *
     * @param  ...
     * @return unsigned int
     **/
    unsigned int CALL_CONVERSION GetVersion( void );

    /**
     * @brief Получить идентификатор интерфейса
     *
     * @param  ...
     * @return const char*
     **/
    const char* CALL_CONVERSION	GetId( void );

private:
    /**
     * @brief Инициализация
     */
    void Initialize( void );

private slots:
    /**
     * @brief Слот для отработки логики вновь прихолдящего сообщения
     * @param InMessage - текст сообщения
     */
    void OnNewLogMessage( const QString& InMessage );

private:

    Log4Qt::SignalAppender*             m_pSignalAppender;

    LogMessagesGrabberPool              _LogMessagesGrabberPool;
};
//-----------------------------------------------------------------------------
