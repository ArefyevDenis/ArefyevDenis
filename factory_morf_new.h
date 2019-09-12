#ifndef FACTORY_MORF_NEW_H
#define FACTORY_MORF_NEW_H

#include <map>
#include <memory>
#include <functional>

class Base_factory;

extern std::map<std::string,  Base_factory *(*)()> *_iserialize_builders_new;
extern std::shared_ptr<std::map<std::string, std::function<Base_factory*()>>> sh_map_builders;

typedef Base_factory*(*CREATOR_FUNC)();

class Factory_Morf_new{
public:
  Factory_Morf_new()                                      = default;
  Factory_Morf_new(const Factory_Morf_new&)               = delete;
  Factory_Morf_new(Factory_Morf_new&& )                   = delete;
  Factory_Morf_new& operator = (const Factory_Morf_new& ) = delete;
  Factory_Morf_new& operator = (Factory_Morf_new&& )      = delete;
  ~Factory_Morf_new()                              ;

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

#define REGISTER_SERIAL(B, C) B* create_##C(){ return new C(); } bool _trick##C = Factory_Morf_new().set(#C, create_##C);
#define REGISTER_SERIALIZABLE(C) REGISTER_SERIAL(Base_factory, C)


#endif // FACTORY_MORF_NEW_H
