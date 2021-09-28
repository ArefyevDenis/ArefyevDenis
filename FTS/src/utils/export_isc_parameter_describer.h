
#pragma once

#pragma once 

#include <vector>

#include "../../include/ifaces/main/exported_internal_system_control_parameters_iface.h"

typedef std::vector< FTS::BasesTypes::ExportIscParameter > ExportIscParameterCont;

namespace FTS{
	namespace Utils{

class ExportISCParameterDescriber: public FTS::Ifaces::IExportedISCParameters,
                                   public ExportIscParameterCont
{
public:
    ExportISCParameterDescriber( void );
    ~ExportISCParameterDescriber( void );
	
//--- FTS::Ifaces::IExportedISCParameters
public:

    /**
     * @brief Добавить описание параметра ВСК
     *
     * @param InInfo описание параметра
     * @return void
     **/
    void CALL_CONVERSION AddISCParameterInfo( const FTS::BasesTypes::ExportIscParameter* InInfo );
	
    /**
     * @brief Очистить данные
     *
     * @param  ...
     * @return void
     **/
    void CALL_CONVERSION Clear( void );
};

	};
};
