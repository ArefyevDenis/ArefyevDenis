
#pragma once

#include <QString>

#include "../../../../include/ifaces/main/module_iface.h"

class TcpServer;

//==================================================================================================================//
/**
 * @brief Класс модуля организующего обмен по TCP
 **/
class ModuleTcpServer: public FTS::Ifaces::IModule
{
public:
    ModuleTcpServer();
    virtual ~ModuleTcpServer();

    /**
     * @brief Инициализация модуля
     *
     * @param ICoreMainIfaces ядро главных интерфейсов
     * @return void
     **/
    void CALL_CONVERSION Initialize( FTS::Ifaces::ICoreMainIfaces* InCoreMainfaces );

    /**
     * @brief Запуск работы модуля
     *
     * @param  ...
     * @return void
     **/
    void CALL_CONVERSION Start( void );

    /**
     * @brief Стоп работы модуля
     *
     * @param  ...
     * @return void
     **/
    void CALL_CONVERSION Stop( void );

    /**
     * @brief Получить интерфейс в соответствии с указанными параметрами
     *
     * @param InIfaceId идентификатор запрашиваемого интерфейса
     * @param InIfaceVersion версия запрашиваемого интерфейса
     * @return :Interfaces::IExportInterface*
     **/
    FTS::Ifaces::IExportIface* CALL_CONVERSION GetExportedIface( const char* InIfaceId, const unsigned int InIfaceVersion );

    /**
     * @brief Удаление объекта
     *
     * @param  ...
     * @return void
     **/
    void CALL_CONVERSION Release( void );

private:

    void        LoadArguments( void );


    void        LoadConfiguration();


    void        LoadExportedInterfaces();

private:
    /**
     * @brief Фабрика интерфейсов, предоставляемых ядром
     **/
    FTS::Ifaces::ICoreMainIfaces* m_pCoreMainIfaces;

    /**
     * @brief Объект организующий обмен по TCP
     **/
    TcpServer*                                  m_pTcpServer;

    QString                                     m_Ipv4ListenIface;

    unsigned int                                m_ListenPort;

};
//-----------------------------------------------------------------------------
