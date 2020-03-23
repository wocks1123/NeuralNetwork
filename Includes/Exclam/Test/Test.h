
#include "Exclam/Common.h"
#include "Exclam/Utils/Blob.hpp"
#include "Exclam/Layers/LinearLayer.hpp"
#include "Exclam/Layers/SoftmaxWithLossLayer.hpp"


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

void LINEAR_LAYER_TEST()
{
	exclam::Blob<float> x(4, 3);
	exclam::LinearLayer<float> l(3, 2);

	auto y = l.foward(x);

	exclam::Blob<float> dL(4, 2);
	auto dLdx = l.backward(dL, x);

	y.Print();
	dLdx.Print();
}

void SOFT_MAX_TEST()
{
	exclam::Blob<float> x(1, 3);
	for (int i = 0; i < x.n; ++i)
	{
		for (int j = 0; j < x.w; ++j)
		{
			ARR_I_J(x.data, i, x.w, j) = 0;
		}
	}
	x.Print();

	exclam::Blob<float> t(1, 3);
	for (int i = 0; i < t.n; ++i)
	{
		for (int j = 0; j < t.w; ++j)
		{
			ARR_I_J(t.data, i, t.w, j) = 0;
		}
		ARR_I_J(t.data, i, t.w, i) = 1;
	}
	t.Print();

	exclam::SoftmaxWithLossLayer<float> l(3);

	exclam::Blob<float> loss = l.foward(t);
	loss.Print();


}