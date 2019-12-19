/*
 * mat_io.c
 *
 *  Created on: 16 gru 2019
 *      Author: liath
 */

/*@mat_io.h
struct _Matrix
	{
	int r,c;
	double **data;
	};
typedef struct _Matrix Matrix;
 */

#include "mat_io.h"
#include <stdio.h>
#include <stdlib.h>

void freeData(double **data, int rows, int columns)
	{
	for(int i = 0; i < columns; i++)
		{
		free(*(data + i));
		}
	free(data);
	}

void freeMatrix(Matrix *mat)
	{
	freeData(mat -> data, mat -> r, mat -> c);
	free(mat);
	}

Matrix *createMatrix(int r, int c)
	{
	Matrix *mat = malloc(sizeof(*mat));
	if(mat == NULL)
		{
		return NULL;
		}
	double **data;
	data = malloc(c * sizeof(*data));
	if(data == NULL)
		{
		free(mat);
		return NULL;
		}
	for(int i = 0; i < c; i++)
		{
		*(data + i) = malloc(sizeof(**data) * r);
		if(*(data + i) == NULL)
			{
			//not all data needs to be freed
			freeData(data, r, i);
			free(mat);
			return NULL;
			}
		}
	mat -> r = r;
	mat -> c = c;
	mat -> data = data;
	return mat;
	}

Matrix *readFromFile(char *fname)
	{
	FILE *f = fopen(fname, "r");
	if(f == NULL)
		{
		printf("Couldn't open %s file\n", fname);
		return NULL;
		}
	int r, c;
	fscanf(f, "%d %d", &r, &c);
	Matrix *mat = createMatrix(r, c);
	if(mat == NULL)
		{
		printf("Memory allocation error in matrix creation from %s file\n", fname);
		return NULL;
		}
	for(int i = 0; i < r; i++)
		{
		for(int j = 0; j < c; j++)
			{
			double pivitforcnoobs;
			fscanf(f, "%lf", &pivitforcnoobs);
			*(*((mat -> data) + j) + i) = pivitforcnoobs;
			}
		}
	fclose(f);
	return mat;
	}

void printToScreen(Matrix *mat)
	{
	for(int i = 0; i < mat -> r; i++)
		{
		for(int j = 0; j < mat -> c; j++)
			{
			printf("%10f ", *(*((mat -> data) + j) + i));
			}
		printf("\n");
		}
	}
