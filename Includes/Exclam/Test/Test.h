
#include "Exclam/Common.h"
#include "Exclam/Utils/Blob.hpp"

#define ARR_I_J(arr, i, row_len, j) arr[i * row_len + j]

void BLOB_TEST()
{
	exclam::Blob<float> x(4, 3);
	for (int i = 0; i < x.n; ++i)
	{
		for (int j = 0; j < x.w; ++j)
		{
			ARR_I_J(x.data, i, x.w, j) = (float)i + 1;
		}
	}
	x.Print();

	exclam::Blob<float> y(3, 2);
	for (int i = 0; i < y.n; ++i)
	{
		for (int j = 0; j < y.w; ++j)
		{
			ARR_I_J(y.data, i, y.w, j) = (float)j+1;
		}
	}
	y.Print();

	//TODO
	// 복사생성자? 대입연산자?
	// Destructor 호출을 제대로 하는지 모르겠다
	exclam::Blob<float> z = x * y; //여기서 만ㄷ르고
	z = x * y;	// 새로 할당했을 때 이전 메모리 free가 되나?
	printf("==\n");
	z.Print();

	z.transpose();
	printf("trans==\n");
	z.Print();


	exclam::Blob<float> trased = z.getTranspose();
	trased.Print();
}