#include "tab_widget.h"

#include <QLabel>
#include <QTabWidget>
#include <QHBoxLayout>
#include <iostream>
#include <typeinfo>
#include "common/logger.h"

#include <widgets/tab/table_one.h>
#include <widgets/tab/table_split.h>

Tab_widget::Tab_widget(QWidget *parent) :
    QDockWidget(parent)
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
    init_widgets();
}


Tab_widget::Tab_widget(const QString &title, QWidget *parent) :
    QDockWidget(title, parent)
{
     LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
     init_widgets();
}

Tab_widget::~Tab_widget()
{
     LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

void Tab_widget::init_widgets(){

    //setStyleSheet("border: 1px solid #999999");
    qhl = new QHBoxLayout();
    auto new_tab = new QTabWidget();

    new_tab->addTab(new Table_one(),typeid(Table_one).name());
    new_tab->addTab(new Table_split(),typeid(Table_split).name());

    qhl->addWidget(new_tab);

    auto *newWidget = new QWidget(this);
    newWidget->setLayout(qhl);
    setWidget(newWidget);

}
