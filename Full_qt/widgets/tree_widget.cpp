#include "tree_widget.h"

#include <QTreeWidget>
#include <QHBoxLayout>
#include <iostream>

#include "common/logger.h"

Tree_widget::Tree_widget(QWidget *parent) :
    QDockWidget(parent)
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
    init_widgets();
}


Tree_widget::Tree_widget(const QString &title, QWidget *parent) :
    QDockWidget(title, parent)
{
     LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
     init_widgets();
}

Tree_widget::~Tree_widget()
{
     LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
};

void Tree_widget::init_widgets(){
    qtw = new QTreeWidget();
    qhl = new QHBoxLayout();
    QList<QTreeWidgetItem*> items;
    qtw->setColumnCount(2);
    for (int i=0;i<25;++i) {
        items.append(new QTreeWidgetItem(qtw,QStringList(QString("item: %1").arg(i)) ) );
    }
    connect(qtw, &QTreeWidget::itemClicked,[this](QTreeWidgetItem* itm, int col){
        std::cout << itm->text(col).toStdString() << '\n';
    });
    //qtw->insertTopLevelItems(0,items);
    qtw->addTopLevelItems(items);
    qtw->resizeColumnToContents(0);

    qhl->addWidget(qtw);

    QWidget *newWidget = new QWidget(this);
    newWidget->setLayout(qhl);
    setWidget(newWidget);


}
