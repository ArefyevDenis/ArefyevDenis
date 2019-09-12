#include "optical_flow_mod.h"

#include <time.h>
#include <iostream>
#include <iomanip>
#include <ostream>
#include <iterator>
#include <numeric>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <strstream>
#include "factory_morf.h"

REGISTER_SERIALIZABLE(Optical_flow_mod);

Optical_flow_mod::Optical_flow_mod(int mc, double ql, double md):
  bfp(boost::filesystem::current_path()),
  max_count(mc),
  qlevel(ql),
  minDist(md),
  termcrit(cv::TermCriteria::COUNT|cv::TermCriteria::EPS,20,0.03)
{

  std::time_t t = std::time(nullptr);
  std::tm tm = *std::localtime(&t);
  std::stringstream st_time;
  bfp += "/track/";
  st_time << bfp.string();
  st_time << std::put_time(&tm,"%Y:%m:%d_%H:%M:%S") ;
  track_log = std::move(std::ofstream( std::string (st_time.str() + ".txt"))) ;

  if(!boost::filesystem::exists(bfp)){                /// если такой директории нет создадим
      if(!boost::filesystem::create_directory(bfp)){  /// если не получилось сразу завалим программу
          std::terminate();                           /// на этапе отладки чем громче упадёт тем лучше.
        }
    }

  map_func[0] = [](const cv::Point2f &a, const cv::Point2f &b) {  return (a.x + a.y < b.x + b.y); }; /// (a.x + a.y < b.x + b.y);
  map_func[1] = [](const cv::Point2f &a, const cv::Point2f &b) {  return (a.x - a.y < b.x - b.y); }; ///a.x - a.y < b.x - b.y);
  map_func[2] = [](const cv::Point2f &a, const cv::Point2f &b) {  return (a.y - a.x < b.y - b.x); }; ///(a.y - a.x < b.y - b.x);
  map_func[3] = [](const cv::Point2f &a, const cv::Point2f &b) {  return (-a.y - a.x < -b.y - b.x); }; /// (-a.y - a.x < -b.y - b.x);
  std::cout << __PRETTY_FUNCTION__ <<'\n';

  of_ptr =  cv::SparsePyrLKOpticalFlow::create( cv::Size(31,31),// размер окна поиска
                                                3,              // максимальный уровень пирамид
                                                termcrit,
                                                0, 0.001);

  vec_trans.reserve(IMAGE_SZ);
}

Optical_flow_mod::~Optical_flow_mod(){
  track_log.close();
  std::cout << __PRETTY_FUNCTION__ << '\n';
}

