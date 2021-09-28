
#pragma once

#include <QString>
#include <QtWidgets/QAction>
#include <QList>
#include <QMap>
#include <boost/thread.hpp>

//==============================================================================================================//
/**
 * @brief Описа тель Действия
 **/
struct ActionHandler{
    const QAction*  action;
    QString         action_id;

    ActionHandler():
        action( 0 ),
        action_id( "" ){
	}
	
    ActionHandler( const QAction* InAction, const QString& InActionId ):
        action( InAction ),
        action_id( InActionId ){
	}
};

//==============================================================================================================//
typedef QList< ActionHandler > ActionHandlerCont;
typedef ActionHandlerCont::iterator ActionHandlerContIter;
typedef ActionHandlerCont::const_iterator ActionHandlerContCIter;
//==============================================================================================================//
typedef QMap< QString, ActionHandlerCont > ActionHandlerContMap;
typedef ActionHandlerContMap::iterator ActionHandlerContMapIter;
typedef ActionHandlerContMap::const_iterator ActionHandlerContMapCIter;
//==============================================================================================================//

/**
 * @brief Класс пулла Действий в Системе
 **/
class ActionsPool{
public:
    ActionsPool( void );
    ~ActionsPool( void );
	
public:

    /**
     * @brief Добавить действие
     * @param InModuleId идентификатор модуля
     * @param InActionId идентификатор действия
     * @param InAction действие
     * @return bool - результат добавления
     **/
    bool AddAction( const QString& InModuleId, const QString& InActionId, const QAction* InAction );
	
    /**
     * @brief Проверить наличие Действия для указанных условий
     * @param InModuleId идентификатор модуля
     * @param InActionId идентификатор Действия
     * @return bool - признак наличия
     **/
    bool ActionInPresence( const QString& InModuleId, const QString& InActionId ) const;
	
    /**
     * @brief Получить количество действий, предоставляемых модулем
     * @param InModuleId идентификатор модуля
     * @return unsigned int - количество (от 0 до N)
     **/
    unsigned int GetCountActions( const QString& InModuleId ) const;
	
    /**
     * @brief Получить Действие по индексу
     * @param InModuleId идентификатор модуля, реализующий Действие
     * @param InIndex индекс действия
     * @return QAction* - результат (0 при отсутствии Действия)
     **/
    const QAction* GetActionByIndex( const QString& InModuleId, unsigned int InIndex ) const;
	
    /**
     * @brief Получить Действие по его идентификатору
     * @param InModuleId идентификатор модуля
     * @param InActionId идентификатор Действия
     * @return QAction* - результат (0 при отсутствии Действия)
     **/
    const QAction* GetActionById( const QString& InModuleId, const QString& InActionId ) const;
	
private:

    ActionHandlerContMap m_AllActions;  //Хэш со всеми Действиями, зарегистрированными в Системе
    mutable boost::mutex m_Mutex;       //Объект безопасного доступа к данным
	
};
//==============================================================================================================//
