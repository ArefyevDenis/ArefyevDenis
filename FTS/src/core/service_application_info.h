
#pragma once

#include "../../include/ifaces/main/application_info_service_iface.h"

namespace FTS{
        namespace Ifaces{
                class ICoreMainIfaces;
	}
}

//==============================================================================================================//
class ServiceAppInfo: public FTS::Ifaces::IAppService
{
public:
    ServiceAppInfo();
    ~ServiceAppInfo( void );

//--- IAppService
public:

    /**
     * @brief Получить путь к каталогу с исполняемыми файлами приложения
     *
     * @param  ...
     * @return QString
    **/
    QString CALL_CONVERSION GetAppBinaryPath( void ) const;

    /**
     * @brief Получить исполняемый файл приложения
     *
     * @param  ...
     * @return QString
     **/
    QString CALL_CONVERSION GetAppExecutName( void ) const;

    /**
     * @brief Получить аргументы приложения, с которыми оно было запущено
     *
     * @param  ...
     * @return QStringList
     **/
    QStringList CALL_CONVERSION GetAppArguments( void ) const;

    /**
     * @brief Получить заголовок приложения
     *
     * @param  ...
     * @return QString
     **/
    QString CALL_CONVERSION GetAppCaption( void ) const;
	
    /**
     * @brief Получить идентификатор процесса приложения
     *
     * @param  ...
     * @return qint64
     **/
    qint64 CALL_CONVERSION GetAppPID( void ) const;
	
    /**
     * @brief Получить путь к временному каталогу для хранения данных приложений, основанных на ядре FTS
     * \remarks Единственным условием, по которосу возвращаемое значение может быть пустой строкой, является
     * отсутствие выставленной системной переменной TMPDIR. Ядро берет на себя ответственность за гарантированное
     * наличие каталога, соответствующего возвращаемому значению из метода
     *
     * @param  ...
     * @return QString
     **/
    QString CALL_CONVERSION GetCoreTempDirectoryPath( void ) const;
	
private:

    /**
     * @brief Базовый каталог для хранения временных файлов Ядра
     **/
    mutable QString m_CoreTempDirectoryPath;
	
};
//==============================================================================================================//
