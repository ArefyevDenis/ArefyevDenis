#ifndef CU_FILES_H
#define CU_FILES_H

// выделить память на GPU
// скопировать данные из памяти CPU в память GPU
// осуществить запуск ядра <<<N,N>>>
// скопировать результаты вычислений в память CPU
// освободить память GPU

class CU_files
{
public:
  CU_files();

  CU_files(const CU_files&) = delete;
  CU_files& operator = (const CU_files&) = delete;

  CU_files(CU_files&&) = delete;
  CU_files& operator = (CU_files&&) = delete;

  ~CU_files();

  bool init();

  void start();

  void stop();

};

#endif // CPP_FILES_H
