#ifndef Q_QLINEEDIT_H
#define Q_QLINEEDIT_H

#include <QLineEdit>

class Q_QLineEdit :
        public QLineEdit
{
    Q_OBJECT
public:
    explicit Q_QLineEdit(QWidget *parent=nullptr);

    explicit Q_QLineEdit(const QString &text, QWidget *parent=nullptr);

    ~Q_QLineEdit();


signals:

public slots:
};

#endif // Q_QLINEEDIT_H
