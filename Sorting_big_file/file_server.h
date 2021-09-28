#ifndef FILE_SERVER_H
#define FILE_SERVER_H

#include <QObject>

#include <file_create.h>
#include <file_fill.h>
#include <file_sort.h>
#include <map>
#include <QMap>

class File_server :
    public QObject
{
  Q_OBJECT
public:
  explicit File_server(QObject *parent = nullptr);

  ~File_server() override;

  void apply();

  QMap<QString, QFile*>                 _qfile_map;//{nullptr};
  std::map<std::string, std::fstream*>  _fstrm_map;//{nullptr};

protected:

  File_create f_create; // знает сколько и какие файлы созданы
  File_fill   f_fill;   // алгоритм заполнения файлов
  File_sort   f_sort;   // алгоритм сортировки файлов

  // исходные данные
  std::string files{""};
  std::string sizes{""};

signals:

};

#endif // FILE_SERVER_H
