#include "unique_app.h"

#include <QMessageBox>
#include <QByteArray>
#include <QCryptographicHash>
#include <iostream>

#include <common/logger.h>

class Non_unique :
        std::exception
{
public:
    explicit Non_unique()
    { LOG_DEBUG(nullptr,__PRETTY_FUNCTION__); }
    ~Non_unique() override
    { LOG_DEBUG(nullptr,__PRETTY_FUNCTION__); }

    const char*   what() const noexcept override
    {
        std::cout << " non unique app \n";
    }
};

namespace  {

    QString generate_key_hash(QString& key, QString& salt){
            QByteArray data;
            data.append(key.toUtf8());
            data.append(salt.toUtf8());
            data = QCryptographicHash::hash(data,QCryptographicHash::Sha1 ).toHex();
            return data;
    }

}

Unique_app::Unique_app(QObject *parent)
   : QObject(parent)
   ,mSem("app_1",1)
   ,mShm("app_2")
{
    //mSem = new QSystemSemaphore("app_1",1);
    mSem.acquire();
    //mShm = new QSharedMemory("app_2");
    bool is_runing;

    if(mShm.attach()){
        is_runing = true;
    }else{
        mShm.create(1);
        is_runing = false;
    }
    mSem.release();

    if(is_runing){
        QMessageBox qbm;
        qbm.setIcon(QMessageBox::Warning);
        qbm.setText(QObject::trUtf8("Внимание приложение уже запущено второй экземпляр блокируется"));
        qbm.exec();
        throw Non_unique();
    }
}

Unique_app::~Unique_app()
{
//    if(mSem!=nullptr)
//        delete mSem;
//    if(mShm!=nullptr)
//        delete mShm;
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}
