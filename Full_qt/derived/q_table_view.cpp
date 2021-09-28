#include "q_table_view.h"

#include<QHeaderView>
#include <qevent.h>

namespace {
  int deep{0};
}

#include <iostream>
#define DEBUG_LOG
template<typename ...Args>
void LOG_t(Args && ...args)
{ // о пробелах и табуляции заботится вызывающий
#ifdef DEBUG_LOG
    (std::cout<< ... << args);
#else

#endif

}

Q_table_view::Q_table_view(QWidget *parent) :
  QTableWidget(parent)
{
  init_tab_full(0,0);
}

Q_table_view::Q_table_view(int rows, int columns, QWidget *parent ) :
  QTableWidget(rows, columns, parent)
{
 init_tab_full(rows,columns);
}

Q_table_view::~Q_table_view()
{

}

void Q_table_view::init_tab(int rows, int columns)
{
  setSelectionMode(QAbstractItemView::SingleSelection);
  setSelectionBehavior(QAbstractItemView::SelectRows);
  horizontalHeader()->setStretchLastSection(true);
  verticalHeader()->setStretchLastSection(true);

  if(deep==((rows*columns)))
    return;

  int r = deep/columns; // делим на количество столбцов
  int c = deep%columns;

  deep++;

  setCellWidget(r,c,new Q_table_view(rows,columns,this));

  int aaa[3][3];
  for(int ix=0;ix<9;++ix){
      int r = ix/3; // делим на количество столбцов
      int c = ix%3;
      aaa[r][c] = c + r*3; // умножаем на количество столбцов
    }

}

void Q_table_view::init_tab_full(int row, int col)
{
//  setSelectionMode(QAbstractItemView::SingleSelection);
//  setSelectionBehavior(QAbstractItemView::SelectRows);
//  horizontalHeader()->setStretchLastSection(true);
//  verticalHeader()->setStretchLastSection(true);


  for (int rr = 0; rr < row; ++rr) {
      for (int cc = 0; cc < col; ++cc) {
          setItem(rr,cc,new QTableWidgetItem(tr("[%1] [%2]").arg(rr).arg(cc)));
        }
    }

  //resizeColumnsToContents();

//  setVisible(false);
//  QRect vporig = viewport()->geometry();
//  QRect vpnew = vporig;
//  vpnew.setWidth(std::numeric_limits<int>::max());
//  viewport()->setGeometry(vpnew);
//  resizeColumnsToContents();
//  //resizeRowsToContents();
//  viewport()->setGeometry(vporig);
//  setVisible(true);

}

void Q_table_view::resizeEvent(QResizeEvent *ev)
{

  int rr = rowCount();
  int cc = columnCount();
  int wi = width();

  int ev_wi = ev->size().width();
  int ev_hi = ev->size().height();

  int ev_old_wi = ev->oldSize().width();
  int ev_old_hi = ev->oldSize().height();


  for (int col = 0; col < cc; ++col) {
      setColumnWidth(col, ev_wi/cc);
    }

  LOG_t(__PRETTY_FUNCTION__,' ',__LINE__,' ',wi,' ',ev_wi,' ',ev_hi,' ',ev_old_wi,' ',ev_old_hi,'\n');

  QTableWidget::resizeEvent(ev);


  //  int ax = verticalHeader()->width()+frameWidth();
  //  int ay = frameWidth();
  //  int wh = columnWidth(0);
  //  int hi = viewport()->height()+horizontalHeader()->height();
  //  LOG_t( verticalHeader()->width(),' ', frameWidth(),' ',columnWidth(0) ,' ',horizontalHeader()->height() ,' ',ax,' ',ay,' ',wh,' ',hi,'\n');
  //  setGeometry(ax,ay,wh,hi);

}


//q_t_w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//_t_w->horizontalHeader( )->setResizeMode(QHeaderView::Stretch);
