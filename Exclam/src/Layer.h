#pragma once

#include <cstdio>
#include <cstdlib>

#include "common.h"
#include "Blob.h"

#ifndef _JCEXCLAM_LAYER_H_
#define _JCEXCLAM_LAYER_H_

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
	virtual void update(float learningRate) {};	// 업데이트가 없는 레이어도 있다.
};

NAME_SPACE_E

#endif