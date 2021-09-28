#ifndef TAB_WIDGET_H
#define TAB_WIDGET_H

#include <QDockWidget>

class QHBoxLayout;

class Tab_widget :
    public QDockWidget
{
    Q_OBJECT
public:
    explicit Tab_widget(QWidget *parent = nullptr);

    explicit Tab_widget(const QString &title, QWidget *parent = nullptr);

    ~Tab_widget() override ;

private:

    QHBoxLayout* qhl;

    void init_widgets();

signals:

public slots:

};

#endif // TAB_WIDGET_H
