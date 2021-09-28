#ifndef Q_QMENU_H
#define Q_QMENU_H

#include <QMenu>

class Q_QMenu :
        public QMenu
{
    Q_OBJECT
public:
    explicit Q_QMenu(QWidget *parent = nullptr);

    explicit Q_QMenu(const QString &title, QWidget *parent = nullptr);

    ~Q_QMenu() override ;

signals:

public slots:
};

#endif // Q_QMENU_H
