#ifndef TREE_WIDGET_H
#define TREE_WIDGET_H

#include <QDockWidget>

class QTreeWidget;
class QHBoxLayout;

class Tree_widget :
    public QDockWidget
{
    Q_OBJECT
public:
    explicit Tree_widget(QWidget *parent = nullptr);

    explicit Tree_widget(const QString &title, QWidget *parent = nullptr);

    ~Tree_widget() override ;

private:

    QTreeWidget* qtw;
    QHBoxLayout* qhl;

    void init_widgets();

signals:

public slots:

};

#endif // TREE_WIDGET_H
