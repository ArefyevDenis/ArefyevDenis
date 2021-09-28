#include "main_window.h"

#include <QContextMenuEvent>

#include <common/logger.h>

#include "derived/q_qmenu.h"
#include "derived/q_qmenubar.h"

#include "dialog/login_dialog.h"

#include "widgets/tree_widget.h"
#include "widgets/doc_widget.h"
#include "widgets/one/one_widget.h"
#include "widgets/tab_widget.h"

#include "common/afactory.h"

Main_window::Main_window(QWidget *parent) :
  QMainWindow(parent)
{
  LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
  Q_QMenuBar *topMenuBar = new Q_QMenuBar(this);
  QMenu* fileSubMenu = topMenuBar->addMenu(tr("&Файл"));
  auto *fileRelogAction = fileSubMenu->addAction(tr("&Релогин..."));
  auto *fileExitAction  = fileSubMenu->addAction(tr("&Выход"));
  connect(fileRelogAction, &QAction::triggered, this, &Main_window::file_Relog_Action);
  connect(fileExitAction, &QAction::triggered, this, &Main_window::file_Exit_Action);

  QMenu* viewSubMenu = topMenuBar->addMenu(tr("&Вид"));
  // класс дерево виджетов должен знать всё обо всех виджетах
  // для этого они должны быть зарегистрированы в фабрике объектов
  Tree_widget* tw = new Tree_widget(tr("Зарегистрированные виджеты научиться их вызывать"),this);
  addDockWidget(Qt::LeftDockWidgetArea, tw);

  Doc_widget* dw = new Doc_widget(tr("Doc_widget"),this);
  addDockWidget(Qt::LeftDockWidgetArea, dw);

  Tab_widget* tb = new Tab_widget(tr("Tab_widget"),this);
  addDockWidget(Qt::LeftDockWidgetArea, tb);

  viewSubMenu->addAction(tw->toggleViewAction());
  viewSubMenu->addAction(dw->toggleViewAction());
  viewSubMenu->addAction(tb->toggleViewAction());
  viewSubMenu->addSeparator();

  setMenuBar(topMenuBar);

  // как-то так нужно добавить все зарегистрированые в фабрике объектов виджеты
  // for (;;) {      viewSubMenu->addAction(tw->toggleViewAction());    }
  //int a __attribute__((optimize(0))) {1} ;
  //    One_widget* ow = dynamic_cast<One_widget*>(AFactory::create_object("One_widget")) ;
  //    addDockWidget(Qt::LeftDockWidgetArea, ow);
  // QObject* ptr = AFactory::create_object("One_widget");

}

Main_window::~Main_window()
{
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}


void Main_window::file_Relog_Action(bool){
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
    Login_dialog ld(this);
    ld.exec();
}

void Main_window::file_Exit_Action(bool){
    LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
}

void Main_window::contextMenuEvent(QContextMenuEvent *event){
     LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
    Q_QMenu menu(this);
    auto *act_1 = menu.addAction(tr("---1---") );
    auto *act_2 = menu.addAction(tr("---2---") );
    menu.exec(event->globalPos());
}
