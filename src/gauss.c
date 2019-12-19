/*
 * gauss.c
 *
 *  Created on: 15 gru 2019
 *      Author: liath
 */

/*	@mat.io.h
 struct _Matrix
	{
	int r,c;
	double **data;
	};
typedef struct _Matrix Matrix;
*/

#include "gauss.h"
#include "mat_io.h"
#include <stdbool.h>
//#include <stdio.h>

//returns true if |subject| > |actmax|
bool modGreater(double subject, double actmax)
	{
	if(subject * subject > actmax * actmax)
		{
		return true;
		}
	return false;
	}

//finds max elem from column
int findDiagEl(Matrix *mat, int i)
	{
	int outcome = i;
	double actmax = *(*((mat -> data) + i) + i);
	for(int j = i + 1; j < mat -> r; j++)
		{
		if(modGreater(*(*((mat -> data) + i) + j), actmax))
			{
			outcome = j;
			actmax = *(*((mat -> data) + i) + j);
			}
		}
	return outcome;
	}

void changeRows(Matrix *mat, Matrix *b, int row1, int row2)
	{
	double pivit;
	//all elements before column(nr.row1) are 0
	for(int i = row1; i < mat -> c; i++)
		{
		pivit = *(*((mat -> data) + i) + row1);
		*(*((mat -> data) + i) + row1) = *(*((mat -> data) + i) + row2);
		*(*((mat -> data) + i) + row2) = pivit;
		}
	pivit = *(*((b -> data) + 0) + row1);
	*(*((b -> data) + 0) + row1) = *(*((b -> data) + 0) + row2);
	*(*((b -> data) + 0) + row2) = pivit;
	}

//divides all elements in a row so that the element on position (row, row) would be one
void makeOneForDial(Matrix *mat, Matrix *b, int row)
	{
	double div = *(*((mat -> data) + row) + row);
	//if(div == 1) return;
	for(int i = row; i < mat -> c; i++)
		{
		*(*((mat -> data) + i) + row) = *(*((mat -> data) + i) + row)/div;
		}
	*(*((b -> data) + 0) + row) = *(*((b -> data) + 0) + row)/div;
	}

//subtracts rows so that the number on position (row1, row2) would be 0
void subtractRows(Matrix *mat, Matrix *b, int row1, int row2)
	{
	double mul = *(*((mat -> data) + row1) + row2);
	for(int i = row1; i < mat -> c; i++)
		{
		*(*((mat -> data) + i) + row2) = *(*((mat -> data) + i) + row2) - mul * (*(*((mat -> data) + i) + row1));
		}
	*(*((b -> data) + 0) + row2) = *(*((b -> data) + 0) + row2) - mul * (*(*((b -> data) + 0) + row1));
	}

void doElimination(Matrix *mat, Matrix *b, int row)
	{
	makeOneForDial(mat, b, row);
	for(int i = row + 1; i < mat -> r; i++)
		{
		subtractRows(mat, b, row, i);
		}
	}

//checks if zeroed rows are behaving properly
bool NoInconsistencies(Matrix *mat, Matrix *b)
	{
	int i = (mat -> r) - 1;
	//if last element of a row is equal to zero then the whole row should be zeroed
	while(i >= 0 && *(*((mat -> data) + (mat -> c - 1)) + i) == 0)
		{
		if(*(*((b -> data) + 0) + i) != 0)
			{
			//the row is zeroed but corresponding value from b != 0
			//that's an inconsistency ;-;
			return false;
			}
		--i;
		}
	return true;
	}

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - układ równań jest sprzeczny
 * Zwraca 2 - Układ równań jest nieoznaczony
 */
int eliminate(Matrix *mat, Matrix *b)
	{
	bool AllOK = true;
	for(int i = 0; i < mat -> c; i++)
		{
		int idDiagEl = findDiagEl(mat, i);
		if(*(*((mat -> data) + i) + idDiagEl) != 0)//if idDiagEl == 0 we will return 1 or 2
			{
			if(idDiagEl != i)//else no need to change rows
				{
				changeRows(mat, b, i, idDiagEl);
				}
			/*printf("Macierz A:\n");
			printToScreen(mat);
			printf("Macierz B:\n");
			printToScreen(b);*/
			doElimination(mat, b, i);
			}
		else
			{
			AllOK = false;
			}
		/*printf("Macierz A:\n");
		printToScreen(mat);
		printf("Macierz B:\n");
		printToScreen(b);*/
		}
	if(AllOK)//no 0 on diagonal
		{
		if(NoInconsistencies(mat, b))
			{
			//no inconsistencies but there are too few equations
			if(mat -> r < mat -> c)
				{
				return 2;
				}
			return 0;
			}
		}
	else//0 on diagonal
		{
		if(NoInconsistencies(mat, b))
			{
			return 2;
			}
		}
	return 1;//The zeroed rows were inconsistent (their b's were not equal to 0)
	//therefore set of equations is inconsistent
	}
