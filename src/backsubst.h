#ifndef _BACKSUBST_H
#define _BACKSUBST_H

#include "mat_io.h"

//rewritten gauss.c so that backsubst.c always gets proper set of equations
int backsubst(Matrix *x, Matrix *mat, Matrix *b);

#endif
