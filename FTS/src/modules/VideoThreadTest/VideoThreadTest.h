#ifndef _VIDEO_THREAD_TEST_H_
#define _VIDEO_THREAD_TEST_H_

#include "../../../../include/ifaces/main/module_iface.h"
#include "../../../../include/ifaces/modules/VideoThreadTest_iface/VideoThreadTest_iface.h"
#include <QtCore/QtGlobal>
#include <QObject>
#include <QTimer>

class IVideoSender;
class IVideoReceiver;

class VideoThreadTest: public QObject,
               public IVideoThreadTest
{
    Q_OBJECT

public:


    VideoThreadTest(FTS::Ifaces::ICoreMainIfaces *pCoreMainIface);
    virtual ~VideoThreadTest();

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

    /**
     * @brief init - функция инициализации конфигурайий
     */
    void init_and_start();

private:

    void LoadArguments();
    void LoadConfiguration();
    void LoadExportedInterfaces();

    FTS::Ifaces::ICoreMainIfaces *m_pCoreMainIface;

    QString m_libReceiver;  //имя либины получателя
    QString m_libSender;    //имя либины отправителя

    IVideoReceiver *m_pVideoReceiver;   //интерфейс получателя
    IVideoSender *m_pVideoSender;       //интерфейс отправителя

    unsigned int m_rate;        //сколько раз в секунду обновлять
    QTimer *m_pTimerRefresh;    //таймер обновления

    QString m_base_dev;         //базовое имя устройства
    unsigned int m_refDev;      //время обновления мс
    QTimer *m_pTimerDev;        //таймер поиска
    bool m_error;               //флаг ошибки

    QTimer *m_pTimerReboot;     //таймер перезапуска конвеера
    unsigned int m_rebootTime;  //время ребута

private slots:
    void refreshImage();
    void refreshDev();
    void rebootPipeline();

};



#endif // _VIDEO_THREAD_TEST_H_
