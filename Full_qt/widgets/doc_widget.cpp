#include "doc_widget.h"

#include "common/logger.h"
#include <derived/q_table_view.h>

Doc_widget::Doc_widget(QWidget *parent) :
  QDockWidget(parent)
{
  LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
  init_widgets();
}


Doc_widget::Doc_widget(const QString &title, QWidget *parent) :
  QDockWidget(title, parent)
{
  LOG_DEBUG(nullptr,__PRETTY_FUNCTION__);
  init_widgets();
}

Doc_widget::~Doc_widget()
{

}

void Doc_widget::init_widgets()
{
  if(q_t_w!=nullptr)
    return;

  q_t_w = new Q_table_view(16,16,this);

  setWidget(q_t_w);
}
