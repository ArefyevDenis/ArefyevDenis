#ifndef		_MODULE_TCP_CLIENT_H_
#define		_MODULE_TCP_CLIENT_H_

#include "../../../../include/ifaces/main/module_iface.h"
#include "tcp_client.h"


/**
 * @brief Класс модуля организующего обмен по TCP
 **/
class ModuleTcpClient : public FTS::Ifaces::IModule
{

public:
    ModuleTcpClient();
    virtual ~ModuleTcpClient();

    /**
     * @brief Инициализация модуля
     *
     * @param ICoreMainIfaces ядро главных интерфейсов
     * @return void
     **/
    virtual void CALL_CONVERSION Initialize( FTS::Ifaces::ICoreMainIfaces* InCoreMainIfaces );
    /**
     * @brief Запуск работы модуля
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Start( void );
    /**
     * @brief Стоп работы модуля
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Stop( void );
    /**
     * @brief Получить интерфейс в соответствии с указанными параметрами
     *
     * @param InIfaceId идентификатор запрашиваемого интерфейса
     * @param InIfaceVersion версия запрашиваемого интерфейса
     * @return :Interfaces::IExportInterface*
     **/
    virtual FTS::Ifaces::IExportIface* CALL_CONVERSION GetExportedIface( const char* InIfaceId, const unsigned int InIfaceVersion );
    /**
     * @brief Удаление объекта
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Release( void );

private:

    void LoadArguments( );

    void LoadConfiguration();

    void LoadExportedInterfaces();

private:

    /**
     * @brief Фабрика интерфейсов, предоставляемых ядром
     **/
    FTS::Ifaces::ICoreMainIfaces *m_pCoreMainIfaces;

    /**
     * @brief Объект организующий обмен по TCP
     **/
    TcpClient *m_pTcpClient;
    QString m_Ipv4Host;
    unsigned int m_port;

};

#endif		//_MODULE_TCP_CLIENT_H_
