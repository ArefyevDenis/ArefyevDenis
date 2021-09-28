#ifndef FREEZE_TABLE_WIDGET_H
#define FREEZE_TABLE_WIDGET_H

#include <QTableView>

class Freeze_Table_Widget :
    public QTableView
{
     Q_OBJECT

public:
      Freeze_Table_Widget(QAbstractItemModel * model);

      Freeze_Table_Widget(int rows, int columns, QWidget *parent = nullptr );

      ~Freeze_Table_Widget();

protected:
      void resizeEvent(QResizeEvent *event) override;
      QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers)  override;
      void scrollTo (const QModelIndex & index, ScrollHint hint = EnsureVisible)          override;

private:
      QTableView *frozenTableView;
      void init();
      void init_row_col(int,int);
      void updateFrozenTableGeometry();

private slots:
      void updateSectionWidth(int logicalIndex, int oldSize, int newSize);
      void updateSectionHeight(int logicalIndex, int oldSize, int newSize);

};

#endif // FREEZE_TABLE_WIDGET_H
