#ifndef PRODUCER_STDOUT_H
#define PRODUCER_STDOUT_H

#include <base_factory.h>

#include <QThread>
#include <QFile>

#include <thread>

class Producer_stdout :
    public Base_factory
{
public:
  Producer_stdout();

  ~Producer_stdout();

  void b_apply(void *);

  void b_start(void *) override;
  void b_stop(void *)  override;
  const char* b_type_name() override ;

private:

  std::thread std_thread;
  std::atomic_bool b_stop_thread     {false}; ///

};

#endif // PRODUCER_STDOUT_H
