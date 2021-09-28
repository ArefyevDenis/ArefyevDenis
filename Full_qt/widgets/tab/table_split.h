#ifndef TABLE_SPLIT_H
#define TABLE_SPLIT_H

#include <QWidget>

class Table_split : public QWidget
{
  Q_OBJECT
public:
  explicit Table_split(QWidget *parent = nullptr);

  ~Table_split()override;

signals:

};

#endif // TABLE_SPLIT_H
