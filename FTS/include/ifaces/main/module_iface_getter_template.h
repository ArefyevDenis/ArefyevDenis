
#pragma once 

#include <assert.h>

namespace FTS{
	namespace Ifaces{
class IModule;
	};

namespace Templates{
/**
 * @brief Шаблонный класс для получения интерфейса модуля
 **/
template class< T > class ModuleIfaceGetter
{
public:	
	typedef T Module_Type;
	
	ModuleIfaceGetter( void ): _ModuleIface( 0 )
	{
	}
	~ModuleIfaceGetter( void )
	{
	}
	
	void 			SetModuleIface( IModule* InModuleIface )
	{
		_ModuleIface = reinterpret_cast< Module_Type* >( InModuleIface );
		assert( _ModuleIface );
	}
	
	Module_Type* 	GetModuleIface( void )
	{
		return _ModuleIface;
	}
	
private:
	/**
	 * @brief Интерфейс модуля
	 **/
	Module_Type*	_ModuleIface;
};
	};
};