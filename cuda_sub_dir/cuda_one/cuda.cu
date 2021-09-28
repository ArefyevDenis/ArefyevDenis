
#include <stdio.h>

static void HandleError( cudaError_t err,  const char *file,     int line ) {
    if (err != cudaSuccess) {
        ::printf( "%s in %s at line %d\n", cudaGetErrorString( err ),  file, line );
        ::exit( EXIT_FAILURE );
    }
}

#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

#define N 100000

#define cudaCheckErrors(msg) \
    do { \
        cudaError_t __err = cudaGetLastError(); \
        if (__err != cudaSuccess) { \
            fprintf(stderr, "Fatal error: %s (%s at %s:%d)\n",msg, cudaGetErrorString(__err),  __FILE__, __LINE__); \
            fprintf(stderr, "*** FAILED - ABORTING\n"); \
            exit(1); \
        } \
    } while (0)

__global__ void add( int *a, int *b, int *c ) {
    int tid = blockIdx.x;    // this thread handles the data at its thread id
    if (tid < N)
        c[tid] = a[tid] + b[tid];
}

extern "C" void Cuda_Main_Test1(){
    int a[N], b[N], c[N];
    int *dev_a, *dev_b, *dev_c;

    // allocate the memory on the GPU
    HANDLE_ERROR( cudaMalloc( (void**)&dev_a, N * sizeof(int) ) );
    HANDLE_ERROR( cudaMalloc( (void**)&dev_b, N * sizeof(int) ) );
    HANDLE_ERROR( cudaMalloc( (void**)&dev_c, N * sizeof(int) ) );
   // cudaCheckErrors("cudamalloc fail");
    // fill the arrays 'a' and 'b' on the CPU
    for (int i=0; i<N; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    // copy the arrays 'a' and 'b' to the GPU
    HANDLE_ERROR( cudaMemcpy( dev_a, a, N * sizeof(int),    cudaMemcpyHostToDevice ) );
    //HANDLE_ERROR( cudaMemcpy( dev_b, b, N * sizeof(int),    cudaMemcpyHostToDevice ) );

    cudaError_t status = cudaMemcpy(dev_b, b, N * sizeof(int),    cudaMemcpyHostToDevice);
  //  cudaCheckErrors("cuda memcpy fail");
    //sleep(1);
    add<<<N,1>>>(dev_a,dev_b,dev_c);
   // sleep(1);
    // copy the array 'c' back from the GPU to the CPU
    HANDLE_ERROR( cudaMemcpy( c, dev_c, N * sizeof(int),    cudaMemcpyDeviceToHost ) );
//    if (status == cudaSuccess) {
//         printf( "0 CUDA Error: %s \n", cudaGetErrorString( status ) );
//    }
//    if (status != cudaSuccess) {
//         printf( "1 CUDA Error:  %s  \n", cudaGetErrorString( status ) );
//       // cout << "CUDA Error: " << cudaGetErrorString( cuerr ) << endl
//    }
//    cudaCheckErrors("cudamemcpy or cuda kernel fail");
   // sleep(1);
    // display the results
    for (int i=0; i<N; i++) {
      //  printf( "%d + %d = %d\n", a[i], b[i], c[i] );
        printf( "%d%c ", c[i],((i%8==7)?'\n':' '));
    }

    printf( "Start CPU add \n ");
    for (int i=0; i<N; i++) {
     c[i]=a[i]+b[i];
        //printf( "%d%c ", c[i],((i%8==7)?'\n':' '));
    }
     printf( "Stop CPU add \n ");
    // free the memory allocated on the GPU
    HANDLE_ERROR( cudaFree( dev_a ) );
    HANDLE_ERROR( cudaFree( dev_b ) );
    HANDLE_ERROR( cudaFree( dev_c ) );

}
