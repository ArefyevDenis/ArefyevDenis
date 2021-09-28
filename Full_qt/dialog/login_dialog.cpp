#include "login_dialog.h"

#include "common/logger.h"

#include "derived/q_qlabel.h"
#include "derived/q_qlineedit.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>

Login_dialog::Login_dialog(QWidget *parent) :
    QDialog(parent)
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);

    /// можно без this и так всё удаляется

    auto *vbx = new QVBoxLayout();
    auto *hbx_0 = new QHBoxLayout();
    hbx_0->addWidget(new QLabel(tr("Учетка:")));
    hbx_0->addWidget(new QLineEdit());
    vbx->addLayout(hbx_0);

    auto *hbx_1 = new QHBoxLayout();
    hbx_1->addWidget(new QLabel(tr("Пароль:")));
    hbx_1->addWidget(new QLineEdit());
    vbx->addLayout(hbx_1);

    auto *dbb = new QDialogButtonBox(QDialogButtonBox::Cancel);
    auto *pb_0 = new QPushButton("OK");
    dbb->addButton(pb_0, QDialogButtonBox::AcceptRole);
    connect(dbb,&QDialogButtonBox::clicked,this, &Login_dialog::click_button_box);
    vbx->addWidget(dbb);

    setLayout(vbx);

}

Login_dialog::~Login_dialog()
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

void Login_dialog::click_button_box(QAbstractButton *button){

    if ((dynamic_cast<QDialogButtonBox*>(sender())) == nullptr)
        return;

    auto btn = (dynamic_cast<QDialogButtonBox*>(sender()))->standardButton(button);

    switch (btn) {
    case QDialogButtonBox::Ok:

        break;
    default:
    {
        auto btn2 = (dynamic_cast<QDialogButtonBox*>(sender()))->buttonRole(button);
        switch (btn2)
        {
        case QDialogButtonBox::AcceptRole:

            break;
        default:
            reject();
            break;
        }
    }
        break;
    }
}

