#pragma once

#include "common.h"
#include <cstdio>

#define ARR_I_J(arr, i, row_len, j) arr[i * row_len + j]

NAME_SPACE_S

void MatAdd(const float* A, const size_t a_h, const size_t a_w, const float* B, const size_t b_h, const size_t b_w, float* C)
{
	if (a_h == b_h && a_w == b_w)
	{
		fprintf(stderr, "The matrixes size is not matched...\n");
		fprintf(stderr, "%s at %s::%05d\n", __func__, __FILE__, __LINE__);
		abort();
	}

	for (int i = 0; i < a_h; i++)
	{
		for (int j = 0; j < b_w; j++)
		{
			ARR_I_J(C, i, b_w, j) = ARR_I_J(A, i, a_h, j) + ARR_I_J(B, i, b_h, j);
		}
	}
}

void MatSub(const float* A, const size_t a_h, const size_t a_w, const float* B, const size_t b_h, const size_t b_w, float* C)
{
	if (a_h == b_h && a_w == b_w)
	{
		fprintf(stderr, "The matrixes size is not matched...\n");
		fprintf(stderr, "%s at %s::%05d\n", __func__, __FILE__, __LINE__);
		abort();
	}

	for (int i = 0; i < a_h; i++)
	{
		for (int j = 0; j < b_w; j++)
		{
			ARR_I_J(C, i, b_w, j) = ARR_I_J(A, i, a_h, j) - ARR_I_J(B, i, b_h, j);
		}
	}
}

void MatMul(const float* A, const size_t a_h, const size_t a_w, const float* B, const size_t b_h, const size_t b_w, float* C)
{
	for (int i = 0; i < a_h; i++)
	{
		for (int j = 0; j < b_w; j++)
		{
			float sum = 0;
			for (int k = 0; k < b_h; k++)
			{
				sum += ARR_I_J(A, i, a_w, k) * ARR_I_J(B, k, b_w, j);
			}
			ARR_I_J(C, i, b_w, j) = sum;
		}
	}
}

void MatMulValue(const float* A, const size_t a_h, const size_t a_w, float* C, float val)
{
	for (int i = 0; i < a_h; i++)
	{
		for (int j = 0; j < a_w; j++)
		{
			ARR_I_J(C, i, a_w, j) = ARR_I_J(A, i, a_w, j) * val;
		}
	}
}


void MatTranpose(const float* A, const size_t a_h, const size_t a_w, float* C)
{
	for (int i = 0; i < a_h; i++)
	{
		for (int j = 0; j < a_w; j++)
		{
			ARR_I_J(C, j, a_h, i) = ARR_I_J(A, i, a_w, j);
		}
	}
}

NAME_SPACE_E