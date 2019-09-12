#ifndef SERVER_MOD_H
#define SERVER_MOD_H

#include <thread>
#include <netinet/in.h>
#include <unistd.h>
#include "base_factory.h"

#include <atomic>

// смотри проект Server_poll_epoll_udp_tcp

class Server_mod :
    public Base_factory
{
  enum {SERVER_PORT = 12346};
public:
  Server_mod();

  ~Server_mod();// override;

  virtual void b_apply(void *)               override;
  virtual void b_start(void *)               override;
  virtual void b_stop(void *)                override;
  inline virtual const char* b_type_name()   override { return typeid (this).name(); }

private:

  int init_socket();
  int loop_waiting_epoll();
  int loop_waiting_connect(int listen_fd);

  struct sockaddr_in   addr;

  int listen_fd   {-1};/// = -1
  int on          {-1};/// =  1
  int nfds        {-1};/// = -1
  int timeout;
  int end_server;
  int close_conn;
  int new_fd;


  std::thread std_thread;
  std::atomic_bool b_stop_thread     {false};

};

#endif // SERVER_MOD_H
