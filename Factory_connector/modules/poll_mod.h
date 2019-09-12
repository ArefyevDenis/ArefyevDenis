#ifndef POLL_MOD_H
#define POLL_MOD_H

#include <thread>
#include <map>
#include <string>
#include <sys/poll.h>
#include <base_factory.h>
#include <logger.h>
#include "parsser_xml.h"

#include <fstream>

class Poll_mod :
    public Base_factory  //,    //public Example_XML<Logger_mod>
{
  enum{MAX_TIME = 120};
public:
  Poll_mod();

  ~Poll_mod()   ;//                         override;

  virtual void b_apply(void *)               override;
  virtual void b_start(void *)               override;
  virtual void b_stop(void *)                override;
  inline virtual const char* b_type_name()   override;

private:

  Parsser_XML           pr_xml;
  std::thread           std_thread;
  std::atomic<bool>     b_stop_thread{false};
  std::vector<pollfd>   vec_fd;
  std::map<std::string,std::string> map_dev_name;

  void loop_poll();

};

#endif // POLL_MOD_H
