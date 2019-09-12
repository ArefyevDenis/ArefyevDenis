#include "video_writer.h"

#include <string>
#include <iostream>
#include "factory_morf.h"

REGISTER_SERIALIZABLE(Video_writer);

namespace  {
  //int WIDTH {1280};
  //int HEIGHT{720};

  int WIDTH {640};
  int HEIGHT{480};
  int FPS   {20};
}

Video_writer::Video_writer() :
  bfp(boost::filesystem::current_path())
{
  bfp += "/video/";
  if(!boost::filesystem::exists(bfp)){                /// если такой директории нет создадим
      if(!boost::filesystem::create_directory(bfp)){  /// если не получилось сразу завалим программу
          std::terminate();                           /// на этапе отладки чем громче упадёт тем лучше.
        }
    }
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

Video_writer::~Video_writer(){ b_stop(nullptr); std::cout << __PRETTY_FUNCTION__ << '\n';}

void Video_writer::b_apply(void *pt) {

  if(pt == nullptr)
    return;

  cv::Mat* src = static_cast<cv::Mat*>(pt);

  if(v_w.isOpened()){
      if(!src->empty()){
         // cv::imshow(typeid (this).name(),*src);
          v_w.write(*src) ;
        }
    }

  if(static_cast<double>(MAX_TIME) < std::difftime(std::time(nullptr),t)){
      b_stop(nullptr);
      b_start(nullptr);
    }

}

void Video_writer::b_start(void *str) {

  std::string *v_str = static_cast<std::string *>(str);
  /// внимание WIDTH, HEIGHT должны быть равны исходным значениям видео кадра иначе в файле будет зелёный фон
  t = std::time(nullptr);
  tm = *std::localtime(&t);
  std::stringstream st_vid;
  st_vid << bfp.string();
  st_vid << std::put_time(&tm,"%Y_%m_%d_%H_%M_%S") << ".avi";

  if(!v_w.isOpened()){

#if CV_MAJOR_VERSION >= 3
      v_w.open(st_vid.str(), cv::VideoWriter::fourcc('X','2','6','4'), FPS, cv::Size(WIDTH, HEIGHT)); /// 4.1.0
#else
      //v_w.open(st_vid.str(), CV_FOURCC('X','2','6','4'), FPS, cv::Size(WIDTH, HEIGHT)); /// 3.1.0
#endif

    }
  // std::cout << __PRETTY_FUNCTION__ << '\n';
}

void Video_writer::b_stop(void *) {
  if(v_w.isOpened()){
      v_w.release();
    }
//  std::cout << __PRETTY_FUNCTION__ << '\n';
}



