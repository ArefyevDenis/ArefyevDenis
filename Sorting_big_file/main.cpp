#include <QCoreApplication>

#include <parser_args.h>
#include <file_server.h>
#include <QWidget>
#include <iostream>
#include <sstream>

//QWidget qww;

int main(int argc, char *argv[])
{
  // QCoreApplication a(argc, argv);

  std::cout << __PRETTY_FUNCTION__ << ' ' << __LINE__ << '\n';

  std::string argv_cin;

  switch (argc) {
    case 1:
      std::cout <<" Введите исходные данные: \n";
      if(std::getline(std::cin, argv_cin)){
          std::cout << "[ " << argv_cin << " ]\n";
        }
      r_pars().parsing_args(argv_cin);
      break;
    default:
      r_pars().parsing_args(argc,argv);
      break;
    }

  File_server fs;

  std::cout << __PRETTY_FUNCTION__ << ' ' << __LINE__ << '\n';

  //return a.exec();
}
