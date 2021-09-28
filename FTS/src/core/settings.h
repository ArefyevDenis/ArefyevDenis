
#pragma once 

#include <QtCore/QSettings>
#include <QtCore/QString>

#include "../../include/ifaces/main/settings_iface.h"

//==============================================================================================================//

/**
 * @brief Класс управления параметрами конфигурации
 **/
class Settings: public FTS::Ifaces::ISettings,
				public QSettings
{
public:
    Settings( const QString& InConfigFileNameWithoutDotAndExt,
              const QString& InConfigFileNameExt,
              const QString& InPathToAllConfigsOrArguments
              );
    ~Settings( void );

//--- FTS::Ifaces::ISettings
public:

    /**
     * @brief Получить список всех ключевых полей
     *
     * @param  ...
     * @return QStringList
     **/
    QStringList	CALL_CONVERSION AllKeys( void ) const;
	
    /**
     * @brief Применить префикс для текущей группы
     *
     * @param InPrefix префикс
     * @return void
     **/
    void CALL_CONVERSION BeginGroup( const QString& InPrefix );
	
    /**
     * @brief Добавить префикс для текущей группы и запустить процесс вычитки данных из массива
     *
     * @param InPrefix превикс
     * @return int - размер массива
     **/
    int	CALL_CONVERSION	BeginReadArray( const QString& InPrefix );
	
    /**
     * @brief Добавить префикс для текущей группы и запустить процесс записи данных в массив
     *
     * @param InPrefix превикс
     * @param InSize индекс прироста позиции записи (по умолчанию инкрементируется на 1)
     * @return void
     **/
    void CALL_CONVERSION BeginWriteArray( const QString& InPrefix, int InSize );
	
    /**
     * @brief Получить список групп верхнего уровня (секций по сути)
     *
     * @param  ...
     * @return QStringList
     **/
    QStringList CALL_CONVERSION ChildGroups( void ) const;
	
    /**
     * @brief Получить список всех ключей
     *
     * @param  ...
     * @return QStringList
     **/
    QStringList	CALL_CONVERSION	ChildKeys( void ) const;
	
    /**
     * @brief Очистить все данные
     *
     * @param  ...
     * @return void
     **/
    void CALL_CONVERSION Clear( void );
	
    /**
     * @brief Проверить наличие ключа в объекте конфигурации
     *
     * @param InKey ...
     * @return bool
     **/
    bool CALL_CONVERSION Contains( const QString& InKey ) const;

    /**
     * @brief Закрыть массив, который был открыт одним из методов BeginReadArray или BeginWriteArray
     *
     * @param  ...
     * @return void
     **/
    void CALL_CONVERSION EndArray( void );
	
    /**
     * @brief Закрыть группу, которая была открыта методом BeginGroup
     *
     * @param  ...
     * @return void
     **/
    void CALL_CONVERSION EndGroup( void );
	
    /**
     * @brief Установить индекс текущей позиции в массиве
     *
     * @param InIndex индекс для установки текущей позации в массиве
     * @return void
     **/
    void CALL_CONVERSION SetArrayIndex( int InIndex );

    /**
     * @brief Получить наименование текущей группы
     *
     * @param  ...
     * @return QString
     **/
    QString CALL_CONVERSION Group( void ) const;

    /**
     * @brief Получить признак, возможна ли запись данных в объект конфигурации
     *
     * @param  ...
     * @return bool
     **/
    bool CALL_CONVERSION IsWritable( void ) const;

    /**
     * @brief Удалить данные ключа
     *
     * @param InKey ключ
     * @return void
     **/
    void CALL_CONVERSION Remove( const QString& InKey );

    /**
     * @brief Установить значение
     *
     * @param InKey ключ
     * @param InValue значение
     * @return void
     **/
    void CALL_CONVERSION SetValue( const QString& InKey, const QVariant& InValue );

    /**
     * @brief Получить статус
     *
     * @param  ...
     * @return QSettings::Status
     **/
    QSettings::Status CALL_CONVERSION GetStatus( void ) const;

    /**
     * @brief Принудительно записать все ранее несохраненные данные в файл
     *
     * @param  ...
     * @return void
     **/
    void CALL_CONVERSION Sync( void );

    /**
     * @brief Получить значение по ключу
     *
     * @param InKey ключ
     * @param InDefaultValue ... Defaults to QVariant().
     * @return QVariant
     **/
    QVariant CALL_CONVERSION Value( const QString& InKey, const QVariant& InDefaultValue ) const;
	
    /**
     * @brief Получить путь ко всем файлам конфигурации или аргументов
     *
     * @param  ...
     * @return const QString
     **/
    const QString CALL_CONVERSION GetPathToAllConfigsOrArguments( void ) const;
	
private:

    QSettings* m_pBaseSettings;
    const QString m_PathToAllConfigsOrArguments;   //Путь ко всем файлам конфигурации или аргументов
	
};
//==============================================================================================================//
