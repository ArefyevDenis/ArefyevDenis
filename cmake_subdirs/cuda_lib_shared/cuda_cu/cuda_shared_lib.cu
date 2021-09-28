#include "cuda_shared_lib.h"

#include <iostream>

#include <cuda_runtime.h>
#include <driver_types.h>
#include <cuda.h>

Cuda_shared_lib::Cuda_shared_lib(int sz) :
  sz_( sz!=0 ? sz : SIZE)
{
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

Cuda_shared_lib::~Cuda_shared_lib(){
    std::cout << __PRETTY_FUNCTION__ << "\n";
}


__global__ void kernel(){

}

__global__ void add(int a, int b, int* c){
  *c = a + b;
}

__global__ void vec_add(int *a, int *b, int* c){

 //http://ssd.sscc.ru/sites/default/files/content/attach/332/cuda-2-program-arch.pdf
 // преобразование 2D координат в линейный номер
  int idx = blockIdx.x * blockDim.x  + threadIdx.x;
  int idy = blockIdx.y * blockDim.y  + threadIdx.y;

   c[idx] = a[idx] + b[idx];

}

#define N (2048*2048)
#define THREADS_PER_BLOCK 512

__global__ void dot( int *a, int *b, int *c ) {

  __shared__ int temp[THREADS_PER_BLOCK];

  int index = threadIdx.x + blockIdx.x*blockDim.x;

  temp[threadIdx.x] = a[index] * b[index];

  __syncthreads();

  if( 0 == threadIdx.x ) {

      int sum = 0;

      for( int i = 0; i < THREADS_PER_BLOCK; i++ )
        sum += temp[i];

      *c += sum;

      atomicAdd( c , sum );

    }
}

// выделить память на
// скопировать данные из памяти CPU в память GPU
// осуществить запуск ядра <<<N,N>>>
// скопировать результаты вычислений в память CPU
// освободить память GPU

bool Cuda_shared_lib::init(){
  cudaError_t error_id ;

  if( (error_id = cudaMalloc((void **)&v_a, sizeof (int))) != cudaSuccess )
    return error_id;
  if( (error_id = cudaMalloc((void **)&v_b, sizeof (int))) != cudaSuccess )
    return error_id;
  if( (error_id = cudaMalloc((void **)&v_c, sizeof (int))) != cudaSuccess )
    return error_id;

}

void Cuda_shared_lib::apply(){

  /// зачем делать так если есть define
  dim3 dim_grid{32};
  dim3 dim_block{32};

 dot<<<N/THREADS_PER_BLOCK,THREADS_PER_BLOCK>>>(v_a,v_b,v_c);

}

bool Cuda_shared_lib::de_init(){
  cudaFree(v_a);
  cudaFree(v_b);
  cudaFree(v_c);
}

void Cuda_shared_lib::start(){}

void Cuda_shared_lib::stop(){}


//#define N_BLOCKS 1024;
//#define N_THREADS 1024;

//template<class T1, class T2>
//struct prefetch :
//    public thrust::unary_function<T1,T2>
//{
//  const T1* data;
//  prefetch(T1* _data) :
//    data(_data)
//  {};

//  // This method prefetchs the previous grid of data point into the L2.
//  __device__  T1 operator()(T2 i) {

//    if( (i-N_BLOCKS*N_THREADS) > 0) { //prefetch the previous grid
//        const T1 *pt = &data[i − (N_BLOCKS*N_THREADS)];
//        asm volatile ("prefetch.global.L2 [%0];"::"l"(pt) );
//      }
//    return data[i];

//  }
//};

//cudaError_t error_id ;

//int c;
//int *dev_c;

//if( (error_id = cudaMalloc((void **)&dev_c, sizeof (int))) != cudaSuccess )
//  return error_id;

//kernel<<<1,1>>>();

//add<<<1,1>>>(2,7,dev_c);

//if( (error_id = cudaMemcpy( &c, dev_c, sizeof (int), cudaMemcpyDeviceToHost) ) != cudaSuccess )
//  return error_id;

//std::cout << " 2 + 7 = " << c << "\n";

//cudaFree(dev_c);

//return 0;
