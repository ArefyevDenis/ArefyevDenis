#include "q_qmenu.h"

#include "common/logger.h"

Q_QMenu::Q_QMenu(QWidget *parent) :
    QMenu (parent)
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

Q_QMenu::Q_QMenu(const QString &title, QWidget *parent) :
    QMenu (parent)
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

Q_QMenu::~Q_QMenu()
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}
