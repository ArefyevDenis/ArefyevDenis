#ifndef FILE_CREATE_H
#define FILE_CREATE_H

#include <QObject>
#include <QMap>
#include <map>
#include <string>
#include <fstream>

class File_server;
class QFile;

class File_create :
    public QObject
{
  Q_OBJECT
public:
  explicit File_create(QObject *parent = nullptr);
  ~File_create()override;

  void create_qfile(const char*);
  void create_sfile(const char*);

private:

  File_server *p_fs{nullptr};

  QMap<QString, QFile*>                *p_qfile_map{nullptr};
  std::map<std::string, std::fstream*> *p_fstrm_map{nullptr};

signals:

};

#endif // FILE_CREATE_H
