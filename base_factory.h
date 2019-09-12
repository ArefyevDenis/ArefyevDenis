#ifndef BASE_FACTORY_H
#define BASE_FACTORY_H

#include <map>
#include <string>
//#include <QObject>

class Base_factory //: public QObject
{
       // Q_OBJECT
public:
  Base_factory(/*QObject* p=nullptr*/)         ;
  Base_factory(const Base_factory&)                 = delete;
  Base_factory(Base_factory&& )                     = delete;
  Base_factory& operator = (const Base_factory& )   = delete;
  Base_factory& operator = (Base_factory&& )        = delete;
  virtual ~Base_factory()                           ;

  virtual void b_apply(void *) = 0;              ///применять, использовать
  virtual void b_start(void *) = 0;              ///
  virtual void b_stop(void *) = 0;               ///

  virtual const char* b_type_name()  = 0;

  static void set_obj(std::pair<std::string, Base_factory *> );

  static std::map<std::string, Base_factory *> map_obj;

};


#endif // BASE_FACTORY_H