void Optical_flow_mod::b_apply(void *pt){

  if(closing)
    return;

  if(pt == nullptr)
    return;

  cv::Mat* src = static_cast<cv::Mat*>(pt);
  cv::Mat deep_copy ;
  src->copyTo(deep_copy);

  if(!deep_copy.empty()){

      //      cv::imshow(typeid (this).name(),*src);

#if CV_MAJOR_VERSION >= 3
      cv::cvtColor(deep_copy, gray,  cv::COLOR_BGR2GRAY); // 4.1.0
#else
      //cv::cvtColor(deep_copy, gray, CV_BGR2GRAY); /// 3.4.1
#endif
      //Определяет сильные углы на изображении.
      cv::goodFeaturesToTrack(gray,   features_p,   max_count,   0.001, 10, cv::Mat(), 3, 3, 0, 0.04);
      //      //точное определение углов
      cv::cornerSubPix(gray, features_p, cv::Size(10,10), cv::Size(-1,-1), termcrit);

      if(!features_p.empty() ) {

          if(gray_prev.empty())
            gray.copyTo(gray_prev);
          //расчитать оптический поток
          of_ptr->calc(gray_prev,      // первое восьми битное изображение
                       gray,           // второе входное изображение
                       features_p,     // исходный вектор точек для которых
                       track_p,        //
                       status,         // вектор состояния
                       err             // вектор ошибок
                       );

          std::size_t k=0;
          for( std::size_t i = 0; i < track_p.size(); i++ ) {

              if( !status[i] ){
                  continue;
                }

              features_p[k] = features_p[i];
              track_p[k++] = track_p[i];

            }

          track_p.resize(k);
          features_p.resize(k);

          if( auto sz(track_p.size()); sz > 4){
              if(features_p.size() != track_p.size()){
                  std::cout << "---------------------------- size---------------------------\n";
                }
              cv::Point2f a[4];
              cv::Point2f b[4];
              // поиск угловых точек
              auto it = std::min_element(features_p.begin(),features_p.end(), map_func[0]);
              a[0] = *it; b[0] = track_p.at(static_cast<std::size_t>(it - features_p.begin()));
              // std::cout << "[ " << it->x <<' ' << it->y << " ] " ; std::cout << "[ " << track_p.at(it - features_p.begin()).x <<' ' << track_p.at(it - features_p.begin()).x << "]\n" ;
              it = std::min_element(features_p.begin(),features_p.end(), map_func[1]);
              a[1] = *it; b[1] = track_p.at(static_cast<std::size_t>(it - features_p.begin()));
              // std::cout << "[ " << it->x <<' ' << it->y << " ] " ; std::cout << "[ " << track_p.at(it - features_p.begin()).x <<' ' << track_p.at(it - features_p.begin()).x << "]\n" ;
              it = std::min_element(features_p.begin(),features_p.end(), map_func[2]);
              a[2] = *it; b[2] = track_p.at(static_cast<std::size_t>(it - features_p.begin()));
              // std::cout << "[ " << it->x <<' ' << it->y << " ] " ; std::cout << "[ " << track_p.at(it - features_p.begin()).x <<' ' << track_p.at(it - features_p.begin()).x << "]\n" ;
              it = std::min_element(features_p.begin(),features_p.end(), map_func[3]);
              a[3] = *it; b[3] = track_p.at(static_cast<std::size_t>(it - features_p.begin()));
              // std::cout << "[ " << it->x <<' ' << it->y << " ] " ; std::cout << "[ " << track_p.at(it - features_p.begin()).x <<' ' << track_p.at(it - features_p.begin()).x << "]\n" ;

              for (int i=0;i<4;++i) {
                  cv::circle(*src, a[i], 3, cv::Scalar(0,255,0),-1);
                  cv::circle(*src, b[i], 3, cv::Scalar(0,0,255),-1);
                }

              vec_trans.push_back(cv::getPerspectiveTransform(b,a));
              //              { /// debug debug debug
              //        vec_trans        std::stringstream str;
              //                str << "[ " << image_count << " ]";
              //                for (int r=0;r<vec_trans.back().rows;++r) {
              //                    for (int c=0;c<vec_trans.back().cols;++c) {`
              //                       str << std::setw(13) << vec_trans.back().at<double>(r,c) << " , ";
              //                      }
              //                  }std::cout << str.str() << '\n';
              //              }

              // cv::warpPerspective(dst,dst, vec_trans.back(),dst.size());
              // -------------------------------  расчёт траектории -------------------------------------
              if(image_count++ % IMAGE_SZ == 499){
                  // track_log << "r (default) = \n" << vec_trans.at(vec_trans.size() - 499) << ";" << '\n';
                  double xp0 = 1280/2;
                  double yp0 = 720/2;

                  for (uint m = 1 ; m < vec_trans.size(); ++m) {

                      double a11 = vec_trans[m].at<double>(0,0);  double a12 = vec_trans[m].at<double>(0,1);  double a13 = vec_trans[m].at<double>(0,2);
                      double a21 = vec_trans[m].at<double>(1,0);  double a22 = vec_trans[m].at<double>(1,1);  double a23 = vec_trans[m].at<double>(1,2);
                      double a31 = vec_trans[m].at<double>(2,0);  double a32 = vec_trans[m].at<double>(2,1);  double a33 = vec_trans[m].at<double>(2,2);

                      double xP0 =  (xp0 * a11 + yp0 * a12 + a13) /
                          (xp0 * a31 + yp0 * a32 + a33);
                      double yP0 =  (xp0 * a21 + yp0 * a22 + a23) /
                          (xp0 * a31 + yp0 * a32 + a33);

                      for (uint i = m; i > 1; --i) {

                          double xkP0 =   (xP0 * vec_trans[i].at<double>(0,0) + yP0 * vec_trans[i].at<double>(0,1) + vec_trans[i].at<double>(0,2)) /
                              (xP0 * vec_trans[i].at<double>(2,0) + yP0 * vec_trans[i].at<double>(2,1) + vec_trans[i].at<double>(2,2));

                          yP0 =           (xP0 * vec_trans[i].at<double>(1,0) + yP0 * vec_trans[i].at<double>(1,1) + vec_trans[i].at<double>(1,2)) /
                              (xP0 * vec_trans[i].at<double>(2,0) + yP0 * vec_trans[i].at<double>(2,1) + vec_trans[i].at<double>(2,2));

                          xP0 = xkP0;
                          //yP0 = ykP0;

                        }

                      vec_x_y.push_back({xP0,yP0});
                      track_log << '[' << xP0 << ',' << yP0 << ']' << " \n"[m%10 == 9];
                    }

                  std::time_t t = std::time(nullptr); /// старый файл закроем новый откроем
                  std::tm tm = *std::localtime(&t);
                  std::stringstream st_time;
                  st_time << bfp.string();
                  st_time << std::put_time(&tm,"%Y_%m_%d_%H_%M_%S") ;
                  track_log = std::move(std::ofstream( std::string (st_time.str() + ".txt"))) ;

                  vec_trans.clear();                  /// очистим вектор и начнём всё по новой
                }
            }
        }else{
          std::cout << "<<<<<<<<<<<<<<<<<<<<<< no features >>>>>>>>>>>>>>>>>>>>>>>>>\n";
        }
      std::swap(track_p, features_p);
      cv::swap(gray_prev, gray);
    }

}

void Optical_flow_mod::b_start(void *pt){ closing = false; std::cout << __PRETTY_FUNCTION__ << '\n'; }

void Optical_flow_mod::b_stop(void *pt){ closing = true; std::cout << __PRETTY_FUNCTION__ << '\n'; }








//          cv::calcOpticalFlowPyrLK( gray_prev,      // первое восьми битное изображение
//                                    gray,           // второе входное изображение
//                                    features_p,     // исходный вектор точек для которых
//                                    track_p,        //
//                                    status,         // вектор состояния
//                                    err,            // вектор ошибок
//                                    cv::Size(31,31),// размер окна поиска
//                                    3,              // максимальный уровень пирамид
//                                    termcrit,
//                                    0, 0.001);
