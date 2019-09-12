#ifndef KONSOLE_CORE_H
#define KONSOLE_CORE_H

#include <iostream>
#include <typeinfo>

#include <signal.h>

#include "encapsulation_obj.h"
#include "configurate_obj.h"
#include "example_xml.h"

template<typename Types>
class Konsole_core :
    public Types
{
public:

  Konsole_core(int &argc, char **argv) :
    Types(argc,argv),
    c_obj(),
    e_obj(c_obj)
  {
    catchUnixSignals({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
    std::cout << __PRETTY_FUNCTION__ << '\n';
  }

  ~Konsole_core(){
    std::cout << __PRETTY_FUNCTION__ << '\n';
  }

  bool init(){
    e_obj.create_modules();
    std::cout << __PRETTY_FUNCTION__ << '\n';
  }

  bool run(){
    std::cout << __PRETTY_FUNCTION__ << '\n';
    Types::exec();
  }

  void ignoreUnixSignals(std::initializer_list<int> ignoreSignals) {
      // all these signals will be ignored.
      for (int sig : ignoreSignals)
          signal(sig, SIG_IGN);
  }

  void catchUnixSignals(std::initializer_list<int> quitSignals) {

      auto handler = [](int sig) -> void { Types::quit();  };

      sigset_t blocking_mask;
      sigemptyset(&blocking_mask);
      for (auto sig : quitSignals)
          sigaddset(&blocking_mask, sig);

      struct sigaction sa;
      sa.sa_handler = handler;
      sa.sa_mask    = blocking_mask;
      sa.sa_flags   = 0;

      for (auto sig : quitSignals)
          sigaction(sig, &sa, nullptr);
  }


public:

  Configurate_obj   c_obj; //
  Encapsulation_obj e_obj; //
//  Action_poll   actp;

};

#endif // KONSOLE_CORE_H
