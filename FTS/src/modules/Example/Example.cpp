#include "Example.h"

//================================================== PBULIC ========================================================//
//==================================================================================================================//
Example::Example(FTS::Ifaces::ICoreMainIfaces *pCoreMainIface):
    m_pCoreMainIface(pCoreMainIface) {
}

Example:: ~Example() {

}

//==================================================================================================================//
const char *CALL_CONVERSION Example::GetId(){
    return EXAMPLE_IFACE_ID;
}

unsigned int CALL_CONVERSION Example::GetVersion() {
    return EXAMPLE_IFACE_VERSION;
}

//==================================================================================================================//
QObject* CALL_CONVERSION Example::getObjectPtr(){
    QObject* ptr = (QObject*) this;
    return ptr;
}

//==================================================================================================================//
const char* CALL_CONVERSION Example::getSignalPtr(){
    const char* ptr = (const char*)SIGNAL(signalEvent(int));
    return ptr;
}

//==================================================================================================================//

