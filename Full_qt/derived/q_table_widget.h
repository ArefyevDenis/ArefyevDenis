#ifndef Q_TABLE_WIDGET_H
#define Q_TABLE_WIDGET_H

#include <QTableWidget>

// рекурсивный виджет
class Q_table_widget :
    public QTableWidget
{
  Q_OBJECT
public:

  explicit Q_table_widget(QWidget *parent = nullptr);

  Q_table_widget(int rows, int columns, QWidget *parent = nullptr);

  ~Q_table_widget() override;

  void init_tab(int rows, int columns);

  void init_tab_full(int row,int col);

protected:
  // Event handlers QWidget
  bool event(QEvent *event) override;
//  void mousePressEvent(QMouseEvent *event);
//  void mouseReleaseEvent(QMouseEvent *event);
//  void mouseDoubleClickEvent(QMouseEvent *event);
//  void mouseMoveEvent(QMouseEvent *event);
//  void wheelEvent(QWheelEvent *event);
//  void keyPressEvent(QKeyEvent *event);
//  void keyReleaseEvent(QKeyEvent *event);
//  void focusInEvent(QFocusEvent *event);
//  void focusOutEvent(QFocusEvent *event);
//  void enterEvent(QEvent *event);
//  void leaveEvent(QEvent *event);
//  void paintEvent(QPaintEvent *event);
//  void moveEvent(QMoveEvent *event);
  void resizeEvent(QResizeEvent *event) override;
//  void closeEvent(QCloseEvent *event);
//  void contextMenuEvent(QContextMenuEvent *event);

protected:
//    virtual slot QTableView
//    void scrollContentsBy(int dx, int dy) override;
//    QStyleOptionViewItem viewOptions() const override;
//    void paintEvent(QPaintEvent *e) override;
//    void timerEvent(QTimerEvent *event) override;
//    int horizontalOffset() const override;
//    int verticalOffset() const override;
//    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
//    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) override;
//    QRegion visualRegionForSelection(const QItemSelection &selection) const override;
//    QModelIndexList selectedIndexes() const override;
//    void updateGeometries() override;
//    QSize viewportSizeHint() const override;
//    int sizeHintForRow(int row) const override;
//    int sizeHintForColumn(int column) const override;
//    void verticalScrollbarAction(int action) override;
//    void horizontalScrollbarAction(int action) override;
//    bool isIndexHidden(const QModelIndex &index) const override;
//    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;
//    void currentChanged(const QModelIndex &current, const QModelIndex &previous) override;

public slots:

   void slot_sectionResized(int,int,int);
signals:

};

#endif // Q_TABLE_WIDGET_H
