#ifndef CUDA_SHARED_LIB_H
#define CUDA_SHARED_LIB_H

// выделить память на GPU
// скопировать данные из памяти CPU в память GPU
// осуществить запуск ядра <<<N,N>>>
// скопировать результаты вычислений в память CPU
// освободить память GPU

class Cuda_shared_lib
{
  enum {SIZE = 1024
//        N = 2048*2048,
//        THREADS_PER_BLOCK = 512
       };
public:
  Cuda_shared_lib(int sz = 0);

  Cuda_shared_lib(const Cuda_shared_lib&) = delete;
  Cuda_shared_lib& operator = (const Cuda_shared_lib&) = delete;

  Cuda_shared_lib(Cuda_shared_lib&&) = delete;
  Cuda_shared_lib& operator = (Cuda_shared_lib&&) = delete;

  ~Cuda_shared_lib();

  bool init();
  bool de_init();

  void start();
  void stop();

  void apply();

private:

  int *v_a;
  int *v_b;
  int *v_c;

  int sz_{-1};

};

#endif // CUDA_SHARED_LIB_H
