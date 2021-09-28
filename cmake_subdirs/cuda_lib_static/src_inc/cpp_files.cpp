#include "cpp_files.h"

#include <iostream>

#include <cuda_runtime.h>
#include <driver_types.h>
#include <cuda.h>

Cpp_files::Cpp_files(){
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

Cpp_files::~Cpp_files(){
    std::cout << __PRETTY_FUNCTION__ << "\n";
}



