#ifndef KEEPER_H
#define KEEPER_H

#include <QObject>

#include <QMap>

class QFile;

class Keeper : public QObject
{
  Q_OBJECT
public:
  explicit Keeper(QObject *parent = nullptr);

  ~Keeper() override;

  QMap<QString, QFile*>                 *p_qfile_map{nullptr};
  std::map<std::string, std::fstream*>  *p_fstrm_map{nullptr};

signals:


};

#endif // KEEPER_H
