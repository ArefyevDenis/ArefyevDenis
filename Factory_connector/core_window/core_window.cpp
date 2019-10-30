#include "core_window.h"

#include <QtWidgets>

#include <iostream>

Core_window::Core_window(QObject *parent)
    : QObject(parent),
      num_display(0)
{
  list_screen = QGuiApplication::screens(); /// колличество мониторов
  QList<QScreen *> list_screens = qApp->screens();

  for (auto kvp: list_screen) {     }

  sh_Left_Window = std::make_shared<Left_window>();
  sh_Left_Window.get()->setGeometry(list_screens[0]->geometry());
  sh_Left_Window.get()->showMaximized();

  //  sh_Right_Window = std::make_shared<Right_window>();
  //  sh_Right_Window.get()->setGeometry(list_screens[1]->geometry());

  std::cout << __PRETTY_FUNCTION__ << "\n";

}

Core_window::~Core_window(){
  std::cout << __PRETTY_FUNCTION__ << "\n";
}
