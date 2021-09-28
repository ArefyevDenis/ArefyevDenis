
#pragma once 

#pragma pack( push, 4 )

#include <vector>
#include <memory.h>

namespace FTS{
	namespace Const{
		/**
		 * @brief Константа - размер строки ключей (в байтах)
		 **/
		const unsigned int 		SIZE_KEY_STRING			= 32;

		/**
		 * @brief Константа - размер короткой строки (в байтах)
		 **/
		const unsigned int 		SIZE_SHORT_STRING		= 128;
		
		/**
		 * @brief Константа - размер полной строки (в байтах)
		 **/
		const unsigned int 		SIZE_FULL_STRING		= 2048;
	}; // end namespace Const
	
	namespace ModuleTypes{
		
		/**
		 * @brief Тип модуля - работа с оборудованием ("железом")
		 **/
		const unsigned int 		HARD 			= 0x1;
		/**
		 * @brief Тип модуля - сервисный модуль
		 **/
		const unsigned int 		SERVICE 		= 0x2;
		/**
		 * @brief Тип модуля - взаимодействие с пользователем
		 **/
		const unsigned int 		GUI 			= 0x4;
		/**
		 * @brief Тип модуля - обработка данных
		 **/
		const unsigned int 		DATA_PROCESS 	= 0x8;
		/**
		 * @brief Тип модуля с поддержкой ВСК
		 **/
		const unsigned int 		ISC			 	= 0x16;
		
	}; // end namespace ModuleTypes
	
	namespace BasesTypes{
		/**
		* @brief Тип данных - короткая строка
		**/
		typedef struct _DummyShortString
		{
			char Data[ Const::SIZE_SHORT_STRING ];
			
			_DummyShortString()
			{
				memset( this, 0, sizeof( *this ) );
			}
		} ShortString;
		
		/**
		* @brief Тип данных - длинная строка
		**/
		typedef struct _DummyFullString
		{
			char Data[ Const::SIZE_FULL_STRING ];
			
			_DummyFullString()
			{
				memset( this, 0, sizeof( *this ) );
			}
		} FullString;
		
		/**
		* @brief Тип данных - строка ключа
		**/
		typedef struct _DummyKeyString
		{
			char Data[ Const::SIZE_KEY_STRING ];
			
			_DummyKeyString()
			{
				memset( this, 0, sizeof( *this ) );
			}
		} KeyString;

		/**
		 * @brief Тип данных - структура с информацией о библиотеке
		 **/
		typedef struct _DummyLibraryInfo
		{
			ShortString		LibraryName;
			ShortString		LibraryVersionInfo;
		} LibraryInfo;
		
		/**
		 * @brief Тип данных - структура с информацией о виджете
		 **/
		typedef struct _DummyWidgetInfo
		{
			ShortString		WidgetId;
			ShortString		WidgetCaption;
			FullString		WidgetDescription;
		} WidgetInfo;		
		
	};
	namespace Containers{
		/**
		* @brief Тип данных - контейнер с информацией о виджетах
		**/
                typedef std::vector< FTS::BasesTypes::WidgetInfo > WidgetInfoCont;
		typedef WidgetInfoCont::iterator WidgetInfoContIter;
		typedef WidgetInfoCont::const_iterator WidgetInfoContCIter;
		
		/**
		 * @brief Тип данных - контейнер со строками длины 32 байта
		 **/
                typedef std::vector< FTS::BasesTypes::KeyString > KeyStringCont;
		typedef KeyStringCont::iterator KeyStringContIter;
		typedef KeyStringCont::const_iterator KeyStringContCIter;
		
		/**
		* @brief Тип данных - контейнер с описанием списка вложенности узлов, к которым принаджлежит параметр ВСК
		**/
                typedef std::vector< FTS::BasesTypes::KeyString > ExportIscParameterCont;
		typedef ExportIscParameterCont::iterator ExportIscParameterContIter;
		typedef ExportIscParameterCont::const_iterator ExportIscParameterContCIter;
	};	// end namespace Containers
	
	namespace BasesTypes{	
		typedef struct _DummyExportInterfaceInfo
		{
			ShortString		InterfaceId;
			unsigned int	MinorVersion;
		} ExportInterfaceInfo;
		
// 		typedef struct _DummyExportIscNode
// 		{
// 			KeyString		NodeIdentifier;
// 		} ExportIscNode;
		
		typedef struct _DummyExportIscParameter
		{
                        FTS::Containers::KeyStringCont			Identifiers;
                        FTS::Containers::ExportIscParameterCont 	ChainNodesForParameter;
                        FTS::BasesTypes::KeyString				Key;
		} ExportIscParameter;
		
		
	};	// end namespace BasesTypes
	
	
	
};	// end namespace FTS

#pragma pack( pop )
