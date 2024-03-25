#include <stdint.h>
#include <math.h>
#include "pmsis.h"
#include "stdio.h"


typedef float float32_t;
typedef enum {ON, OFF} bool;


/* Vq Kernels Functions */

void matMul(float32_t *A, float32_t *B, float32_t *C, int rowSizeA, int colSizeA, int colSizeB);
void MatToVectorSum(float32_t *Src, float32_t *Dst,int rowSize, int colSize);
void VectorToMatrixAdd(float32_t *A, float32_t *B, float32_t *C, int rowSize, int colSize);

/* Utils Functions */
void MatrixInit(float32_t *pSrc, int rowSize, int colSize);
void MatrixPrint(float *A, char *matrix_name, int rowSize, int colSize);
void VectorInit(float32_t *pSrc, int rowSize, float32_t value, bool is_incremental);
void VectorPrint(float32_t *pSrc, char *vector_name, int rowSize);