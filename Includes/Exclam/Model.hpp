#pragma once

#include <vector>

#include "Common.h"
#include "Layer.h"

#ifndef _JCEXCLAM_MODEL_HPP_
#define _JCEXCLAM_MODEL_HPP_

NAME_SPACE_S

template<typename T>
class Model
{
private:
	std::vector<Layer<T>> layers;
	std::vector<Blob<T>> Xs;
public:
	Model(std::initializer_list<Layer<T>> l) : layers(l)
	{

	}
	~Model()
	{

	}

	void forward(Blob<T> X)
	{
		Xs.push_back(X);
		for (const auto& layer : this->layers)
		{
			Xs.push_back(layer.forward(Xs.back()));
		}
	}

	void backward()
	{
		for (int i = layers.size() - 1; i >= 0; --i)
		{

		}
	}

};

NAME_SPACE_E

#endif //_JCEXCLAM_MODEL_HPP_
