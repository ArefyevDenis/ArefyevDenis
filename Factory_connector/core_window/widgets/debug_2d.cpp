#include "debug_2d.h"

#include <iostream>
#include <QDir>

#include <boost/algorithm/string.hpp>

#include <chrono>

/// https://evileg.com/ru/post/80/
/// https://evileg.com/ru/knowledge/qt/
/// http://compvis.readthedocs.io/en/latest/index.html
/// http://www.learnopencv.com/parallel-pixel-access-in-opencv-using-foreach/

namespace  {

  unsigned long tm_scan_count {0};
  unsigned long tm_test_count {0};

  std::chrono::system_clock::time_point start;

}

Debug_2D::~Debug_2D(){
  std::cout << __PRETTY_FUNCTION__ << "\n";
}


Debug_2D::Debug_2D(QWidget *parent)
    :  QWidget(parent)
{

  std::string src_pwd(PATH_SRC_PWD);
  std::string out_pwd(PATH_OUT_PWD);

  std::cout << src_pwd << "\n";
  std::cout << out_pwd << "\n";

  main_vbox_layout = new QVBoxLayout;

 pb_start =  new QPushButton(QObject::tr("START"));
  connect(pb_start, &QPushButton::clicked, [this](bool checked){
    tm_scan.start(TIMING);
    tm_test.start(50); // период 1 msec
    start = std::chrono::high_resolution_clock::now();
  });

 pb_stop = new QPushButton(QObject::tr("STOP"));
  connect(pb_stop, &QPushButton::clicked, [this](bool checked){
    tm_scan.stop();
    tm_test.stop();
  });

  /// создать Qcustomwidget
  vpQCustom.push_back( new QCustomPlot(parent) );
  vpQCustom.back()->setObjectName(QString::fromUtf8("UpLPlot"));
  for(int i=0,step=4,cv=252;i<NUMGRAPHICS;++i){
      vpQCPCurve.push_back(new QCPCurve( vpQCustom.back()->xAxis,  vpQCustom.back()->yAxis));
      vpQCustom.back()->hasPlottable(vpQCPCurve.back());
      unsigned int R = cv%255;unsigned int G = (cv-60>0) ? (cv-60)%255:0;unsigned int B=0; cv = (cv-10)%255;
      vpQCPCurve.back()->setPen(QPen(QColor(R,G,B)));
      //vpQCPCurve.back()->setLineStyle(QCPCurve::lsNone);//lsNone//
      //vpQCPCurve.back()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, 6));
      vElapsed.push_back(QVector<double>());
      vOut.push_back(QVector<double>());
    }
  vpQCustom.back()->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
  vpQCustom.back()->axisRect()->setupFullAxesBox();
  vpQCustom.back()->yAxis->setRange(0, 18);
  //vpQCustom.back()->yAxis->rescale();
  vpQCustom.back()->xAxis->setRange(0, 10.0);
  //vpQCustom.back()->xAxis->rescale();

  //vpLabels.push_back(new QLabel);
  //pHBoxLayout->addWidget(vpLabels.back(),100,Qt::AlignHCenter);
  main_vbox_layout->addWidget(vpQCustom.back()/*,1,Qt::AlignAbsolute*/);
  main_vbox_layout->addWidget(pb_start/*,1,Qt::AlignAbsolute*/);
  main_vbox_layout->addWidget(pb_stop/*,1,Qt::AlignAbsolute*/);
  // pHBoxLayout->addLayout(vpGridLayout.back());
  // pHBoxLayout->addStretch();

  setLayout(main_vbox_layout);  /// финальный этап

  connect(&tm_scan, SIGNAL(timeout()), this, SLOT(slot_scanning_exit()));

  connect(&tm_test, SIGNAL(timeout()), this, SLOT(slot_producer_data()));

  //sc.time_start();

}

void Debug_2D::slot_rcv_udp_msg(std::string str){
  //std::cout << " slot " << str << "\n";
  std::vector<std::string> v_str;
  boost::split(v_str, str, [](char c){return c == ' ';}); // разбить строку на подстроки
  int fd = std::stoi(v_str[1]);
  int dd = std::stoi(v_str[3]);

//  if(vOut[fd].empty()){
//      vElapsed[fd].push_back(sc.elapsed());    vOut[fd].push_back(fd + dd*0.8);
//    }else{
//      std::cout << " back : " << vOut[fd].back() << "\n";
//      vElapsed[fd].push_back(sc.elapsed());    vOut[fd].push_back(vOut[fd].back());
//      vElapsed[fd].push_back(sc.elapsed());    vOut[fd].push_back(fd + dd*0.8);
//    }

  //std::cout << " int fd " << fd << " int dd " << dd << "\n";

}

// сформировать тестовые вектора
void Debug_2D::slot_producer_data(){

  tm_test_count++;

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;

  //std::cout << elapsed.count() << " \n"[tm_test_count%8 == 7];

  uint ng = vElapsed.size();

  if(tm_test_count%2){
      for(int i=0; i< vpQCPCurve.size();++i){
          vElapsed[i].push_back( elapsed.count());    vOut[i].push_back(i);
          vElapsed[i].push_back( elapsed.count());    vOut[i].push_back(i + 0.8);
        }
    }else{
      for(int i=0; i< vpQCPCurve.size();++i){
          vElapsed[i].push_back( elapsed.count());    vOut[i].push_back(i + 0.8);
          vElapsed[i].push_back( elapsed.count());    vOut[i].push_back(i);
        }
    }

}

void Debug_2D::slot_scanning_exit(){

  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = finish - start;

  //std::cout << elapsed.count() << " \n"[tm_scan_count%8 == 7];

  if(tm_scan_count++ % PSCAN){
      for(int i=0; i < vpQCPCurve.size();++i){
          if(!vOut[i].empty()){
              vElapsed[i].push_back(elapsed.count());    vOut[i].push_back(vOut[i].back());
            }
          vpQCPCurve[i]->setData(vElapsed[i], vOut[i]);
        }
    }else{      // период развёртки завершён
      for(int i=0; i< vElapsed.size();++i){
          vElapsed[i].clear();    vOut[i].clear();
        }
      start = finish; // перезапуск время только по завершению периода развёртки
    }
  vpQCustom.back()->replot();

}

// накапливаем данные для отрисовки
//void Qcustom_osciloscop::slot_save_data(unsigned char*, double ,double){}
