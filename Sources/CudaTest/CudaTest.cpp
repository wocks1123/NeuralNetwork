//
// Created by User on 2020-03-23.
//

#include "CudaTest/CudaTest.hpp"
#include <stdio.h>


CudaTest::CudaTest(void)
{

}

CudaTest::~CudaTest(void)
{

}


int CudaTest::sum_cpu(int a, int b, int *c)
{
    *c = a + b;

    return true;
}
