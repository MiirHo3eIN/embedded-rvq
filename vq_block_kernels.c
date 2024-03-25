#include "pmsis.h"
#include "stdio.h"
#include <stdint.h>
#include <math.h>

#include "vq_block.h"



/* Constant Variables */


/* Functions */


/* Matrix Multiplication with pointers*/
// C = A*B where A is MxK, B is KxN, C is MxN
void matMul(float32_t *A, float32_t *B, float32_t *C, int rowSizeA, int colSizeA, int colSizeB)
{
    /*
        M is rowSize of A
        K is colSize of A and rowSize of B
        N is colSize of B
    */
    int i = 0; // index of row in A
    int j = 0; // index of col in B
    int k = 0; // index of col in A

    float32_t sum;
    for (i = 0; i < rowSizeA; i++) // row of A
    {   
        for (j = 0; j < colSizeB; j++) // col of B
        {
            sum = 0;
            for (k = 0; k < colSizeA; k++) // col of A
            {
                sum += A[i * colSizeA + k] * B[k * colSizeB + j];
            }
            C[i * colSizeB + j] = sum * -2;
        }
    }
}


/* 
    @brief: Perform Summation in the column dimension of the Input Matric
    @author: @MiirHo3eIN
    @param: float32_t *Src: Pointer to the Input Matrix
    @param: float32_t *Dst: Pointer to the Output Vector
    @param: int rowSize: Number of rows in the Input Matrix
    @param: int colSize: Number of columns in the Input Matrix

*/
void MatToVectorSum(float32_t *Src, float32_t *Dst,int rowSize, int colSize)
{

    /* Sum the elements of each row */
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
           
            Dst[i] += (Src[i*colSize + j]*Src[i*colSize + j] );
        }

        printf("Sum of %d row is %f\n", i, Dst[i]);
    }
}


void VectorToMatrixAdd(float32_t *pSrcA, float32_t* pSrcB, float32_t *pDst, int rowSizeSrcA, int rowSizeSrcB)
{
    int i;
    int j;
    
    for (i = 0; i < rowSizeSrcA; i++)
    {
        for (j = 0; j < rowSizeSrcB; j++)
        {
            pDst[i*rowSizeSrcB + j] = pSrcA[i] + pSrcB[j];
        }
    }
}