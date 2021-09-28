
#pragma once 

#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{
		namespace InternalSystemControl{
			class IControlParameters;
		}
	}
}

namespace FTS{
        namespace Ifaces{
		
//------------------------------------------------------------------
/**
 * @brief Интерфейс сервисного доступа к ВСК
 **/
class IInternalSystemControlService {
public:
	/**
	 * @brief Зарегистрировать узел ВСК в Системе
         * @param InControlParameters интерфейс передачи параметров ВСК и их значений
	 * @param InKeyISCNode ключ узла данных ВСК
	 * @return bool - успешность регистрации параметра ВСК
	 * \remarks Цепочка узлов 2го типа, к которой должен "клеиться" данный 
	 * узел с контролируемыми параметрами, выставляется каждым модулем 
	 * в описательном классе модуля (см. метод FillExportingISCParametersDescriber)
	 * При несоотевтствии и в прочих ситуациях (несоотевтствие с конфигурационным файлов)
	 * результат ошибочный
	 **/
        virtual bool CALL_CONVERSION RegisterInternalSystemControlNode(
            const FTS::Ifaces::InternalSystemControl::IControlParameters* InControlParameters,
            const char* InKeyISCNode
        ) = 0;
	
};
//------------------------------------------------------------------
	}
};
