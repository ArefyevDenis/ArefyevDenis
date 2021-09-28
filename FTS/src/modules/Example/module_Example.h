#ifndef		_MODULE_EXAMPLE_H_
#define		_MODULE_EXAMPLE_H_


#include "../../../../include/ifaces/main/module_iface.h"
#include "Example.h"

class IDataExchange;

class ModuleExample : public FTS::Ifaces::IModule
{
public:
    ModuleExample();
    virtual ~ModuleExample();

    /**
     * @brief Инициализация модуля
     *
     * @param ICoreMainIfaces ядро главных интерфейсов
     * @return void
     **/
    virtual void CALL_CONVERSION Initialize ( FTS::Ifaces::ICoreMainIfaces* InCoreMainIfaces );

    /**
     * @brief Запуск работы модуля
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Start ( void );

    /**
     * @brief Стоп работы модуля
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Stop ( void );

    /**
     * @brief Получить интерфейс в соответствии с указанными параметрами
     *
     * @param InIfaceId идентификатор запрашиваемого интерфейса
     * @param InIfaceVersion версия запрашиваемого интерфейса
     * @return :Interfaces::IExportInterface*
     **/
    virtual FTS::Ifaces::IExportIface* CALL_CONVERSION GetExportedIface ( const char* InIfaceId, const unsigned int InIfaceVersion );

    /**
     * @brief Удаление объекта
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Release ( void );

private:


    FTS::Ifaces::ICoreMainIfaces *m_pCoreMainIfaces;    //Фабрика интерфейсов, предоставляемых ядром
    Example *m_pExample;                                //Объект предоставляемого класса

    // просто для примера
    QString m_libTcpServerDataExchanger;                //Имя либины из котрой будем тянуть нужный интерфейс
    QString m_libTcpClientDataExchanger;                //Имя либины из котрой будем тянуть нужный интерфейс

    IDataExchange* m_pTcpServer;                        //Указатель на вытянутый интерфейс
    IDataExchange* m_pTcpClient;                        //Указатель на вытянутый интерфейс


    /**
     * @brief Загрузить аргументы модуля
     *
     * @param  ...
     * @return void
     **/
    void LoadArguments();

    /**
     * @brief Загрузить конфигурацию модуля
     *
     * @return void
     **/
    void LoadConfiguration();

    /**
     * @brief Загрузить экспортированные из других модулей интерфейсы
     *
     * @param  ...
     * @return void
     **/
    void LoadExportedInterfaces();


};

#endif		//_MODULE_EXAMPLE_H_
