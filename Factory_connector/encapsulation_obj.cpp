#include "encapsulation_obj.h"

#include <iostream>

#include <modules/modules.h>
#include <modules/producer_stdout.h>
#include <modules/video_producer.h>
#include <modules/logger_mod.h>
#include <modules/optical_flow_mod.h>
#include <modules/video_consumer.h>
#include <modules/video_writer.h>
#include <modules/poll_mod.h>
#include <modules/video_sender.h>
#include <modules/qt_thread_mod.h>

#include <network/tcp_server_wrap.h>
#include <network/udp_sock_wrap.h>

Encapsulation_obj::Encapsulation_obj(Configurate_obj& c_obj) :
  c_obj_(c_obj)
{
  std::cout <<__PRETTY_FUNCTION__ << '\n';
}

Encapsulation_obj::~Encapsulation_obj()
{
  for (auto it: map_str_f) {
      it.second->b_stop(nullptr);
      delete it.second;
    }
  std::cout <<__PRETTY_FUNCTION__ << '\n';
}

void Encapsulation_obj::create_modules(){

  /// создаём необходимые модули

  //map_str_f["Producer_stdout"] = dynamic_cast<Producer_stdout*>(f_morf.create("Producer_stdout"));
  map_str_f["Logger_mod"]       = dynamic_cast<Logger_mod*>(f_morf.create("Logger_mod"));
  map_str_f["Video_producer"]   = dynamic_cast<Video_producer*>(f_morf.create("Video_producer"));
  map_str_f["Optical_flow_mod"] = dynamic_cast<Optical_flow_mod*>(f_morf.create("Optical_flow_mod"));
  map_str_f["Video_writer"]     = dynamic_cast<Video_writer*>(f_morf.create("Video_writer"));
//  map_str_f["Poll_mod"]         = dynamic_cast<Poll_mod*>(f_morf.create("Poll_mod"));
  map_str_f["Video_sender"]     = dynamic_cast<Video_sender*>(f_morf.create("Video_sender"));
  map_str_f["Qt_thread"]        = dynamic_cast<Qt_thread*>(f_morf.create("Qt_thread"));

// ----------------- создадим эти объекты в контексте отдельного потока ---------------------------------
//  map_str_f["Tcp_server_wrap"]        = dynamic_cast<Tcp_server_wrap*>(f_morf.create("Tcp_server_wrap"));
//  map_str_f["Udp_socket_wrap"]        = dynamic_cast<Udp_sock_wrap*>(f_morf.create("Udp_sock_wrap"));

//  for(int i=0 ; i<1; ++i){
//      std::string vid("Video_consumer");
//      vid += '_' + std::to_string(i);
//      map_str_f[vid] = dynamic_cast<Video_consumer*>(f_morf.create("Video_consumer"));
//    }

  /// настройка инициализация модулей
  for (auto kvp: map_str_f) {
     // std::cout << typeid (kvp.second).name() << '\n';
      kvp.second->set_obj({kvp.first,kvp.second});
    }


  /// стартуем дальше боевая работа
  for (auto kvp: map_str_f) {
      kvp.second->b_start(nullptr);
    }

}
