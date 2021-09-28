#ifndef UNIQUE_APP_H
#define UNIQUE_APP_H

#include <QObject>

class QSystemSemaphore;
class QSharedMemory;

#include <QSystemSemaphore>
#include <QSharedMemory>

class Unique_app :
        public QObject
{
    Q_OBJECT
public:

    explicit Unique_app(QObject *parent = nullptr);

    ~Unique_app()override;

protected:

    QSystemSemaphore    mSem;//{nullptr};
    QSharedMemory       mShm;//{nullptr};

signals:

public slots:

};

#endif // UNIQUE_APP_H
