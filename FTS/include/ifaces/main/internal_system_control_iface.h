#pragma once 

#include "../../common/config-win32.h"
#include "../../common/typedefs.h"
#include <exception>

namespace FTS{
	namespace Ifaces{
		namespace InternalSystemControl{


//тут выравнивание по 1-му байту
#pragma pack(push,1)
struct ControlParameterDescriber
{
	//! Идентификатор параметра ВСК
	char 		Identifier[FTS::Const::SIZE_KEY_STRING];
	//! Минимальная и максимальная граница зоны нормального состояния ВСК
	float 		MinNormalZoneLimit;
	float 		MaxNormalZoneLimit;
	//! Минимальная и максимальная граница зоны состояния ВСК, требующего внимания
	float 		MinWarningZoneLimit;
	float 		MaxWarningZoneLimit;
};

#pragma pack(pop)

/**
 * @brief Интерфейс для заполнения описания параметров ВСК
 **/
class IControlParameterSetter
{
public:
	virtual void CALL_CONVERSION AddParameter( const FTS::Ifaces::InternalSystemControl::ControlParameterDescriber* inParameter ) = 0;
};

/**
 * @brief Интерфейс встроенной системы контроля (ВСК)
 **/
class IControlParameters
{
public:
	/**
	 * @brief Получить описание контролируемых параметров
	 *
	 * @param inOutParameterSetter Указатель на объект setter, в который помещаюся описания контролируемых параметров.
	 * @param InKeyISCNode ключ узла данных ВСК
	 * @return void
	 **/
	virtual void	CALL_CONVERSION GetControlParameterList( FTS::Ifaces::InternalSystemControl::IControlParameterSetter* inOutParameterSetter, 
															 const char* InKeyISCNode = 0
														   ) const = 0;
	
	/**
	 * @brief Проверить на изменение списка экспортируемых параметров ВСК
	 * \remarks Данный флаг имеет значение для Контроллера ВСК. Вся ответственность по формированию
	 * и дальнейшей корректной отработке списка параметров ложится на конкретный модуль!
	 * @param InKeyISCNode ключ узла данных ВСК
	 * @return bool true - список параметров изменен, в противном случае всегда false
	 **/
	virtual bool 	CALL_CONVERSION	ParameterListChanged( const char* InKeyISCNode = 0 ) const = 0;
	
	/**
	 * @brief Состояние контролируемого параметра
	 *
	 * @param  Идентификатор контролируемого параметра
	 * @return состояние контролияруемого параметры
	 **/
	virtual float 	CALL_CONVERSION GetState( char inControlParameterId[FTS::Const::SIZE_KEY_STRING] ) const throw(std::exception)= 0;
};

}//namespace InternalSystemControl
}//namespace Ifaces
}//namespace FTS
