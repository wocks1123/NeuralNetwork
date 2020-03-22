//test.cuh



//#ifdef __cplusplus
//extern "C" {//&lt;-- extern 시작
//#endif
class CudaTest
{
public:
        CudaTest(void);
        virtual ~CudaTest(void);
        int sum_cpu(int a, int b, int* c);
        int sum_gpu(int a, int b, int* c);
};

//#ifdef __cplusplus
//}
//#endif

