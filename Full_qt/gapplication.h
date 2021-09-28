#ifndef GAPPLICATION_H
#define GAPPLICATION_H

#include <QApplication>

#include "widgets/main_window.h"
#include <common/signal_handler.h>
#include <common/unique_app.h>
#include <common/encapsulate.h>


class GApplication :
        public QApplication
{
    Q_OBJECT
public:

    GApplication(int &argc, char **argv, int = ApplicationFlags);

    ~GApplication() override;

private:

    void init();

    Unique_app      ua_; // проверяем приложение на уникальность
    Signal_handler  sh_; // создаём обработчики сигналов
    Main_window     mw_; // создаём главное окно приложения
    Encapsulate     en_; // backend

signals:

public slots:

   void slot_commitDataRequest(QSessionManager &);
   void slot_saveStateRequest(QSessionManager &);

};

#endif // GAPPLICATION_H
