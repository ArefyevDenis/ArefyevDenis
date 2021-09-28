#ifndef FILE_FILL_H
#define FILE_FILL_H

#include <QObject>

class File_server;

class File_fill :
    public QObject
{
  Q_OBJECT
public:
  explicit File_fill(QObject *parent = nullptr);

  void filling_sfile();
  void filling_qfile();

protected:

  File_server *p_fs{nullptr};

  uint size_{0};

signals:

};

#endif // FILE_FILL_H
