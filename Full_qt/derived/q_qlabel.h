#ifndef Q_QLABEL_H
#define Q_QLABEL_H

#include <QLabel>

class Q_QLabel :
        public QLabel
{
    Q_OBJECT
public:
    explicit Q_QLabel(QWidget *parent=nullptr);

    explicit Q_QLabel(const QString &text, QWidget *parent=nullptr);

    ~Q_QLabel();

signals:

public slots:
};

#endif // Q_QLABEL_H
