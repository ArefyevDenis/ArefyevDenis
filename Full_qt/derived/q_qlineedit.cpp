#include "q_qlineedit.h"

#include "common/logger.h"

Q_QLineEdit:: Q_QLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

Q_QLineEdit:: Q_QLineEdit(const QString &text, QWidget *parent) :
    QLineEdit(text,parent)
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

Q_QLineEdit::~Q_QLineEdit()
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}
