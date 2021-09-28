#include "table_one.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QLabel>

#include <derived/q_table_widget.h>

namespace {
  enum {ROW=32,COL=8};
}

Table_one::Table_one(QWidget *parent) :
  QWidget(parent)
{
  auto gr_lay = new QHBoxLayout();

  auto qtw = new Q_table_widget(ROW,COL);

  gr_lay->addWidget(qtw);

  gr_lay->setObjectName(tr("%1_%2").arg(typeid(this).name()).arg(typeid(gr_lay).name()));
  qtw->setObjectName(tr("%1_%2").arg(typeid(this).name()).arg(typeid(qtw).name()));

  setLayout(gr_lay);

  dumpObjectTree();
  dumpObjectInfo();

}

Table_one::~Table_one()
{

}



//auto tw = new QTableWidget(ROW,COL);
//for (int rr = 0; rr < ROW; ++rr) {
//    for (int cc = 0; cc < COL; ++cc) {
//        tw->setItem(rr,cc,new QTableWidgetItem(tr("[%1][%2]").arg(rr).arg(cc)));
//      }
//  }
//tw->resizeColumnsToContents();
