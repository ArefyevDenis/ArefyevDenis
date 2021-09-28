#ifndef BASE_HANDLER_H
#define BASE_HANDLER_H

//#include <QObject>
class QNetworkDatagram;

class Base_handler //:  public QObject
{
   //Q_OBJECT
public:
    explicit Base_handler(/*QObject *parent = nullptr*/);

    virtual~Base_handler();// override;

    virtual void  operator()(QNetworkDatagram&) = 0;

//signals:
//public slots:

};

#endif // BASE_HANDLER_H
