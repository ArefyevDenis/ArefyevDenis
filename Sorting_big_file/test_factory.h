#ifndef TEST_FACTORY_H
#define TEST_FACTORY_H

#include <QWidget>

class File_server;

//namespace TFC {

  class AA:
      public QWidget
  {
    Q_OBJECT
  public:

    explicit AA(QWidget *parent = nullptr);

    ~AA()override;

  protected:

    File_server* p_fs{nullptr};

  };


//}


#endif // TEST_FACTORY_H
