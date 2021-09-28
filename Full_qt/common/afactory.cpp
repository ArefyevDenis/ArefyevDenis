#include "afactory.h"

namespace  {
 std::map<std::string, QObject*> map_obj;
 std::map<std::string, QObject*> map_crate;
}

int AFactory::count{0};

std::map<std::string, int> AFactory::str_int;

std::map<std::string, std::function< std::unique_ptr<QObject>()>> AFactory::map_crt;

AFactory::AFactory()
{
 LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

AFactory::~AFactory()
{
 LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

AFactory& AFactory::instance(){
    static AFactory af;
    return af;
}


class QQ :
        public QObject
{
public:
    QQ (QObject* parent = nullptr) :
    QObject(parent)
    {
        LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
    }

    ~QQ()
    {
        LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
    }
};


QQ* p1 = crt_obj<QQ>();

QObject* p2 = AFactory::crt_obj<QQ>();

bool b1 = AFactory::register_type<QQ>("1");
bool b2 = AFactory::register_type<QQ>("2");
bool b3 = AFactory::register_type<QQ>("3");
bool b4 = AFactory::register_type<QQ>("4");
bool b5 = AFactory::register_type<QQ>("5");
bool b6 = AFactory::register_type<QQ>("6");
bool b7 = AFactory::register_type<QQ>("7");
