#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <QObject>
#include <initializer_list>

class Signal_handler : public QObject
{
    Q_OBJECT
public:
    explicit Signal_handler(QObject *parent = nullptr);

    explicit Signal_handler(std::initializer_list<int> il);

    ~Signal_handler()override;

private:

    static void exitQt(int sig);

signals:

public slots:

};

#endif // SIGNAL_HANDLER_H
