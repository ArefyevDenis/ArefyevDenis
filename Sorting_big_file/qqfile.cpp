#include "qqfile.h"

#include <iostream>

QQFile::QQFile() :
  QFile()             {std::cout << __PRETTY_FUNCTION__ << "\n";}

QQFile::QQFile(const QString &name) :
  QFile(name)         {std::cout << __PRETTY_FUNCTION__ << "\n";}

QQFile::QQFile(QObject *parent) :
  QFile(parent)       {std::cout << __PRETTY_FUNCTION__ << "\n";}

QQFile::QQFile(const QString &name, QObject *parent):
  QFile(name,parent)  {std::cout << __PRETTY_FUNCTION__ << "\n";}

QQFile::~QQFile(){std::cout << __PRETTY_FUNCTION__ << "\n";}
