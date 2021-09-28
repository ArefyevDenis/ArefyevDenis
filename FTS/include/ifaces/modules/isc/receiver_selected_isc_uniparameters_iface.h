
#pragma once

#include <memory.h>

#include "../../../common/config-win32.h"
#include "../../../common/typedefs.h"

 namespace KilimoOte{
 	namespace Interfaces{
 		namespace ISC{
#pragma pack(push,1)
struct UniControlParameterDescriber
{
	//! Идентификатор параметра ВСК
	char 		Identifier[ KilimoOte::Const::SIZE_KEY_STRING ];
	//! Описание параметра
	char 		ParameterDescriptor[ KilimoOte::Const::SIZE_SHORT_STRING ];
	//! Минимальная и максимальная граница зоны нормального состояния ВСК
	float 		MinNormalZoneLimit;
	float 		MaxNormalZoneLimit;
	//! Минимальная и максимальная граница зоны состояния ВСК, требующего внимания
	float 		MinWarningZoneLimit;
	float 		MaxWarningZoneLimit;
	//!Полное символьное имя параметра
	std::string FSN;
	
	UniControlParameterDescriber()
	{
	  memset(Identifier,0,KilimoOte::Const::SIZE_KEY_STRING);
	  memset(ParameterDescriptor,0,KilimoOte::Const::SIZE_SHORT_STRING );
	  MinNormalZoneLimit	= 0.9;
	  MaxNormalZoneLimit	= 1.1;
	  MinWarningZoneLimit	= 0.9;
	  MaxWarningZoneLimit	= 1.1;
	  FSN.clear();
	}
};
#pragma pack(pop)
 		}
 	}
 }

#include <vector>
#include <string>
namespace InternalSystemControl{
	
//-------------------------------------------------------------
/**
 * @brief Приемник выбранных параметров ВСК
 **/
class IReceiverSelectedISCParameters
{
public:
	/**
	 * @brief Получить перечень унифицированных идентификаторов, желаемых для получения
	 *
	 * @param OutFullParameterNames - вектор, содержащий полные символьные имена запрашиваемых параметров (в формате АПС/Приложение/Сущность/.../Сущность/Имя параметра
	 **/
	virtual void CALL_CONVERSION GetUnifiedIdParameters( std::vector <std::string> & OutFullParameterNames ) = 0;
	
	/**
	 * @brief Обозначение начала цикла записи параметров
	 *
	 * @param  ...
	 * @return void
	 **/
	virtual void CALL_CONVERSION		BeginPushISCParameters( void ) = 0;
	
	/**
	 * @brief Добавить информацию о параметре ВСК
	 *
	 * @param InDescriber описатель параметра
	 * @param InActualValue актуальное значение
	 * @return void
	 **/
	virtual void CALL_CONVERSION		PushISCParameterInfo( 
												const KilimoOte::Interfaces::ISC::UniControlParameterDescriber* InDescriber,
												const float InActualValue
											) = 0;
	
	/**
	 * @brief Обозначение начала окончания записи параметров
	 *
	 * @param  ...
	 * @return void
	 **/
	virtual void CALL_CONVERSION		EndPushISCParameters( void ) = 0;
	
};
//-------------------------------------------------------------

};
