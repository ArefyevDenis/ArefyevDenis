#ifndef Q_QMENUBAR_H
#define Q_QMENUBAR_H

#include <QMenuBar>

class Q_QMenuBar :
        public QMenuBar
{
    Q_OBJECT
public:
    explicit Q_QMenuBar(QWidget *parent = nullptr);

    ~Q_QMenuBar() override ;

signals:

public slots:

};

#endif // Q_QMENUBAR_H
