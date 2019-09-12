#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>
#include <QFile>
#include <QSocketNotifier>

class Joystick
      : public QObject
{
    Q_OBJECT

    QString fileName = "/dev/input/js0";
    QSocketNotifier *notifier;
    int fd;

public:
    explicit Joystick(QObject *parent = nullptr);
    ~Joystick();

signals:
    void buttonPressed(quint8 number, qint16 value);
    void axisMoved(quint8 number, qint16 value);


public slots:
    void handle_readNotification(int socket);
};

#endif // JOYSTICK_H
