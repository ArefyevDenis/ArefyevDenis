#ifndef CORE_APPLICATION_H
#define CORE_APPLICATION_H

#include <iostream>
#include <QCoreApplication>
#include <QApplication>

#include "common/logger.h"

template<typename TT>
class Core_application :
        public TT
{
   // Q_OBJECT шаблонные классы не поддерживаю
public:
    Core_application(int argc, char* argv[]) try :
        TT(argc,argv),
        argc_(argc),
        argv_(argv)
    {
        LOG_DEBUG(NULL,__PRETTY_FUNCTION__);
    } catch (std::exception &ex) {
        LOG_DEBUG(NULL,__PRETTY_FUNCTION__);
        std::terminate();
    }

    bool event(QEvent *evt) override {
        LOG_DEBUG(NULL,__PRETTY_FUNCTION__);
        return TT::event(evt);
    }

    void start(){
        LOG_DEBUG(NULL,__PRETTY_FUNCTION__);
        TT::exec();
    }
    void stop(){
        LOG_DEBUG(NULL,__PRETTY_FUNCTION__);
        TT::exit();
    }

    ~Core_application() override {
        LOG_DEBUG(NULL,__PRETTY_FUNCTION__);
    }

private:
    int argc_;
    char** argv_;

signals:

public slots:

};
#endif // CORE_APPLICATION_H
