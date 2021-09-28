#pragma once 

class QString;
class QWidget;
class IVideoDataBuffer;

//-----------------------------------------------------------------------------
/**
 * @brief Интерфейс для отображения видеоинформации
 **/
class IVideoWidget
{
public:
	/**
	 * @brief Установить параметры видео
	 *
	 * @param InWidth ширина видеокартинки
	 * @param InVideoHeight высота видеокартинки
	 * @return void
	 **/
	virtual void SetVideoParameters( unsigned int InWidth, unsigned int InHeight ) = 0;
	
	/**
	 * @brief Установить данные для отображения
	 *
	 * @param InData данные
	 * @return void
	 **/
	virtual void SetData( IVideoDataBuffer* InData ) = 0;
	
	/**
	 * @brief Установить строку ошибки
	 *
	 * @param InErrorString строка с описанием ошибки
	 * @return void
	 **/
	virtual void SetErrorString(	const QString& InErrorString ) = 0;
	
	/**
	 * @brief Вернуть признак необходимости обновления данных
	 * \remarks Необходимо внимательно подойти к реализации данного метода, поскольку
	 * он используется для определения необходимости декодирования информации в режиме "Play"
	 * Необходимо осуществить проверку на основании параметра FPS, загруженного из конфигурации
	 *
	 * @param  ...
	 * @return bool
	 **/
	virtual bool IsNeedUpdate( void ) const = 0;
	
	/**
	 * @brief Уведомление виджета о том, что он присоединен к некому источнику видеоинформации
	 *
	 * @param  ...
	 * @return void
	 **/
	virtual void Attached( void ) = 0;
	
	/**
	 * @brief Уведомление виджета о том, что он отсоединен от некого источника видеоинформации
	 *
	 * @param  ...
	 * @return void
	 **/
	virtual void Detached( void ) = 0;
	
	/**
	 * @brief Проверить, присоединен ли виджет к источнику видеоинформации
	 *
	 * @param  ...
	 * @return bool
	 **/
	virtual bool IsAttached( void ) const = 0;
	
	/**
	 * @brief Получить виджет для отрисовки
	 *
	 * @param  ...
	 * @return QWidget*
	 **/
	virtual QWidget* GetWidget( void ) = 0;

};
//-----------------------------------------------------------------------------