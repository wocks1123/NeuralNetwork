/*
#include "Exclam/Layer.hpp"
#include <cstdio>

int main()
{
    auto l = TestLayer();
    l.Foo();
    //printf("hello\n");
    printf("%ld\n", sizeof(void*));

    return 0;
}
*/



//cpp_test.cpp
#include <stdio.h>
#include <vector>
#include "CudaTest/CudaTest.hpp"
#include "Exclam/Test/Test.h"

int sum_int(int a, int b)
{
    return a + b;
}

template<typename T>
class Model
{
private:
    std::vector<T> layers;

public:
    //Model(std::initializer_list<Layer<T>> l) : layers(l)
    Model(std::initializer_list<T> l) : layers(l)
    {

    }
    ~Model()
    {

    }
    void print()
    {
        for (unsigned int i = 0; i < layers.size(); i++)
        {
            printf("layer%d : %d\n", i, layers[i]);
        }
    }
};


int main()
{
    int a = 3, b = 4, c = 0, cu = 0;

    c = sum_int(a, b);

    CudaTest gpuacc;
    gpuacc.sum_cpu(a, b, &c);
    //gpuacc.sum_gpu(a, b, &cu);

    printf("1CPU Result : %d\n", c);
    printf("1GPU Result : %d\n", cu);
    //printf("size : %ud\n", sizeof(void*));

    Model<int> m = {1, 2, 3};
    m.print();

	BLOB_TEST();

    return 0;
}

