#ifndef FILE_SORT_H
#define FILE_SORT_H

#include <QObject>

class File_sort :
    public QObject
{
  Q_OBJECT
public:
  explicit File_sort(QObject *parent = nullptr);

signals:

};

#endif // FILE_SORT_H
