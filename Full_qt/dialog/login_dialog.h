#ifndef LOGIN_DIALOG_H
#define LOGIN_DIALOG_H

#include <QDialog>

class QAbstractButton;

class Login_dialog :
        public QDialog
{
    Q_OBJECT
public:
    explicit Login_dialog(QWidget *parent = nullptr);

    ~Login_dialog() override ;

signals:

public slots:

    void click_button_box(QAbstractButton*);

};



#endif // LOGIN_DIALOG_H
