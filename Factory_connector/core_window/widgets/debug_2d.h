#ifndef DEBUG_2D_H
#define DEBUG_2D_H

#include <QtGlobal>
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#include <QtGui>
#include <QWidget>
#else
#include <QtWidgets>
#endif

#include "core_window/qcustomplot.h"

class Debug_2D :
    public QWidget
{
  Q_OBJECT
  enum { ROWS = 4, COLS = 8, TROWS=8,TCOLS=8};
public:

  explicit Debug_2D(QWidget *parent = 0);

  Debug_2D(const Debug_2D&)               = delete;
  Debug_2D(Debug_2D&&)                    = delete;
  Debug_2D& operator = (const Debug_2D&)  = delete;
  Debug_2D& operator = (Debug_2D&&)       = delete;
  Debug_2D(std::initializer_list<int> il)     = delete;

  ~Debug_2D();

private:

  enum {BUTTONS = 3, LABELS = 6, SLIDERS = 6, SLI_LAB_BUT = LABELS+SLIDERS+BUTTONS, NUMGRAPHICS = 16,
    TIMING  = 1,          // период срабатывания таймера msec
    HZ      = 1000/TIMING,  // частота таймера
    PSCAN   = HZ         // время развёртки 10 секунд
  };

  enum {SIZE_TEXT = 2048};

  QHBoxLayout* main_hbox_layout;
  QVBoxLayout* main_vbox_layout;

  QPushButton* pb_start;
  QPushButton* pb_stop;

  QTimer tm_scan;   // генератор развёртки
  QTimer tm_test;   // генератор тестовых данных

  std::vector<QCustomPlot*>     vpQCustom;
  QVector<QCPCurve *>           vpQCPCurve;
  QVector< QVector<double> >    vElapsed;
  QVector< QVector<double> >    vOut;

signals:

public slots:

  void slot_rcv_udp_msg(std::string);
  void slot_producer_data();                               // поставщик данных
  void slot_scanning_exit();                               // период развёртки завершён


};

#endif // DEBUG_2D_H
