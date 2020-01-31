#pragma once

#include <cstdio>
#include <cstdlib>
#include <memory>
#include <string>

#include "common.h"
#include "util.h"

#ifndef _JCEXCLAM_BLOB_H_
#define _JCEXCLAM_BLOB_H_

NAME_SPACE_S

template <typename T>
class Blob
{
public:
	size_t n = 0;
	unsigned dim = 0;
	size_t w = 0;
	size_t h = 0;
	size_t c = 0;
	size_t lenth = 0;
	T* data = NULL;
public:
	Blob(size_t _n, size_t _w) : n(_n), w(_w), dim(2), lenth(_n* _w)
	{
		this->data = (T*)calloc(_n * _w, sizeof(T));
		if (this->data == NULL)
		{
			fprintf(stderr, "can't alloc memery...\n");
			fprintf(stderr, "%s at %s::%05d\n", __func__, __FILE__, __LINE__);
			abort();
		}
	}

	Blob(size_t _n, size_t _w, size_t _h) : n(_n), w(_w), h(_h), dim(3), lenth(_n* _w* _h)
	{
		this->data = (T*)calloc(_n * _w * _h, sizeof(T));
		if (this->data == NULL)
		{
			fprintf(stderr, "can't alloc memery...\n");
			fprintf(stderr, "%s at %s::%05d\n", __func__, __FILE__, __LINE__);
			abort();
		}
	}

	Blob(size_t _n, size_t _w, size_t _h, size_t _c) : n(_n), w(_w), h(_h), c(_c), dim(4), lenth(_n* _w* _h* _c)
	{
		this->data = (T*)calloc(this->lenth, sizeof(T));
		if (this->data == NULL)
		{
			fprintf(stderr, "can't alloc memery...\n");
			fprintf(stderr, "%s at %s::%05d\n", __func__, __FILE__, __LINE__);
			abort();
		}
	}

	Blob(const Blob<T>& obj) : n(obj.n), w(obj.w), h(obj.h), c(obj.c), dim(obj.dim), lenth(obj.lenth)
	{
		this->data = (T*)calloc(this->lenth, sizeof(T));
		memcpy(this->data, obj.data, this->lenth * sizeof(T));
		if (this->data == NULL)
		{
			fprintf(stderr, "can't alloc memery...\n");
			fprintf(stderr, "%s at %s::%05d\n", __func__, __FILE__, __LINE__);
			abort();
		}
	}


	~Blob()
	{
		free(this->data);
	}

	void copy(T* _data, size_t sz)
	{
		T* ret = memcpy(this->data, _data, sz);
		if (ret == NULL)
		{
			fprintf(stderr, "memery copy error...\n");
			fprintf(stderr, "%s at %s::%05d\n", __func__, __FILE__, __LINE__);
			abort();
		}
	}


	T* getDataMutable() const
	{
		return this->data;
	}


	const T* getDataImmutable() const
	{
		return this->data;
	}


	/* TODO
	*	- CPU/GPU ��� �и�
	*	- ������ �ϴ� CPU��...
	*	- CNN���� ���� 3D ��굵 �ʿ��Ѱ�?
	*/
	void transpose()
	{
		T* temp = (T*)calloc(this->lenth, sizeof(T));
		MatTranpose(this->data, this->n, this->w, temp);
		free(this->data);
		size_t t = this->n;
		this->n = this->w;
		this->w = t;

		this->data = temp;
	}

	void Print()
	{
		if (this->dim == 2)
		{
			for (int i = 0; i < this->n; ++i)
			{
				for (int j = 0; j < this->w; ++j)
				{
					printf("%f ", ARR_I_J(this->data, i, this->w, j));
				}
				printf("\n");
			}
		}
		else
		{
			fprintf(stderr, "Print Error\n");
			fprintf(stderr, "%s at %s::%05d\n", __func__, __FILE__, __LINE__);
			abort();
		}

	}



	/* TODO
	*	- CPU/GPU ��� �и�
	*	- ������ �ϴ� CPU��...
	*	- CNN���� ���� 3D ��굵 �ʿ��Ѱ�?
	*/
	Blob<T> operator*(const Blob<T>& x)
	{
		if (this->dim != x.dim || this->w != x.n)
		{
			fprintf(stderr, "The dimension is not matched...\n");
			fprintf(stderr, "%s at %s::%05d\n", __func__, __FILE__, __LINE__);
			abort();
		}

		Blob<T> res(this->n, x.w);
		MatMul(this->data, this->n, this->w, x.data, x.n, x.w, res.data);
		return res;
	}

	Blob<T>& operator=(const Blob<T>& obj)
	{
		if (this->lenth != obj.lenth)
		{
			fprintf(stderr, "The data size is not matched...\n");
			fprintf(stderr, "%s at %s::%05d\n", __func__, __FILE__, __LINE__);
			abort();
		}
		memcpy(this->data, obj.data, this->lenth * sizeof(T));

		return *this;
	}

};

NAME_SPACE_E

#endif