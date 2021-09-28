
#pragma once

namespace FTS{
  namespace Ifaces{
    class IUsageLibraryInfoDescriber;
  }
  namespace Utils{

    /**
 * @brief Класс, инкапсулирующий в себе сбор информации о используемых в проекте библиотеках
 * \remarks Сбор инфоормации производится по инициативе разработчиков, т.е. после явного вызова методов класса
 **/
    class LibrariesInfoSetter
    {
    public:

      LibrariesInfoSetter( FTS::Ifaces::IUsageLibraryInfoDescriber* InDescriber );
      ~LibrariesInfoSetter();

    public:

      /**
     * @brief Модуль использует Qt
     *
     * @param  ...
     * @return bool
     **/
      bool ModuleUsingQt( void );

      /**
     * @brief Модуль использует Boost
     *
     * @param  ...
     * @return bool
     **/
      bool ModuleUsingBoost( void );

      /**
     * @brief Модуль использует Qwt
     *
     * @param  ...
     * @return bool
     **/
      bool ModuleUsingQwt( void );

    private:

      /**
     * @brief Описатель используемых библиоитек
     **/
      FTS::Ifaces::IUsageLibraryInfoDescriber* _Describer;

    };

  };
};
