#ifndef DOC_WIDGET_H
#define DOC_WIDGET_H

#include <QDockWidget>

class QHBoxLayout;
class Q_table_view;

class Doc_widget :
    public QDockWidget
{
  Q_OBJECT
public:
  explicit Doc_widget(QWidget *parent = nullptr);

  explicit Doc_widget(const QString &title, QWidget *parent = nullptr);

  ~Doc_widget() override ;

private:

  Q_table_view* q_t_w{nullptr};

  QHBoxLayout* qhl{nullptr};

  void init_widgets();

signals:

public slots:

};

#endif // DOC_WIDGET_H
