#ifndef FACTORY_MORF_H
#define FACTORY_MORF_H

#include <map>

class Base_factory;

extern std::map<std::string,  Base_factory *(*)()> *_iserialize_builders;
typedef Base_factory*(*CREATOR_FUNC)();

class Factory_Morf{
public:
  Factory_Morf()                                  = default;
  Factory_Morf(const Factory_Morf&)               = delete;
  Factory_Morf(Factory_Morf&& )                   = delete;
  Factory_Morf& operator = (const Factory_Morf& ) = delete;
  Factory_Morf& operator = (Factory_Morf&& )      = delete;
  ~Factory_Morf()                              ;

    /**
    * Ставит строку в соответствие функции создающей объект
    * @param name си строка
    * @param creator указатель на функцию создающую объект
    * @return true если с этим именем прежде не было ассоциаций
    */
    bool set(const char *name, Base_factory *(*creator)());
    /**
    * Возвращает указатель на объект созданный в соответствии с
    * указанным названием
    * @param name название
    * @return указатель насозданный объект, 0 если с названием
    * не была ассоциирована функция
    */
    Base_factory *create(const char *name);
    CREATOR_FUNC getCreator(const char *name);
};

#define REGISTER_SERIAL(B, C) B* create_##C(){/* std::cout << __PRETTY_FUNCTION__ << '\n';*/ return new C(); } static bool _trick##C = Factory_Morf().set(#C, create_##C);
#define REGISTER_SERIALIZABLE(C) REGISTER_SERIAL(Base_factory, C)


#endif // FACTORY_MORF_H
