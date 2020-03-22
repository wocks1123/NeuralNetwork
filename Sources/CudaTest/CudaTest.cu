//test.cu
#include "CudaTest/CudaTest.hpp"
#include <stdio.h>

#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>

__global__ void sum_kernel(int a, int b, int *c)
{
        int tid = blockIdx.x * blockDim.x + threadIdx.x;
        printf("tid : %d\n", tid);
        c[tid] = a + b;
}

int CudaTest::sum_gpu(int a, int b, int *c)
{
        int *f;
        cudaMalloc((void**)&f, sizeof(int)* 1);
        cudaMemcpy(f, c, sizeof(int)* 1, cudaMemcpyHostToDevice);

        sum_kernel <<<1, 1>>>(a, b, f);
        cudaMemcpy(c, f, sizeof(int)* 1, cudaMemcpyDeviceToHost);
        cudaFree(f);

        return true;
}

