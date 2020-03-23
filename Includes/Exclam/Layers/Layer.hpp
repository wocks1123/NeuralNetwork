#pragma once

#include <cstdio>
#include <cstdlib>

#include "Exclam/Common.h"
#include "Exclam/Utils/Blob.hpp"

#ifndef _JCEXCLAM_LAYER_HPP_
#define _JCEXCLAM_LAYER_HPP_

NAME_SPACE_S

template <typename T>
class Layer
{
protected:
	size_t in;
	size_t out;

public:
	Layer(size_t in, size_t out) : in(in), out(out)
	{
		printf("Layer Constructor called\n");
	}

	~Layer()
	{
		printf("Layer Destructor called\n");
	}

	virtual Blob<T> foward(const Blob<T>& x) = 0;
	virtual Blob<T> backward(const Blob<T>& dL, const Blob<T>& x) = 0;
	virtual void update(float learningRate) { learningRate += 1; };	// 업데이트가 없는 레이어도 있다.
};

NAME_SPACE_E

#endif