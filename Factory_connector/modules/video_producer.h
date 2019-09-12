#ifndef VIDEO_PRODUCER_H
#define VIDEO_PRODUCER_H

#include <base_factory.h>

#include <thread>
#include <atomic>
#include <fstream>
#include <vector>
#include <map>
#include <opencv2/core/core.hpp>

#include "logger.h"

class Video_consumer;

class Video_producer :
    public Base_factory
{
  enum{VC = 8}; /// не более 8 потребтиелей видеопотока
public:
  Video_producer();

  Video_producer(const Video_producer&)                 = delete;
  Video_producer(Video_producer&& )                     = delete;
  Video_producer& operator = (const Video_producer& )   = delete;
  Video_producer& operator = (Video_producer&& )        = delete;

  ~Video_producer();    //                    override ;

  virtual void b_apply(void *)               override;
  virtual void b_start(void *)               override;
  virtual void b_stop(void *)                override;
  inline virtual const char* b_type_name()   override;

private:

  std::vector<Video_consumer *> vec_consum; /// получатель данных

  std::thread std_thread;
  std::atomic_bool b_stop_thread     {false}; ///

};


#endif // VIDEO_PRODUCER_H
