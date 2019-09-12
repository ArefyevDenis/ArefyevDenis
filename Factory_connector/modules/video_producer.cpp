#include "video_producer.h"
#include "video_consumer.h"

#include <iostream>
#include <exception>
#include <unistd.h>
#include "factory_morf.h"

#include <opencv2/core/cvstd.hpp>
#include <opencv2/opencv.hpp>

REGISTER_SERIALIZABLE(Video_producer)

namespace  {
  //int WIDTH {1280};
  //int HEIGHT{720};
  std::string op_odr = "v4l2src device=/dev/video0 do­timestamp=true ! video/x­raw, width=640, height=480, framerate=20/1 ! v4l2video20convert ! appsink";

  std::string op_x86 = "/dev/video0";

  int WIDTH {640};
  int HEIGHT{480};
  int FPS   {20};
}

Video_producer::Video_producer()
{
}

Video_producer::~Video_producer(){
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

void Video_producer::b_apply(void *)try{

}catch(...){

}

void Video_producer::b_start(void* str) {

  std::string *v_str = static_cast<std::string *>(str);

  b_stop_thread.store(false);

  std::thread temp([this](){

      try {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        //cv::VideoCapture vc(op_x86,cv::CAP_GSTREAMER);
        cv::VideoCapture vc(0,cv::CAP_V4L);
        cv::Mat mat_;

        while(!b_stop_thread.load()){
            if(vc.isOpened()){        /// если камера отвалилась она по прежнему считается открытой !!!
                if(vc.read(mat_)){    /// если прочитать не смогли закроем камеру она отвалилась
                    try {             /// если модуль не открыт перехватим искCV_CAP_PROP_FRAME_WIDTHлючение

                      cv::imshow(typeid (this).name(),mat_);

                      map_obj.at("Optical_flow_mod")->b_apply(&mat_); /// оптический поток
                      map_obj.at("Video_writer")->b_apply(&mat_);     /// записать видео файл
                      map_obj.at("Video_sender")->b_apply(&mat_);     /// отправка по сети

                    } catch (std::exception & ex) { /// можно сообщить об этом модулю обработки ошибок (если он есть)
                      std::cout << ex.what() << __FILE__ << __LINE__ << '\n';
                    }
                  }else{
                    vc.release();
                  }
                usleep(1000000/FPS);
              }else{  /// если камера закрыта откроем её
                if(vc.open(op_x86,cv::CAP_V4L)){
#if CV_MAJOR_VERSION >= 3
                    vc.set(cv::CAP_PROP_FRAME_WIDTH,WIDTH);
                    vc.set(cv::CAP_PROP_FRAME_HEIGHT,HEIGHT);
                    vc.set(cv::CAP_PROP_FPS,FPS);
#else
                    vc.set(cv_CAP_PROP_FRAME_WIDTH,WIDTH);
                    vc.set(CV_CAP_PROP_FRAME_HEIGHT,HEIGHT);
                    vc.set(CV_CAP_PROP_FPS,FPS);
#endif
                  }
                sleep(1);             /// камеры может долго не быть не будем жить в бесконечном цикле
              }
          }

        vc.release();
        mat_.release();

      } catch (std::exception & ex) {
        std::cout << ex.what() << __FILE__ << __LINE__ << '\n';
      }
      sleep(1);
    }

  );

 std_thread = std::move(temp);
 std::cout << __PRETTY_FUNCTION__ << '\n';
}

void Video_producer::b_stop(void *)  {
  b_stop_thread.store(true);
  if(std_thread.joinable())
    std_thread.join();
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

const char* Video_producer::b_type_name(){ return typeid (this).name(); }





























//                       for (int i=0; i<VC; ++i) {
//                           std::string vid("Video_consumer");
//                           vid += '_' + std::to_string(i);
//                          Video_consumer *pv =  dynamic_cast<Video_consumer*>(map_obj[vid]);
//                          if(pv==nullptr)
//                            continue;
//                          std::unique_lock<std::mutex> lock(pv->mt);
//                          pv->que_frame.push(&mat_);
//                          pv->cv.notify_all();
//                        }














/*

void Video_producer::b_start(void* str) {

  std::string *v_str = static_cast<std::string *>(str);

  std::thread temp([this](){

      try {

        cv::VideoCapture vc;

        cv::Mat mat_;

        while(!b_stop_thread.load()){
            if(vc.isOpened()){        /// если камера отвалилась она по прежнему считается открытой !!!
                if(vc.read(mat_)){    /// если прочитать не смогли закроем камеру она отвалилась
                    try {             /// если модуль не открыт перехватим исключение
                      map_obj.at("Optical_flow_mod")->b_apply(&mat_); /// оптический поток
//                      map_obj.at("Mod_b")->b_apply(&mat_); /// запись видоепотока
//                      map_obj.at("Mod_c")->b_apply(&mat_); ///
                    } catch (std::exception & ex) { /// можно сообщить об этом модулю обработки ошибок (если он есть)
                      std::cout << ex.what() << __FILE__ << __LINE__ << '\n';
                    }
                  }else{
                    vc.release();
                  }
                usleep(1000000/FPS);
              }else{                  /// если камера закрыта откроем её
                if( vc.open("/dev/video0")){
                    vc.set(CV_CAP_PROP_FRAME_WIDTH,WIDTH);
                    vc.set(CV_CAP_PROP_FRAME_HEIGHT,HEIGHT);
                    vc.set(CV_CAP_PROP_FPS,FPS);
                  }
                sleep(1);             /// камеры может долго не быть не будем жить в бесконечном цикле
              }
          }

      } catch (std::exception & ex) {
        std::cout << ex.what() << __FILE__ << __LINE__ << '\n';
      }

    }
  );

  std_thread = std::move(temp);
  std::cout << __PRETTY_FUNCTION__ << '\n';
}


*/
