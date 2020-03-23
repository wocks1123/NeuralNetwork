#pragma once

#include <memory>

#include "Exclam/Common.h"
#include "Exclam/Layers/Layer.hpp"
#include "Exclam/Utils/Blob.hpp"

#ifndef _JCEXCLAM_LINEAR_LAYER_HPP_
#define _JCEXCLAM_LINEAR_LAYER_HPP_

NAME_SPACE_S

template<typename T>
class LinearLayer : public Layer<T>
{
private:
	/* TODO
	*	- ��׸� � �ڷ������� �����ؾ����� �𸣁ٴ�.
	*	- �ϴ� shared_ptr�� ���� ������
	*		- Blob<T>�� �⺻ �����ڰ� ��� �̷��� ����...
	*		- �����غ��ϱ� ������ ������Ʈ�ؾ��ϴµ� shared_ptr�̸� �� ������ �ǳ�?
	*		- delta�� �׳� ���ο �����ϰ� �ϸ� ���ٵ� �������ϸ� ����/������ ����Ұ� ����.
	*/
	/*std::shared_ptr<Blob<T>> W;
	std::shared_ptr<Blob<T>> b;
	std::shared_ptr<Blob<T>> delta;*/
	Blob<T> W;
	Blob<T> b;
	Blob<T> delta;

public:
	LinearLayer(size_t in, size_t out) : Layer<T>(in, out)
	{
		printf("LinearLayer Constructor called\n");
		/*this->W = std::make_shared<Blob<T>>(in, out);
		this->b = std::make_shared<Blob<T>>(1, out);*/
		this->W = Blob<T>(in, out);
		this->b = Blob<T>(1, out);
		this->delta = Blob<T>(in, out);
	}

	~LinearLayer()
	{
		printf("LinearLayer Destructor called\n");
	}

	virtual Blob<T> foward(const Blob<T>& x) override
	{
		//return x * *W.get();
		return x * W;
	}

	virtual Blob<T> backward(const Blob<T>& dL, const Blob<T>& x) override
	{
		//this->delta = std::make_shared<Blob<T>>(dL.getTranspose() * x);
		//return dL * W.get()->getTranspose();
		this->delta = dL.getTranspose() * x;
		return dL * W.getTranspose();
	}

	virtual void update(float learningRate) override
	{
		this->W = this->W - (this->delta * learningRate);
	}

};

NAME_SPACE_E

#endif