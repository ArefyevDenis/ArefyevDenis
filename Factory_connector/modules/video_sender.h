#ifndef VIDEO_SENDER_H
#define VIDEO_SENDER_H

#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>
#include "base_factory.h"

class Video_sender :
    public Base_factory
{
  enum{MAX_TIME = 120}; /// пишем видеоролики по MAXT_IIME секунд
public:
  Video_sender();

  Video_sender(const Video_sender&)                 = delete;
  Video_sender(Video_sender&& )                     = delete;
  Video_sender& operator = (const Video_sender& )   = delete;
  Video_sender& operator = (Video_sender&& )        = delete;

  ~Video_sender() ;//                        override ;

  virtual void b_apply(void *)               override;
  virtual void b_start(void *)               override;
  virtual void b_stop(void *)                override;
  inline virtual const char* b_type_name()   override {return typeid (this).name(); }

private:

  std::string str_send;

  cv::VideoWriter v_w;

};

#endif // VIDEO_SENDER_H
