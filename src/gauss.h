#ifndef _GAUSS_H
#define _GAUSS_H

#include "mat_io.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - układ równań jest sprzeczny
 * Zwraca 2 - Układ równań jest nieoznaczony
 */
int eliminate(Matrix *mat, Matrix *b);

#endif
