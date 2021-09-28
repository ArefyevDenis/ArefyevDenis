
#pragma once

#include "../../../../include/ifaces/main/export_interface_iface.h"

#define EXAMPLE_IFACE_ID 		"Example_iface"
#define EXAMPLE_IFACE_VERSION		1

#include <QObject>

class IExample : public FTS::Ifaces::IExportIface {

public:

    //============================================ для проброса сигнала о событии ======================================//
    //===================== Не самый лучший способ, но иногда полезно, оставил для примера =============================//
    /**
     * @brief getObjectPtr - указатель на объект нашего класса, чтобы привязаться к источнику сигнала
     * @return
     */
    virtual QObject* CALL_CONVERSION getObjectPtr() = 0;

    /**
     * @brief getSignalPtr - указатель на сигнал от нашего объекта
     * @return
     */
    virtual const char* CALL_CONVERSION getSignalPtr() = 0;

};





