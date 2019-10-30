#ifndef LEFT_WINDOW_H
#define LEFT_WINDOW_H

#include <QTabWidget>
#include <QVBoxLayout>

class Left_window :
    public QWidget
{
  Q_OBJECT
public:
  explicit Left_window(QWidget *parent = nullptr);

  Left_window(const Left_window&)               = delete;
  Left_window( Left_window&&)                   = delete;
  Left_window& operator = (const Left_window&)  = delete;
  Left_window& operator = ( Left_window&&)      = delete;

  ~Left_window();

  std::vector<QWidget*>     vQwidget;

signals:

public slots:

private:

  enum {COUNT_TAB_WIDGET = 16};

  QVBoxLayout mainVLayout  ;

  QTabWidget tabWidget     ;

};
#endif // LEFT_WINDOW_H
