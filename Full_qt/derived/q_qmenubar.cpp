#include "q_qmenubar.h"

#include "common/logger.h"

Q_QMenuBar::Q_QMenuBar(QWidget *parent) :
    QMenuBar(parent)
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

Q_QMenuBar::~Q_QMenuBar()
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}
