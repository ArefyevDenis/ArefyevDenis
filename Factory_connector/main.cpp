#include <QCoreApplication>
#include <QApplication>

#include <boost/asio.hpp>
#include <boost/version.hpp>

#include "konsole_core.h"

int main(int argc, char *argv[])
{
  //Konsole_core<QCoreApplication> kc(argc,argv);
  Konsole_core<QApplication> kc(argc,argv);

  kc.init();

  kc.run();

  std::cout << __PRETTY_FUNCTION__ <<'\n';
  return 0;
}
