#ifndef AFACTORY_H
#define AFACTORY_H

#include <QObject>

#include <map>
#include <memory>
#include <string>

#include <common/logger.h>
#include<functional>

extern std::map<std::string, QObject*> map_obj;

#define a_inst() AFactory::instance()

class AFactory
{
public:

    static AFactory& instance();

    ~AFactory();

    template<typename TT>
    static QObject* crt_obj(){
        LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
        return new TT();
    }

    template<typename TT>
    static bool register_type(std::string str){
        LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
        try {
            map_crt[str] = []() -> std::unique_ptr<QObject> { return std::make_unique<TT>(); };
            ++count;
            return true;
        } catch (...) {

        }
        return false;
    }

    //template<typename TT>
    static QObject* create_object(std::string str){
        QObject *ptr{nullptr};
        try {
//            for(auto kvp : map_crt){
//                kvp.second();
//            }
            /// необходимо возвращать std::unique_ptr<QObject>
            ptr = map_crt.at(str)().get();
        } catch (...) {
            return nullptr;
        }
        return ptr ;
    }

private:

    AFactory();

    static int count;

    static std::map<std::string, std::function<std::unique_ptr<QObject>()>> map_crt;

    static std::map<std::string, int> str_int;

};


template<typename TT>
TT* crt_obj(){
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
    return new TT();
}

template<typename TT>
bool reg_cre(){
       a_inst();
}




#define REGISTER_TYPE(name)



//        for(auto kvp : map_crt){
//            kvp.second();
//        }

#endif // AFACTORY_H
