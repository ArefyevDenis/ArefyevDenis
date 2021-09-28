
#pragma once

class IISCController;

namespace FTS{
        namespace Ifaces{
		class IModulesService;
	}
}

//==============================================================================================================///**
/**
 * @brief Надстройка над Контроллером ВСК
 **/
class ICSControllerHandler{
public:

    ICSControllerHandler( FTS::Ifaces::IModulesService* InModulesService );
    ~ICSControllerHandler( void );
	
public:

    /**
     * @brief Получить интерфейс контроллера ВСК
     *
     * @param  ...
     * @return IISCController*
     **/
    IISCController* GetISCControllerIface( void );
	
private:

    /**
     * @brief Интерфейс сервисного доступа к модулям
     **/
    FTS::Ifaces::IModulesService* _ModulesService;
	
};
//==============================================================================================================//
