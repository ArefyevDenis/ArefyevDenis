#include "video_consumer.h"

#include <iostream>

#include <unistd.h>
#include <sys/types.h> /* POSIX */
#include <sys/syscall.h>

#include <opencv2/highgui/highgui.hpp>

#include "factory_morf.h"

REGISTER_SERIALIZABLE(Video_consumer);

#define SSTR( x ) static_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << x ) ).str()

Video_consumer::Video_consumer()
{
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

Video_consumer::~Video_consumer(){
    //std::cout << __PRETTY_FUNCTION__ << "0\n";
    b_stop_thread.store(true);
    cv.notify_all();
    if(std_thread.joinable())
      std_thread.join();
   std::cout << __PRETTY_FUNCTION__ << "1\n";
}

void Video_consumer::b_start(void* str){

  std::string *v_str = static_cast<std::string *>(str);

  std::thread temp([this]( ){
      std::cout << "ThreadMain vc PID: " << getpid() << "\n";
      std::cout << "ThreadMain vc TID: " << syscall(__NR_gettid) << "\n";

      //      if(!str->empty())
      //          str.clear();

      std::thread::id t_id = std_thread.get_id();

      while(!b_stop_thread.load()){
          std::unique_lock<std::mutex> lock(mt);                                              ///https://en.cppreference.com/w/cpp/thread/condition_variable
          cv.wait(lock, [this](){  return b_stop_thread.load() || !que_frame.empty();     });   ///https://gist.github.com/iikuy/8115191
          while(!que_frame.empty()){        // если очередб не пуста будем вычитывать её до конца
              auto res = que_frame.front();
              //map_obj.at("Optical_flow_mod")->b_apply(res); /// оптический поток
              //cv::imshow(SSTR(t_id) ,*res);
              //cv::waitKey(1);
              //std::cout << "t_id = " << t_id << " size = " << que_frame.size() << "\n";
              que_frame.pop();
            }
        }
       std::cout << __PRETTY_FUNCTION__ << '\n';
    });

  std_thread = std::move(temp);
  std::cout << __PRETTY_FUNCTION__ << '\n';

}

void Video_consumer::b_apply(void *){}

void Video_consumer::b_stop(void *)  {
 // std::cout << __PRETTY_FUNCTION__ << "0\n";
  b_stop_thread.store(true);
  cv.notify_all();
  if(std_thread.joinable())
    std_thread.join();
  std::cout << __PRETTY_FUNCTION__ << "1\n";
}

const char* Video_consumer::b_type_name(){ return typeid (this).name(); }
