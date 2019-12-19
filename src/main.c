/*
 ============================================================================
 Name        : GaussMethod.c
 Author      : liath
 Version     :
 Copyright   : NULL
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "mat_io.h"
#include "backsubst.h"
#include "gauss.h"

void presentYourself(Matrix *A, Matrix *B)
	{
	printf("Macierz A:\n");
	printToScreen(A);
	printf("Macierz B:\n");
	printToScreen(B);
	}

int main(int argc, char *argv[])
	{
	Matrix *A = readFromFile(argc > 1 ? argv[1] : "A.txt");
	Matrix *B = readFromFile(argc > 2 ? argv[2] : "B.txt");
	if(A == NULL || B == NULL)
		{
		return EXIT_FAILURE;
		}
	presentYourself(A, B);
	int outcome = eliminate(A, B);
	presentYourself(A, B);
	if(outcome == 1 || outcome == 2)
		{
		if(outcome == 1)
			{
			printf("Set of equations is inconsistent\n");
			}
		else//outcome == 2
			{
			printf("Set of equations is indeterminate\n");
			}
		freeMatrix(A);
		freeMatrix(B);
		return EXIT_FAILURE;
		}
	//outcome == 0
	Matrix *X = createMatrix(A -> c, 1);
	if(X == NULL)
		{
		printf("Memory allocation error in creation of outcome vector (X)\n");
		freeMatrix(A);
		freeMatrix(B);
		return EXIT_FAILURE;
		}
	backsubst(X, A, B);
	printf("Outcome vector:\n");
	printToScreen(X);
	freeMatrix(A);
	freeMatrix(B);
	freeMatrix(X);
	return EXIT_SUCCESS;
	}
