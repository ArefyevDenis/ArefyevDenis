
#pragma once

#pragma once 

#include <vector>

#include "../../include/ifaces/main/export_interfaces_describer_iface.h"

typedef std::vector< FTS::BasesTypes::ExportInterfaceInfo > ExportInterfaceInfoCont;

namespace FTS{
	namespace Utils{

class ExportInterfacesDescriber:
        public ExportInterfaceInfoCont,
        public FTS::Ifaces::IExportInterfaceInfoDescriber
{
public:
	ExportInterfacesDescriber( void );
	~ExportInterfacesDescriber( void );
	
//--- FTS::Ifaces::IUsageLibraryInfoDescriber
public:
    /**
     * @brief Добавить описание экспортиуремого интерфейса в описатель
     *
     * @param InInfo описание библиотеки
     * @return void
    **/
    void CALL_CONVERSION AddInterfaceInfo( FTS::BasesTypes::ExportInterfaceInfo* InInfo );
	
    /**
     * @brief Очистить данные в описателе
     *
     * @param  ...
     * @return void
     **/
    void CALL_CONVERSION Clear( void );
	
};

	};
};
