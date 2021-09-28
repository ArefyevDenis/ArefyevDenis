#ifndef ENCAPSULATE_H
#define ENCAPSULATE_H

#include <QObject>

#include <network/udp_multiplexer.h>

class Encapsulate : public QObject
{
    Q_OBJECT
public:
    explicit Encapsulate(QObject *parent = nullptr);
    ~Encapsulate() override;
private:

    Udp_server um_;

signals:

public slots:

};

#endif // ENCAPSULATE_H
