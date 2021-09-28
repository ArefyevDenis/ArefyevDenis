#ifndef QQFILE_H
#define QQFILE_H

#include <QFile>

class QQFile :
    public QFile
{
   Q_OBJECT
public:

  QQFile() ;

  QQFile(const QString &name) ;

  explicit QQFile(QObject *parent) ;

  QQFile(const QString &name, QObject *parent);

  ~QQFile();

signals:

};
#endif // QQFILE_H
