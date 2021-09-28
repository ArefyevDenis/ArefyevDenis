
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "shared_lib.h"
#include "static_lib.h"

#include "cpp_files.h"
#include "cu_files.h"

#include "cpp_shared_lib.h"
#include "cuda_shared_lib.h"

int main(int argc, char *argv[]){


  //std::ostream& std_cout = std::cout;
  //std::ostream& std_fstr(std::ofstream(argv[2], std::ios::out | std::ios::binary));
  //std::ostream& std_cout_move = std::move(std::cout);

  std::istream* is;
  std::string arg;
  switch (argc) {
    case 1:
      {
        is = &std::cin;
        std::istream& std_is =  std::cin;
        std::istream is_(std::cin.rdbuf());
      }
      break;

    default:
      {
      is = new std::istringstream(argv[1]);
      //std::istream std_is = std::move( std::istringstream(argv[1]) );
      }
      break;
    }

  std::getline(*is,arg);

  std::cout << "----------------START--------------" << "\n" << arg << "\n-------------------------------------------\n";

  Static_lib stl;

  Shared_lib shl;

  Cpp_files cpf;

  CU_files cuf;
  cuf.init();

  Cpp_shared_lib cpp_shl;

  Cuda_shared_lib cud_shl;

  return 0;

}
