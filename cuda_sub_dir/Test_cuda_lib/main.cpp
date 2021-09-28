#include <QCoreApplication>

#include "../cuda_one/wrap_cuda_one.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  Wrap_cuda_one wco;

  return a.exec();
}
