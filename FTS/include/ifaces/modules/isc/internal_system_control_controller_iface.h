
#pragma once

#include <string>

#include "../../main/export_interface_iface.h"
#include "../../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{
		namespace InternalSystemControl{
			class IControlParameters;
		}
	}
}

//------------------------------------------------------------------
#define ISC_CONTROLLER_IFACE_ID 		"isc_controller_iface"
#define ISC_CONTROLLER_IFACE_VERSION            3
//------------------------------------------------------------------

/**
 * @brief Интерфейс Контроллера ВСК
 **/
class IISCController: public FTS::Ifaces::IExportIface
{
public:

    /**
     * @brief Зарегистрировать обработчик в Контроллере ВСК
     *
     * @param InControlParameters интерфейс передачи параметров ВСК и их значений
     * @param InFullNodeChain полная цепочка узлов ВСК 2го типа в рамках приложения
     * @param InISCKeyNodeId идентификатор ключа узла непосредственно из модуля
     * @return bool - успешность регистрации параметра ВСК
     * \remarks Цепочка узлов 2го типа, к которой должен "клеиться" данный
     * узел с контролируемыми параметрами, выставляется каждым модулем
     * в описательном классе модуля (см. метод FillExportingISCParametersDescriber)
     * При несоотевтствии и в прочих ситуациях (несоотевтствие с конфигурационным файлов)
     * результат ошибочный
     **/
    virtual bool CALL_CONVERSION	RegisterISCProcessor(
            const FTS::Ifaces::InternalSystemControl::IControlParameters* InControlParameters,
            const char* InModuleId,
            const char* InISCKeyNodeId,
            const std::string& InFullNodeChain
            ) = 0;
};
//------------------------------------------------------------------

