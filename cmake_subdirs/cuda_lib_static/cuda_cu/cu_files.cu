#include "cu_files.h"

#include <iostream>

#include <cuda_runtime.h>
#include <driver_types.h>
#include <cuda.h>

CU_files::CU_files(){
  std::cout << __PRETTY_FUNCTION__ << "\n";
  int device_CU = 0;

  cudaError_t error_id = cudaGetDeviceCount(&device_CU);

  if(error_id == cudaSuccess ){
      std::cout << "device_CU: " << device_CU << "\n";

      for (int i = 0; i < device_CU; ++i) {
          cudaSetDevice(i);
          cudaDeviceProp cdp;

          if( (error_id = cudaGetDeviceProperties(&cdp,i)) != cudaSuccess )
            break;
          std::cout << "cudaGetDeviceProperties: " << cdp.name << "\n";

          int drv_get_ver{0};
          if( (error_id = cudaDriverGetVersion(&drv_get_ver)) != cudaSuccess )
            break;
          std::cout << "cudaDriverGetVersion: " <<drv_get_ver << "\n";

          int run_time_ver{0};
          if( (error_id = cudaRuntimeGetVersion(&run_time_ver)) != cudaSuccess )
            break;
          std::cout << "cudaRunTimeGetVersion: " <<run_time_ver << "\n";

        }

    }else{
      std::cout << " NO CUDA DEVICES \n";
    }

}

CU_files::~CU_files(){
    std::cout << __PRETTY_FUNCTION__ << "\n";
}


__global__ void kernel(){

}

__global__ void add(int a, int b, int* c){
  *c = a + b;
}

// выделить память на
// скопировать данные из памяти CPU в память GPU
// осуществить запуск ядра <<<N,N>>>
// скопировать результаты вычислений в память CPU
// освободить память GPU

bool CU_files::init(){
  cudaError_t error_id ;

  int c;
  int *dev_c;

  if( (error_id = cudaMalloc((void **)&dev_c, sizeof (int))) != cudaSuccess )
    return error_id;

  kernel<<<1,1>>>();

  add<<<1,1>>>(2,7,dev_c);

  if( (error_id = cudaMemcpy( &c, dev_c, sizeof (int), cudaMemcpyDeviceToHost) ) != cudaSuccess )
    return error_id;

  std::cout << " 2 + 7 = " << c << "\n";

  cudaFree(dev_c);

  return 0;

}


void CU_files::start(){}

void CU_files::stop(){}

