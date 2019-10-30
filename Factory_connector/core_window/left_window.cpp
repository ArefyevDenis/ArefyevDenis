#include "left_window.h"

#include <iostream>

#include "core_window/widgets/debug_2d.h"

Left_window::Left_window(QWidget *parent)
    : QWidget(parent)
{

  vQwidget.push_back(new Debug_2D);
  tabWidget.addTab(vQwidget.back(),tr("Debug_2D"));

  mainVLayout.addWidget(&tabWidget);

  setLayout(&mainVLayout);
  setWindowTitle(tr("QTabWidget Widget"));
  std::cout << __PRETTY_FUNCTION__ << "\n";

}

Left_window::~Left_window(){
  //  for (auto i : vQwidget) {  delete i;  }
  std::cout << __PRETTY_FUNCTION__ << "\n";
}
