#ifndef OPTICAL_FLOW_MOD_H
#define OPTICAL_FLOW_MOD_H

#include <fstream>
#include <vector>
#include <map>
#include <opencv2/core/core.hpp>
#include <opencv2/video/tracking.hpp>
#include <boost/filesystem.hpp>

#include "base_factory.h"
#include "logger.h"

class Optical_flow_mod :
    public Base_factory
{
  enum{IMAGE_SZ = 500};
public:
  Optical_flow_mod(int mc = 1000, double ql = 0.001, double md = 50.);

  ~Optical_flow_mod()       ;//               override;

  virtual void b_apply(void *)               override;
  virtual void b_start(void *)               override;
  virtual void b_stop(void *)                override;
 inline virtual const char* b_type_name()   override { return typeid (this).name(); }

  void  calculate(void *);

private:

  boost::filesystem::path             bfp;          /// путь по которому сохраняется файл

  bool closing{true}; // работа только после старта

  Logger lg;
  std::ofstream track_log;

  std::map<uint,std::vector<cv::Point2f>>                       points;       //
  std::map<uint,std::vector<cv::Point2f>>                       send_points;  // применяется только для отладки (щтправим красивые точки на виджет)
  std::map<int,std::function<bool(cv::Point2f&,cv::Point2f&)>>  map_func;     // алгоритмы сортировки

  std::vector<cv::Mat> vec_trans;
  double XP_0 {0};//{1280/2} ;
  double YP_0 {0};//{720/2} ;
  std::vector<std::pair<double,double>> vec_x_y;
  cv::Mat gray;                         // current gray-level image
  cv::Mat gray_prev;                    // previous gray-level image
  ulong image_count{0};                 // cчётчик кадров
  std::vector<cv::Point2f> features_p;  // detected features обнаруженные особенные точки
  std::vector<cv::Point2f> track_p;     //
  int max_count;                        // maximum number of features to detect
  double qlevel;                        // quality level for feature detection
  double minDist;                       // min distance between two points
  std::vector<uchar> status;            // состояние отслеживаемых объектов
  std::vector<float> err;

  cv::TermCriteria termcrit;

  cv::Ptr<cv::SparsePyrLKOpticalFlow> of_ptr;

};

#endif // OPTICAL_FLOW_MOD_H
