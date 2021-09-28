#include "derived/core_application.h"
#include "widgets/main_window.h"

#include <qbytearray.h>
#include <common/signal_handler.h>
#include "common/afactory.h"
#include "gapplication.h"

#include <exception>
#include <QSystemSemaphore>
#include <QSharedMemory>
#include <QMessageBox>

QCoreApplication* create_application(int& argc, char* argv[] ) {
    for (int i=1; i<argc; ++i) {
        if(!qstrcmp(argv[i],"-no-gui")){
            return new Core_application<QApplication>(argc,argv);
        }
        return new Core_application<QApplication>(argc,argv);
    }
}

int main(int argc, char *argv[])
{

    try {
        GApplication gap(argc,argv);

       // int* ppp; //= (int*)0x04000000;
       // std::cout << '['<< *ppp << "]\n";

//        QSystemSemaphore sem("app_1",1);
//        sem.acquire();
//        QSharedMemory shm("app_2");
//        bool is_runing;

//        if(shm.attach()){
//            is_runing = true;
//        }else{
//            shm.create(1);
//            is_runing = false;
//        }
//        sem.release();

//        if(is_runing){
//            QMessageBox qbm;
//            qbm.setIcon(QMessageBox::Warning);
//            qbm.setText(QObject::trUtf8("Внимание приложение уже запущено второй экземпляр блокируется"));
//            qbm.exec();
//            return 1;
//        }

        gap.exec();
    } catch (...) {
        LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
    }

    return 0;

}



//   Core_application<QApplication> app(argc, argv);
//   Main_window mw;
//   mw.showMaximized();
//   app.start();
//   return 0;
//    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);

//    /*std::unique_ptr<QObject*>*/ auto ptr = AFactory::create_object("1");

//    QApplication a(argc, argv);
//    Main_window mw;
//    mw.showMaximized();
//    Signal_handler sa;
//    return a.exec();
