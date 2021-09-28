#include "one_widget.h"

#include <QVBoxLayout>
#include <QLabel>

#include "common/logger.h"
#include "common/afactory.h"

//bool b_One_widget = AFactory::register_type<One_widget>("One_widget");

One_widget::One_widget(QWidget *parent) :
    QDockWidget(parent)
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
    init_widgets();
}


One_widget::One_widget(const QString &title, QWidget *parent) :
    QDockWidget(title, parent)
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
    init_widgets();
}

One_widget::~One_widget()
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

void One_widget::init_widgets(){
    QVBoxLayout *vb = new QVBoxLayout();
    vb->setObjectName(tr("%1_%2").arg(typeid(this).name()).arg(typeid(vb).name()));
    QLabel* lb = new QLabel(typeid (this).name());
    vb->addWidget(lb);
    lb->setObjectName(tr("%1_%2").arg(typeid(this).name()).arg(typeid(vb).name()));
    setLayout(vb);

    dumpObjectTree();
    dumpObjectInfo();

}
