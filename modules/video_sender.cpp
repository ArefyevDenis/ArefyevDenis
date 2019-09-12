#include "video_sender.h"

#include <string>
#include <iostream>
#include "factory_morf.h"

REGISTER_SERIALIZABLE(Video_sender);

namespace  {

  std::string gst264 = "appsrc ! videoconvert ! x264enc speed-preset=ultrafast tune=zerolatency byte-stream=true threads=8 key-int-max=15 intra-refresh=true "
                    "! video/x-h264, profile=high ! rtph264pay ! udpsink async=false host=192.168.97.93 port=5000";
 //std::string gst = "appsrc ! videoconvert ! x264enc tune=zerolatency bitrate=2048 speed-preset=superfast ! video/x-h264 ! rtph264pay ! udpsink host=127.0.0.1 port=5000";

   std::string gst = "appsrc ! videoconvert ! x264enc tune=zerolatency bitrate=2048 speed-preset=ultrafast ! video/x-h264, profile=high ! rtph264pay ! udpsink host=192.168.97.93 port=5000 sync=false" ;

  //int WIDTH {1280};
  //int HEIGHT{720};
  int WIDTH {640};
  int HEIGHT{480};
  int FPS   {20};
}

Video_sender::Video_sender() :
  str_send(gst)
{
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

Video_sender::~Video_sender(){ b_stop(nullptr); std::cout << __PRETTY_FUNCTION__ << '\n';}

void Video_sender::b_apply(void *pt) {

  if(pt == nullptr)
    return;

  cv::Mat* src = static_cast<cv::Mat*>(pt);

  if(v_w.isOpened()){
      if(!src->empty()){
          v_w.write(*src) ;
        }
    }

}

void Video_sender::b_start(void *str) {

  if(str == nullptr)

  std::string *v_str = static_cast<std::string *>(str);

  /// внимание WIDTH, HEIGHT должны быть равны исходным значениям видео кадра иначе в файле будет зелёный фон

  if(!v_w.isOpened()){
      //v_w.open(gst, cv::CAP_GSTREAMER, 0, FPS, cv::Size(WIDTH,HEIGHT), true);
     v_w = cv::VideoWriter(gst264, cv::CAP_GSTREAMER, 0, FPS, cv::Size(WIDTH,HEIGHT), true);
    }

  std::cout << __PRETTY_FUNCTION__ << '\n';
}

void Video_sender::b_stop(void *) {
  if(v_w.isOpened()){
      v_w.release();
    }
  std::cout << __PRETTY_FUNCTION__ << '\n';
}
