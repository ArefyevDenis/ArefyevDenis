#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class Main_window :
        public QMainWindow
{
    Q_OBJECT
public:
    explicit Main_window(QWidget *parent=nullptr);

    ~Main_window()override;

   void contextMenuEvent(QContextMenuEvent *event) override;

signals:

public slots:

    void file_Relog_Action(bool);

    void file_Exit_Action(bool);

};

#endif // MAIN_WINDOW_H
