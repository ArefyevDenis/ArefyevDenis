
#pragma once

#pragma pack( push, 4 )

#include <QtCore/QString>

namespace FTS{
        namespace Ifaces{
                class IExportIface;
	};
};

/**
 * @brief Структура с описанием параметров интерфейса
 **/
struct IfaceStructDescriber
{
        QString interface_id;
        unsigned int minor_version;
        FTS::Ifaces::IExportIface* ptr_iface;
	
        IfaceStructDescriber():
		interface_id( "" ),
		minor_version( 0 ),
		ptr_iface( 0 )
	{
	}
};

#pragma pack( pop )
