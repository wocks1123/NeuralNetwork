#pragma once

#include <cstdio>
#include <cmath>
#include <vector>

#include "Exclam/Common.h"
#include "Exclam/Layers/Layer.hpp"

#ifndef _JCEXCLAM_SOFTMAX_WITH_LOSS_LAYER_HPP_
#define _JCEXCLAM_SOFTMAX_WITH_LOSS_LAYER_HPP_

NAME_SPACE_S

template <typename T>
class SoftmaxWithLossLayer : public Layer<T>
{
private:
	Blob<T> p;


public:
	SoftmaxWithLossLayer(size_t in) : Layer<T>(in, in)
	{
		//p = Blob<T>(in, in);
	}
	~SoftmaxWithLossLayer()
	{

	}

public:

	virtual Blob<T> foward(const Blob<T>& t) override
	{
		std::vector<int> target(t.n, 0);

		p = Blob<T>(t.n, t.w);

		//softmax
		for (int i = 0; i < t.n; ++i)
		{
			T sum = 0;
			for (int j = 0; j < t.w; ++j)
			{
				float val = exp(ARR_I_J(t.data, i, t.w, j));
				sum += val;
				if (ARR_I_J(t.data, i, t.w, j) == 1)
				{
					target[i] = j;
				}
			}

			for (int j = 0; j < t.w; ++j)
			{
				ARR_I_J(p.data, i, p.w, j) = exp(ARR_I_J(t.data, i, t.w, j)) / sum;
			}
		}
		p.Print();


		//loss
		Blob<T> loss(1, 1);
		loss.data[0] = 0;
		for (int i = 0; i < p.n; ++i)
		{
			T sum = 0;
			for (int j = 0; j < p.w; ++j)
			{
				printf("sum : %f = %f + %f\n", sum, ARR_I_J(t.data, i, t.w, j), log(ARR_I_J(p.data, i, p.w, j)));
				sum += ARR_I_J(t.data, i, t.w, j) * log(ARR_I_J(p.data, i, p.w, j));
			}
			loss.data[0] += -sum;
		}

		//local gradient
		for (int i = 0; i < p.n; ++i)
		{
			printf("target[i] : %d\n", target[i]);
			ARR_I_J(p.data, i, p.w, target[i]) -= 1;
		}


		return loss;
	}

	virtual Blob<T> backward(const Blob<T>& dL, const Blob<T>& x) override
	{
		return p;
	}


};

NAME_SPACE_E

#endif