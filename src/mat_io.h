#ifndef _MAT_IO_H
#define _MAT_IO_H

struct _Matrix
	{
	int r,c;
	double **data;
	};
typedef struct _Matrix Matrix;

/**
 * Zwraca wskaźnik na macierz - udalo sie wczytac
 * Zwraca NULL - podczas wczytywania wystapil blad
 * Założenie: Macierz jest odpowiednio sformatowanej postaci
 */
Matrix *readFromFile(char *fname);
void printToScreen(Matrix *mat);
Matrix *createMatrix(int r, int c);
void freeMatrix(Matrix *mat);

#endif
