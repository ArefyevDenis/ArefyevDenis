
#include "actions_pool.h"

//==============================================================================================================//
ActionsPool::ActionsPool( void ){

}

//==============================================================================================================//
ActionsPool::~ActionsPool( void ){

}

//==============================================================================================================//
bool ActionsPool::AddAction( const QString& InModuleId, const QString& InActionId, const QAction* InAction ){
    boost::mutex::scoped_lock locker( m_Mutex );
	// Поищем для начала...
    ActionHandlerCont& cont_for_module = m_AllActions[ InModuleId ];
	ActionHandlerContCIter it = cont_for_module.begin();
	
    for( ; it != cont_for_module.end(); it++ ){
        if( ( *it ).action_id == InActionId ){
			return false;
		}
	}
	
	// А потом при необходимости добавим...
	cont_for_module.append( ActionHandler( InAction, InActionId ) );
	return true;
}

//==============================================================================================================//
bool ActionsPool::ActionInPresence( const QString& InModuleId, const QString& InActionId ) const{
    boost::mutex::scoped_lock locker( m_Mutex );
	
	// Поищем для начала...
    ActionHandlerContMapCIter it_f = m_AllActions.constFind( InModuleId );
    if( it_f == m_AllActions.end() )
		return false;
	
	const ActionHandlerCont& cont_for_module = it_f.value();
	ActionHandlerContCIter it = cont_for_module.begin();
	
	for( ; it != cont_for_module.end(); it++ ){
		if( ( *it ).action_id == InActionId ){
			return true;
		}
	}

	return false;
}

//==============================================================================================================//
unsigned int ActionsPool::GetCountActions( const QString& InModuleId ) const{
    boost::mutex::scoped_lock locker( m_Mutex );
	
    ActionHandlerContMapCIter it_f = m_AllActions.constFind( InModuleId );
    if( it_f == m_AllActions.end() )
		return 0;
	
	return it_f.value().size();
}

//==============================================================================================================//
const QAction* ActionsPool::GetActionByIndex( const QString& InModuleId, unsigned int InIndex ) const{
    boost::mutex::scoped_lock locker( m_Mutex );
	
	// Поищем для начала...
    ActionHandlerContMapCIter it_f = m_AllActions.constFind( InModuleId );
    if( it_f == m_AllActions.end() )
        return 0;
	
	const ActionHandlerCont& cont_for_module = it_f.value();
	ActionHandlerContCIter it = cont_for_module.begin();
	
	unsigned int indx = 0;
	for( ; it != cont_for_module.end(); it++, indx++ ){
		if( indx == InIndex ){
			return ( *it ).action;
		}
	}
	
	return 0;
}

//==============================================================================================================//
const QAction* ActionsPool::GetActionById( const QString& InModuleId, const QString& InActionId ) const{
    boost::mutex::scoped_lock locker( m_Mutex );
	
	// Поищем для начала...
    ActionHandlerContMapCIter it_f = m_AllActions.constFind( InModuleId );
    if( it_f == m_AllActions.end() )
		return 0;
	
	const ActionHandlerCont& cont_for_module = it_f.value();
	ActionHandlerContCIter it = cont_for_module.begin();
	
	for( ; it != cont_for_module.end(); it++ ){
		if( ( *it ).action_id == InActionId ){
			return ( *it ).action;
		}
	}
	
	return 0;
}
//==============================================================================================================//
