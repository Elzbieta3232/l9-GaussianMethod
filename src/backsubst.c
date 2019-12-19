/*
 * backbust.c
 *
 *  Created on: 16 gru 2019
 *      Author: liath
 */

#include "backsubst.h"
#include "mat_io.h"

int backsubst(Matrix *x, Matrix *mat, Matrix *b)
	{
	int i = (mat -> r) - 1;
	//skip zeroed rows
	while(i >= 0 && *(*((mat -> data) + (mat -> c - 1)) + i) == 0)
		{
		--i;
		}
	double outcome;
	while(i >= 0)
		{
		outcome = *(*((b -> data) + 0) + i);
		for(int j = i + 1; j < mat -> c; ++j)
			{
			outcome = outcome - *(*((x -> data) + 0) + j) * (*(*((mat -> data) + j) + i));
			}
		*(*((x -> data) + 0) + i) = outcome;
		--i;
		}
	//rewritten gauss.c so that backsubst.c always gets proper set of equations
	return 0;
	}
