#ifndef BASE_QT_THREAD_H
#define BASE_QT_THREAD_H

#include <QThread>
#include "base_factory.h"

class Base_qt_thread :
    public QThread
{
  Q_OBJECT
public:
  explicit Base_qt_thread(QObject *parent = nullptr);

  Base_qt_thread(const Base_qt_thread&)               = delete;
  Base_qt_thread(Base_qt_thread&&)                    = delete;
  Base_qt_thread& operator = (const Base_qt_thread&)  = delete;
  Base_qt_thread& operator = (Base_qt_thread&&)       = delete;

  template<typename TT>
  Base_qt_thread(std::initializer_list<TT> il)        = delete;

  ~Base_qt_thread() override;

signals:

public slots:

};

#endif // BASE_QT_THREAD_H
