#include "server_mod.h"

#include <iostream>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/epoll.h>

#include <cstring>

#include <netdb.h>

Server_mod::Server_mod()
{

}

Server_mod::~Server_mod(){}

void Server_mod::b_start(void *str){

  std::string *v_str = static_cast<std::string *>(str);

  if(!init_socket());
    return;

  std::thread temp(&Server_mod::loop_waiting_connect,this,listen_fd);

  std_thread = std::move(temp);
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

void Server_mod::b_stop(void *){}

void Server_mod::b_apply(void *){}


int Server_mod::init_socket(){
  /*************************************************************/
  /* Create an AF_INET stream socket to receive incoming       */
  /* connections on                                            */
  /*************************************************************/
  listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(listen_fd < 0){
      perror("socket() failed");
      return -1;
    }
  /*************************************************************/
  /* Allow socket descriptor to be reuseable
   * дескриптор сокета, который будет использоваться многократно
  /*************************************************************/
  int rc = setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
  if(rc < 0){
      perror("setsockopt() failed");
      close(listen_fd);
      return -1;
    }
  /*************************************************************/
  /*Установить socket,  неблокирующими. Все sockets для */
  /* входящих соединений также будут неблокирующими      */
  /* они будут наследовать, состояние от слушающего сокета.
  /*************************************************************/
  rc = ioctl(listen_fd, FIONBIO, (char *)&on);
  if(rc < 0){
      perror("ioctl() failed");
      close(listen_fd);
      return -1;
    }
  /*************************************************************/
  /* Bind the socket                                           */
  /*************************************************************/
  ::memset(&addr, 0, sizeof(addr));
  addr.sin_family      = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port        = htons(SERVER_PORT);
  rc = bind(listen_fd,(struct sockaddr *)&addr, sizeof(addr));
  if(rc < 0){
      perror("bind() failed");
      close(listen_fd);
      return -1;
    }
  /*************************************************************/
  /* Set the listen back log                                   */
  /*************************************************************/
  rc = listen(listen_fd, 32);
  if(rc < 0){
      perror("listen() failed");
      close(listen_fd);
      return -1;
    }
  return 1;
  // thread_accept = new std::thread(Thread_server_epoll::loop_waiting_connect,listen_fd);
}

int Server_mod::loop_waiting_epoll(){
  return 0;
}

int Server_mod::loop_waiting_connect(int listen_fd){
  return 0;
}






