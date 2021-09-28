
#pragma once 

#include <QtCore/QSettings>
#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{

class ISettings
{
public:

    /**
     * @brief Получить список всех ключевых полей
     *
     * @param  ...
     * @return QStringList
     **/
    virtual QStringList	CALL_CONVERSION	AllKeys( void ) const = 0;
	
    /**
     * @brief Применить префикс для текущей группы
     *
     * @param InPrefix префикс
     * @return void
     **/
    virtual void CALL_CONVERSION BeginGroup( const QString& InPrefix ) = 0;
	
    /**
     * @brief Добавить префикс для текущей группы и запустить процесс вычитки данных из массива
     *
     * @param InPrefix превикс
     * @return int - размер массива
     **/
    virtual int	CALL_CONVERSION BeginReadArray( const QString& InPrefix ) = 0;
	
    /**
     * @brief Добавить префикс для текущей группы и запустить процесс записи данных в массив
     *
     * @param InPrefix превикс
     * @param InSize индекс прироста позиции записи (по умолчанию инкрементируется на 1)
     * @return void
     **/
    virtual void CALL_CONVERSION BeginWriteArray( const QString& InPrefix, int InSize = -1 ) = 0;
	
    /**
     * @brief Получить список групп верхнего уровня (секций по сути)
     *
     * @param  ...
     * @return QStringList
     **/
    virtual QStringList CALL_CONVERSION	ChildGroups( void ) const = 0;
	
    /**
     * @brief Получить список всех ключей
     *
     * @param  ...
     * @return QStringList
     **/
    virtual QStringList	CALL_CONVERSION ChildKeys( void ) const = 0;
	
    /**
     * @brief Очистить все данные
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Clear( void ) = 0;
	
    /**
     * @brief Проверить наличие ключа в объекте конфигурации
     *
     * @param InKey ...
     * @return bool
     **/
    virtual bool CALL_CONVERSION Contains( const QString& InKey ) const = 0;

    /**
     * @brief Закрыть массив, который был открыт одним из методов BeginReadArray или BeginWriteArray
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION EndArray( void ) = 0;
	
    /**
     * @brief Закрыть группу, которая была открыта методом BeginGroup
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION EndGroup( void ) = 0;

   /**
     * @brief Установить индекс текущей позиции в массиве
     *
     * @param InIndex индекс для установки текущей позации в массиве
     * @return void
     **/
    virtual void CALL_CONVERSION SetArrayIndex( int InIndex ) = 0;
	
    /**
     * @brief Получить наименование текущей группы
     *
     * @param  ...
     * @return QString
     **/
    virtual QString CALL_CONVERSION Group( void ) const = 0;

    /**
     * @brief Получить признак, возможна ли запись данных в объект конфигурации
     *
     * @param  ...
     * @return bool
     **/
    virtual bool CALL_CONVERSION IsWritable( void ) const = 0;

    /**
     * @brief Удалить данные ключа
     *
     * @param InKey ключ
     * @return void
     **/
    virtual void CALL_CONVERSION Remove( const QString& InKey ) = 0;

    /**
     * @brief Установить значение
     *
     * @param InKey ключ
     * @param InValue значение
     * @return void
     **/
    virtual void CALL_CONVERSION SetValue( const QString& InKey, const QVariant& InValue ) = 0;

    /**
     * @brief Получить статус
     *
     * @param  ...
     * @return QSettings::Status
     **/
    virtual QSettings::Status CALL_CONVERSION GetStatus( void ) const = 0;

    /**
     * @brief Принудительно записать все ранее несохраненные данные в файл
     *
     * @param  ...
     * @return void
     **/
    virtual void CALL_CONVERSION Sync( void ) = 0;

    /**
     * @brief Получить значение по ключу
     *
     * @param InKey ключ
     * @param InDefaultValue ... Defaults to QVariant().
     * @return QVariant
     **/
    virtual QVariant CALL_CONVERSION Value( const QString& InKey, const QVariant& InDefaultValue = QVariant() ) const = 0;

    /**
     * @brief Получить путь ко всем файлам конфигурации или аргументов
     *
     * @param  ...
     * @return const QString
     **/
    virtual const QString CALL_CONVERSION GetPathToAllConfigsOrArguments( void ) const = 0;
	
};

	};
};
