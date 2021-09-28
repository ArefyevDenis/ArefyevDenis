#include "q_qlabel.h"

#include "common/logger.h"

Q_QLabel:: Q_QLabel(QWidget *parent) :
    QLabel(parent)
{
     LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

Q_QLabel:: Q_QLabel(const QString &text, QWidget *parent) :
    QLabel(text,parent)
{
     LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

Q_QLabel::~Q_QLabel()
{
     LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}
