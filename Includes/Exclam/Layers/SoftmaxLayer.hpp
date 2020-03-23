#pragma once

#include <cstdio>
#include <cmath>

#include "Exclam/Common.h"
#include "Exclam/Layers/Layer.h"

#ifndef _JCEXCLAM_SOFTMAX_LAYER_
#define _JCEXCLAM_SOFTMAX_LAYER_

NAME_SPACE_S

template <typename T>
class SoftmaxLayer : public Layer<T>
{
private:
	Blob<T> W;


public:
	SoftmaxLayer(size_t in)
	{

	}
	~SoftmaxLayer()
	{

	}

public:

	//일단 단순 순회...
	virtual Blob<T> foward(const Blob<T>& x) override
	{
		Blob<T> res(x.n, x.w);
		for (int i = 0; i < x.n; i++)
		{
			T sum = 0;
			for (int j = 0; j < x.w; j++)
			{
				sum += exp(x.data[i][j]);
			}

			for (int j = 0; j < x.w; j++)
			{
				res.data[i][j] = exp(x.data[i][j]) / sum;
			}
		}


		return res;
	}

	virtual Blob<T> backward(const Blob<T>& dL, const Blob<T>& x) override
	{
		//this->delta = dL.getTranspose() * x;
		//return dL * W.getTranspose();
		return Blob<T>();
	}


};



NAME_SPACE_E

#endif