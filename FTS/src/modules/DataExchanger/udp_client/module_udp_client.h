#ifndef		_MODULE_UDP_CLIENT_H_
#define		_MODULE_UDP_CLIENT_H_

#include "../../../../include/ifaces/main/module_iface.h"
#include "udp_client.h"


/**
 * @brief Класс модуля организующего обмен по UDP
 **/
class ModuleUdpClient : public FTS::Ifaces::IModule
{
public:
    ModuleUdpClient();
    virtual ~ModuleUdpClient();

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
     * @brief Объект организующий обмен по UDP
     **/
    UdpClient *m_pUdpClient;

    QString m_host_dst;
    unsigned int m_port_dst;
    QString m_host_src;
    unsigned int m_port_src;
    bool m_mcast;



};

#endif		//_MODULE_UDP_CLIENT_H_
