#include "table_split.h"

#include <QGridLayout>
#include <QLabel>

#include <derived/freeze_table_widget.h>

namespace {
  enum {ROW=32,COL=8};
}

Table_split::Table_split(QWidget *parent) :
  QWidget(parent)
{
  auto gr_lay = new QGridLayout();

  auto lbl = new Freeze_Table_Widget(ROW,COL);

  gr_lay->addWidget(lbl);

  setLayout(gr_lay);
}

Table_split::~Table_split()
{

}



//QWidget* pTabCornerWidget = new QWidget(this);

//    QLabel* pLabelTime = new QLabel(pTabCornerWidget);
//    pLabelTime->setText("10:22:20");

//    QPushButton* pButton = new QPushButton(pTabCornerWidget);
//    pButton->setText("?");
//    pButton->setMaximumSize(QSize(25, 25));

//    QHBoxLayout* pHLayout = new QHBoxLayout(pTabCornerWidget);
//    pHLayout->addWidget(pLabelTime);
//    pHLayout->addWidget(pButton);

//    mUI.tabWidget->setCornerWidget(pTabCornerWidget, Qt::TopRightCorner);
