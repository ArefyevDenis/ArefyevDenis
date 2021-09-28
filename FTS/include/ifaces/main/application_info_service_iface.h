
#pragma once

#include <QString>
#include <QStringList>
#include "../../common/config-win32.h"

namespace FTS{
        namespace Ifaces{

//==============================================================================================================//
/**
 * @brief Интерфейс доступа к сервисной информации о приложении
 **/
class IAppService
{
public:
	
    /**
     * @brief Получить путь к каталогу с исполняемыми файлами приложения
     *
     * @param  ...
     * @return QString
     **/
    virtual QString CALL_CONVERSION GetAppBinaryPath( void ) const = 0;
	
    /**
     * @brief Получить исполняемый файл приложения
     *
     * @param  ...
     * @return QString
     **/
    virtual QString CALL_CONVERSION GetAppExecutName( void ) const = 0;
	
    /**
     * @brief Получить аргументы приложения, с которыми оно было запущено
     *
     * @param  ...
     * @return QStringList
     **/
    virtual QStringList	CALL_CONVERSION GetAppArguments( void ) const = 0;

    /**
     * @brief Получить заголовок приложения
     *
     * @param  ...
     * @return QString
     **/
    virtual QString CALL_CONVERSION GetAppCaption( void ) const = 0;
	
    /**
     * @brief Получить идентификатор процесса приложения
     *
     * @param  ...
     * @return long int
     **/
    virtual qint64 CALL_CONVERSION GetAppPID( void ) const = 0;

    /**
     * @brief Получить путь к временному каталогу для хранения данных приложений, основанных на ядре KilimoOte
     * \remarks Единственным условием, по которосу возвращаемое значение может быть пустой строкой, является
     * отсутствие выставленной системной переменной TMPDIR. Ядро берет на себя ответственность за гарантированное
     * наличие каталога, соответствующего возвращаемому значению из метода
     *
     * @param  ...
     * @return QString
     **/
    virtual QString CALL_CONVERSION GetCoreTempDirectoryPath( void ) const = 0;
	
};
//==============================================================================================================//
        }
};
