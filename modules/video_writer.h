#ifndef VIDEO_WRITER_H
#define VIDEO_WRITER_H

#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>
#include "base_factory.h"

class Video_writer :
    public Base_factory
{
  enum{MAX_TIME = 120}; /// пишем видеоролики по MAXT_IIME секунд
public:
  Video_writer();

  Video_writer(const Video_writer&)                 = delete;
  Video_writer(Video_writer&& )                     = delete;
  Video_writer& operator = (const Video_writer& )   = delete;
  Video_writer& operator = (Video_writer&& )        = delete;

  ~Video_writer()   ;//                      override ;

  virtual void b_apply(void *)               override;
  virtual void b_start(void *)               override;
  virtual void b_stop(void *)                override;
  inline virtual const char* b_type_name()   override {return typeid (this).name(); }

private:

  boost::filesystem::path             bfp;          /// путь по которому сохраняется файл

  cv::VideoWriter v_w;

  std::time_t t;
  std::tm tm;

};

#endif // VIDEO_WRITER_H
