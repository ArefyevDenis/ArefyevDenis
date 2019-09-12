#include "joystick.h"

#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

Joystick::Joystick(QObject *parent)
   : QObject(parent)
{
    auto file = new QFile();
    file->setFileName(fileName);
    if( !file->exists() ){
        qWarning("file does not exist");
        return;
    }

    fd = open(fileName.toUtf8().data(), O_RDONLY|O_NONBLOCK);
    if( fd==-1 ){
        qWarning("can not open file");
        return;
    }

    notifier = new QSocketNotifier( fd,
                                    QSocketNotifier::Read,
                                    this);

    connect( notifier,
             &QSocketNotifier::activated,
             this,
             &Joystick::handle_readNotification );
}

Joystick::~Joystick()
{
    if( fd>=0 ){
        close(fd);
    }
}

void Joystick::handle_readNotification(int /*socket*/)
{
    struct js_event buf;
    while( read(fd,&buf,sizeof(buf))>0 ){
        switch (buf.type) {
        case JS_EVENT_BUTTON:
            emit buttonPressed(buf.number, buf.value);
            break;
        case JS_EVENT_AXIS:
            emit axisMoved(buf.number, buf.value);
            break;
        }
    }
}
