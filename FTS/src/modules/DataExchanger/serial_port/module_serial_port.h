#ifndef		_MODULE_SERIAL_PORT_H_
#define		_MODULE_SERIAL_PORT_H_

#include "../../../../include/ifaces/main/module_iface.h"
#include "serial_port.h"


/**
 * @brief Класс модуля организующего обмен по COM порту
 **/
class ModuleSerialPort : public FTS::Ifaces::IModule
{
public:
    ModuleSerialPort();
    virtual ~ModuleSerialPort();

    /**
     * @brief Инициализация модуля
     *
     * @param ICoreMainInterfaces ядро главных интерфейсов
     * @return void
     **/
    virtual void CALL_CONVERSION Initialize(FTS::Ifaces::ICoreMainIfaces* InCoreMainIfaces );
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

    FTS::Ifaces::ICoreMainIfaces *m_pCoreMainIfaces;

    SerialPort *m_pSerialPort;

    QString m_name;
    unsigned int m_baud;
    unsigned int m_dbits;
    unsigned int m_sbits;
    unsigned int m_parity;
    unsigned int m_fctrl;

};

#endif		//_MODULE_SERIAL_PORT_H_
