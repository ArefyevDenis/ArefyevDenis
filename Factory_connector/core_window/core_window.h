#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <QObject>
#include <memory>
#include <vector>

#include "right_window.h"
#include "left_window.h"

class Core_window :
    public QObject
{
Q_OBJECT
public:

explicit Core_window(QObject *parent = nullptr);

  ~Core_window()                             ;

signals:

public slots:

private:

protected:

  int                             num_display;
  QList<QScreen *>                list_screen;
  std::shared_ptr<Left_window>    sh_Left_Window;
  std::shared_ptr<Right_window>   sh_Right_Window;

};

#endif // CORE_WINDOW_H
