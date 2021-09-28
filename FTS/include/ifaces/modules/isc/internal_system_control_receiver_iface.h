
#pragma once

#include "../../main/export_interface_iface.h"
#include "../../../common/config-win32.h"

namespace InternalSystemControl{
	class IReceiverSelectedISCParameters;
}

//---------------------------------------------------------------------
#define ISC_RECEIVER_IFACE_ID 		"isc_receiver_iface"
#define ISC_RECEIVER_IFACE_VERSION	1
//---------------------------------------------------------------------
/**
 * @brief Интерфейс приемника данных ВСК
 **/
class IISCReceiver: public KilimoOte::Interfaces::IExportInterface
{
public:
	/**
	 * @brief Зарегистрировать интерфейс получения данных о желаемых параметрах ВСК
	 *
	 * @param InReceiver получатель информации
	 * @return void
	 **/
	virtual void CALL_CONVERSION		RegisterSelectedISCParametersReceiver( InternalSystemControl::IReceiverSelectedISCParameters* InReceiver ) = 0;
	
};
//---------------------------------------------------------------------
