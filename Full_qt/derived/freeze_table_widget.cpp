#include "freeze_table_widget.h"

#include <QStandardItemModel>
#include <QHeaderView>
#include <QScrollBar>


Freeze_Table_Widget::Freeze_Table_Widget(QAbstractItemModel * model)
{
  setModel(model);

  init();

  connect(horizontalHeader(),&QHeaderView::sectionResized, this,  &Freeze_Table_Widget::updateSectionWidth);

  connect(verticalHeader(),&QHeaderView::sectionResized, this,  &Freeze_Table_Widget::updateSectionHeight);

  connect(frozenTableView->verticalScrollBar(),&QAbstractSlider::valueChanged, verticalScrollBar(), &QAbstractSlider::setValue);

  connect(verticalScrollBar(), &QAbstractSlider::valueChanged, frozenTableView->verticalScrollBar(), &QAbstractSlider::setValue);
}


Freeze_Table_Widget::Freeze_Table_Widget(int rows, int columns, QWidget *parent ) :
  QTableView(parent)
{


 init_row_col(rows,columns);

 connect(horizontalHeader(),&QHeaderView::sectionResized, this,  &Freeze_Table_Widget::updateSectionWidth);

 connect(verticalHeader(),&QHeaderView::sectionResized, this,  &Freeze_Table_Widget::updateSectionHeight);

 connect(verticalScrollBar(),&QAbstractSlider::valueChanged, verticalScrollBar(), &QAbstractSlider::setValue);

 connect(verticalScrollBar(), &QAbstractSlider::valueChanged, verticalScrollBar(), &QAbstractSlider::setValue);
}

Freeze_Table_Widget::~Freeze_Table_Widget()
{
  deleteLater();
}

void Freeze_Table_Widget::init_row_col(int row, int col)
{
  auto model = new QStandardItemModel(this);
  model->setColumnCount(col);
  model->setRowCount(row);
  setModel(model);

  init();
  for (int rr = 0; rr < row; ++rr) {
      for (int cc = 0; cc < col; ++cc) {
         model->setItem(rr,cc,new QStandardItem(tr("[%1] [%2]").arg(rr).arg(cc)));
        }
    }
}

void Freeze_Table_Widget::init()
{

  setFocusPolicy(Qt::NoFocus);
  verticalHeader()->hide();
  horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  selectRow(0);
  //viewport()->stackUnder(frozenTableView);
  setStyleSheet("QTableView { border: none;background-color: #8EDE21;"
                                                  "selection-background-color: #999}"); //for demo purposes
  //setSelectionModel(selectionModel());
  for (int col = 1; col < model()->columnCount(); ++col){
      setColumnHidden(col, true);
      setColumnWidth(col, columnWidth(0) );
    }

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  show();

  updateFrozenTableGeometry();

  setHorizontalScrollMode(ScrollPerPixel);
  setVerticalScrollMode(ScrollPerPixel);
  setVerticalScrollMode(ScrollPerPixel);
}

void Freeze_Table_Widget::updateSectionWidth(int logicalIndex, int /* oldSize */, int newSize)
{
  if (logicalIndex == 0){
      setColumnWidth(0, newSize);
      updateFrozenTableGeometry();
    }
}

void Freeze_Table_Widget::updateSectionHeight(int logicalIndex, int /* oldSize */, int newSize)
{
  setRowHeight(logicalIndex, newSize);
}
void Freeze_Table_Widget::resizeEvent(QResizeEvent * event)
{
  QTableView::resizeEvent(event);
  updateFrozenTableGeometry();
}

QModelIndex Freeze_Table_Widget::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
  QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);

  if (cursorAction == MoveLeft && current.column() > 0 && visualRect(current).topLeft().x() < columnWidth(0) ){
      const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x() - columnWidth(0);
      horizontalScrollBar()->setValue(newValue);
    }
  return current;
}

void Freeze_Table_Widget::scrollTo (const QModelIndex & index, ScrollHint hint){
    if (index.column() > 0)
        QTableView::scrollTo(index, hint);
}

void Freeze_Table_Widget::updateFrozenTableGeometry()
{
  setGeometry(verticalHeader()->width() + frameWidth(), frameWidth(), columnWidth(0), viewport()->height()+horizontalHeader()->height());
}
