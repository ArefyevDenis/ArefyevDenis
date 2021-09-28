#ifndef     _DATA_EXCHANGE_INTERFACE_H_
#define     _DATA_EXCHANGE_INTERFACE_H_


#include "../../main/export_interface_iface.h"
#include "../../../common/config-win32.h"

#define DATA_EXCHANGE_IFACE_ID            "data_exchange_iface"
#define DATA_EXCHANGE_IFACE_VERSION       1

//==================================================================================================================//
//Интерфейс для полученния данных
class IDataReceiver
{
public:
    /**
     * @brief Полученные данные
     *
     * @param buffer - массив данных
     * @param size - размер массива
     * @return void
     **/
    virtual void CALL_CONVERSION setData( char * data, int size ) = 0;

    /**
     * @brief Посуте дела сигнал о подключении
     *
     * @return void
     **/
    virtual void CALL_CONVERSION Connnect() = 0;

    /**
     * @brief Посуте дела сигнал о  разрыве соединения
     *
     * @return void
     **/
    virtual void CALL_CONVERSION Disconnect() = 0;

};

//==================================================================================================================//
//Интерфейс объекта обмена данными
class IDataExchange : public FTS::Ifaces::IExportIface
{
public:
    /**
     * @brief Передача данных
     *
     * @param  data - данные
     * @param  size - размер массива данных
     * @return ...
     **/
    virtual void CALL_CONVERSION write(const char* data, int size) = 0;

    /**
     * @brief установить приёмник данных
     *
     * @param InIDataReceiver - приёмник данных
     * @return void
     **/
    virtual void CALL_CONVERSION setIDataReceiver( IDataReceiver * InIDataReceiver ) = 0;

    /**
     * @brief Возвращает состояние подключения
     *
     * @return true - соединение есть, false - неподключены
     **/
    virtual bool CALL_CONVERSION isConnect() = 0;

};

#endif      //_DATA_EXCHANGE_INTERFACE_H_
