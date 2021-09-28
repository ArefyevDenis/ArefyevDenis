#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_

#include "../../../../include/ifaces/main/module_iface.h"
#include "../../../../include/ifaces/modules/Example_iface/Example_iface.h"
#include <QtCore/QtGlobal>
#include <QObject>


class Example: public QObject,
               public IExample
{
    Q_OBJECT

public:


    Example(FTS::Ifaces::ICoreMainIfaces *pCoreMainIface);
    virtual ~Example();

    //===================================== из FTS::Ifaces::IExportIface ===============================================//

    /**
    * @brief Получить версию интерфейса
    *
    * @param  ...
    * @return unsigned int
    **/
    virtual unsigned int CALL_CONVERSION GetVersion( void );

    /**
    * @brief Получить идентификатор интерфейса
    *
    * @param  ...
    * @return const char*
    **/
    virtual const char* CALL_CONVERSION GetId( void );

    //========================================= для проброса сигнала о событии ==========================================//
    /**
     * @brief getObjectPtr - указатель на объект нашего класса, чтобы привязаться к источнику сигнала
     * @return
     */
    virtual QObject* CALL_CONVERSION getObjectPtr();

    /**
     * @brief getSignalPtr - указатель на сигнал от нашего объекта
     * @return
     */
    virtual const char* CALL_CONVERSION getSignalPtr();

private:

    FTS::Ifaces::ICoreMainIfaces *m_pCoreMainIface;


private slots:

signals:
    void signalEvent( int );

};



#endif // _EXAMPLE_H_
