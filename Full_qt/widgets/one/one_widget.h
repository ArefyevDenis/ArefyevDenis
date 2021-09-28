#ifndef ONE_WIDGET_H
#define ONE_WIDGET_H

#include <QWidget>


#include <QDockWidget>

class QTreeWidget;

class One_widget :
        public QDockWidget
{
    Q_OBJECT
public:
    explicit One_widget(QWidget *parent = nullptr);

    explicit One_widget(const QString &title, QWidget *parent = nullptr);

    ~One_widget() override ;

private:

    void init_widgets();

signals:

public slots:

};


#endif // ONE_WIDGET_H
