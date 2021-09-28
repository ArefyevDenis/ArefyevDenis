#ifndef CFACTORY_H
#define CFACTORY_H

class Object;

class Object_Factory
{
public:

    Object_Factory();

    virtual Object* create() = 0;

};

//template<typename TT>
//class klass :
//        public Object_Factory
//{
//public:
//    klass()
//    {

//    }

//    virtual Object* create()
//    {
//        new TT();
//    }
//};

//
#endif // CFACTORY_H
