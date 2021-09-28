#ifndef FACTORY_H
#define FACTORY_H

#include <dbg.h>

#include <map>
#include <string>
#include <cxxabi.h>

//class QObject;

#define class_instance( name ) static FACT::Instancer<name,QObject> class_##name

namespace FACT {

  template <class BT>
  class CCreator
  {
  public:
      CCreator()                          {  who();  }
      virtual ~CCreator()                 {  who();  }
      virtual BT* Create()       {  who();  }
  };

  template<class BT>
  class Factory
  {
  public:

    Factory()
    {
      who();
    }

    static std::map<std::string,CCreator<BT>*> map_crt;

    static void rgg(std::string key ,CCreator<BT>* fn)
    {
      int status{0};  const char* ccc = abi::__cxa_demangle(typeid(map_crt).name() ,0,0,&status);      LOG(ccc);
      ccc = abi::__cxa_demangle(typeid(fn).name() ,0,0,&status);           LOG(ccc);
      map_crt[key] = fn;//        LOG(key);
      //if(map_crt.empty()){}
      //map_crt.insert({key,fn});
    }

    static BT* crt(std::string key)
    {
      return map_crt[key]->Create();
    }

  };

  template<class BT>
  std::map<std::string,CCreator<BT>*> Factory<BT>::map_crt;

  template<class TT,class BT>
  class Instancer :
      public CCreator<BT>
  {
  public:
    Instancer()
    {
      int status{0};  const char* ccc = abi::__cxa_demangle(typeid(TT).name() ,0,0,&status);
      LOG(ccc);
      Factory<BT>::rgg(ccc,this);
    }

    ~Instancer() override
    {  who();  }

    BT* Create() override
    {
      return new TT();
    }

  };
}



























//#define class_instance( name ) FACT::Instancer<name,QObject> class_##name;

//namespace FACT {

//  template <class BT>
//  class CCreator
//  {
//  public:
//      CCreator()                          {  who();  }
//      virtual ~CCreator()                 {  who();  }
//      virtual BT* Create(QObject*parent)  {  who();  }
//  };

//  template<class BT>
//  class Factory
//  {
//  public:

//    Factory()
//    {
//      who();
//    }

//    static std::map<std::string,CCreator<BT>*> map_crt;

//    static void rgg(std::string key ,CCreator<BT>* fn)
//    {
//        map_crt[key] = fn;        LOG(key);
//    }

//    static BT* crt(QObject* parent, std::string key)
//    {
//      return map_crt[key]->Create(parent);
//    }

//  };

//  template<class BT>
//  std::map<std::string,CCreator<BT>*> Factory<BT>::map_crt;

//  template<class TT,class BT>
//  class Instancer :
//      public CCreator<BT>
//  {
//  public:
//    Instancer()
//    {
//      int status{0};  const char* ccc = abi::__cxa_demangle(typeid(TT).name() ,0,0,&status);
//      LOG(ccc);
//      Factory<BT>::rgg(ccc,this);
//    }

//    ~Instancer() override
//    {  who();  }

//    BT* Create(QObject* parent) override
//    {
//      return new TT(parent);
//    }

//   // TT tt;
//  };

//}



#endif // FACTORY_H
