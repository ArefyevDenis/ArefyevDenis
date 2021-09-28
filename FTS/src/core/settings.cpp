
#include <assert.h>
#include <iostream>
#include <QtCore/QStringList>
#include <QtCore/QTextCodec>
#include <QFile>

#include "settings.h"

//==============================================================================================================//
Settings::Settings(const QString& InConfigFileNameWithoutDotAndExt,
                    const QString& InConfigFileNameExt,
                    const QString& InPathToAllConfigsOrArguments ):
        m_pBaseSettings( 0 ),
        m_PathToAllConfigsOrArguments( InPathToAllConfigsOrArguments ){

    QString file_name_to_change_manual( QString( "%1.%2" ).arg( InConfigFileNameWithoutDotAndExt ).arg( InConfigFileNameExt ) );

    m_pBaseSettings = new QSettings(file_name_to_change_manual, QSettings::IniFormat);

    m_pBaseSettings->setIniCodec( "UTF-8" );
}

//==============================================================================================================//
Settings::~Settings( void ){
    if( m_pBaseSettings ){
        delete m_pBaseSettings;
        m_pBaseSettings = 0;
    }
}

//==============================================================================================================//
QStringList CALL_CONVERSION Settings::AllKeys( void ) const{
    assert( m_pBaseSettings );
    return m_pBaseSettings->allKeys();
}

//==============================================================================================================//
void CALL_CONVERSION Settings::BeginGroup( const QString& InPrefix ){
    assert( m_pBaseSettings );
    return m_pBaseSettings->beginGroup( InPrefix );
}

//==============================================================================================================//
int CALL_CONVERSION Settings::BeginReadArray( const QString& InPrefix ){
    assert( m_pBaseSettings );
    return m_pBaseSettings->beginReadArray( InPrefix );
}

//==============================================================================================================//
void CALL_CONVERSION Settings::BeginWriteArray( const QString& InPrefix, int InSize ){
    assert( m_pBaseSettings );
    m_pBaseSettings->beginWriteArray( InPrefix, InSize );
}

//==============================================================================================================//
QStringList	CALL_CONVERSION Settings::ChildGroups( void ) const{
    assert( m_pBaseSettings );
    return m_pBaseSettings->childGroups();
}

//==============================================================================================================//
QStringList	CALL_CONVERSION	Settings::ChildKeys( void ) const{
    assert( m_pBaseSettings );
    return m_pBaseSettings->childKeys();
}

//==============================================================================================================//
void CALL_CONVERSION Settings::Clear( void ){
    assert( m_pBaseSettings );
    m_pBaseSettings->clear();
}

//==============================================================================================================//
bool CALL_CONVERSION Settings::Contains( const QString& InKey ) const{
    assert( m_pBaseSettings );
    return m_pBaseSettings->contains( InKey );
}

//==============================================================================================================//
void CALL_CONVERSION Settings::EndArray( void ){
    assert( m_pBaseSettings );
    m_pBaseSettings->endArray();
}

//==============================================================================================================//
void CALL_CONVERSION Settings::EndGroup( void ){
    assert( m_pBaseSettings );
    m_pBaseSettings->endGroup();
}

//==============================================================================================================//
void CALL_CONVERSION Settings::SetArrayIndex( int InIndex ){
    assert( m_pBaseSettings );
    m_pBaseSettings->setArrayIndex( InIndex );
}

//==============================================================================================================//
QString	CALL_CONVERSION Settings::Group( void ) const{
    assert( m_pBaseSettings );
    return m_pBaseSettings->group();
}

//==============================================================================================================//
bool CALL_CONVERSION Settings::IsWritable( void ) const{
    assert( m_pBaseSettings );
    return m_pBaseSettings->isWritable();
}

//==============================================================================================================//
void CALL_CONVERSION Settings::Remove( const QString& InKey ){
    assert( m_pBaseSettings );
    m_pBaseSettings->remove( InKey );
}

//==============================================================================================================//
void CALL_CONVERSION Settings::SetValue( const QString& InKey, const QVariant& InValue ){
    assert( m_pBaseSettings );
    m_pBaseSettings->setValue( InKey, InValue );
}

//==============================================================================================================//
QSettings::Status CALL_CONVERSION Settings::GetStatus( void ) const{
    assert( m_pBaseSettings );
    return m_pBaseSettings->status();
}

//==============================================================================================================//
void CALL_CONVERSION Settings::Sync( void ){
    assert( m_pBaseSettings );
    return m_pBaseSettings->sync();
}

//==============================================================================================================//
QVariant CALL_CONVERSION Settings::Value( const QString& InKey, const QVariant& InDefaultValue ) const{
    assert( m_pBaseSettings );
    return m_pBaseSettings->value( InKey, InDefaultValue );
}

//==============================================================================================================//
const QString CALL_CONVERSION	Settings::GetPathToAllConfigsOrArguments( void ) const{
    return m_PathToAllConfigsOrArguments;
}

//==============================================================================================================//
