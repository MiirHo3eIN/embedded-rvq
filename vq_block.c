/* PMSIS includes */
#include "pmsis.h"
#include "stdio.h"
#include <stdint.h>
#include <math.h>

#include "vq_block.h"
/* Scenarios to explore 

    1. 
*/

/* Variables used. */


#define N_ROW 10 // row size
#define N_COL 2 // column size

#define N_ROW_A 10
#define N_COL_A 20

#define N_ROW_B 20
#define N_COL_B 10

void MatrixTranspose(float32_t *Src, float32_t *Dst, int rowSize, int colSize)
{
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            Dst[j * rowSize + i] = Src[i * colSize + j];
        }
    }
}


void MatrixTransposeTest() 
{
    float32_t *A;
    float32_t *B;
    A = (float32_t *) malloc(N_ROW * N_COL * sizeof(float32_t));
    B = (float32_t *) malloc(N_ROW * N_COL * sizeof(float32_t));

    MatrixInit(A, N_ROW, N_COL);
    MatrixInit(B, N_COL, N_ROW);

    MatrixPrint(A, "A", N_ROW, N_COL);
    MatrixTranspose(A, B, N_ROW, N_COL);
    MatrixPrint(B, "A Transpose", N_COL, N_ROW);
}

void VectorAddTest()
{
    /* Init the Vectors */
    float32_t *A;
    float32_t *B;
    float32_t *C;

    A = (float32_t *) malloc(N_ROW * sizeof(float32_t));
    B = (float32_t *) malloc(N_COL * sizeof(float32_t));
    C = (float32_t *) malloc(N_ROW * N_COL *sizeof(float32_t));

    VectorInit(A, N_ROW, 10, ON);
    VectorInit(B, N_COL, 5, ON);
    VectorInit(C, N_ROW*N_COL, 0, OFF);
    VectorToMatrixAdd(A, B, C, N_ROW, N_COL);

    VectorPrint(A, "A", N_ROW);
    VectorPrint(B, "B", N_COL);
    VectorPrint(C, "C", N_ROW*N_COL);

}
void MatrixAdd(float32_t *SrcA, float32_t *SrcB, float32_t *Dst, int rowSize, int colSize)
{
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            Dst[i * colSize + j] = SrcA[i * colSize + j] + SrcB[i * colSize + j];
        }
    }
}


void cdist(float32_t *SrcA, float32_t *SrcB, float32_t *Dst, int rowSizeSrc, int colSizeSrc)
{
    
    float32_t *xTemp;
    float32_t *yTemp;
    float32_t *SrcBTransposed;
    float32_t *sumResult; 

    sumResult = (float32_t *) malloc(rowSizeSrc * rowSizeSrc * sizeof(float32_t));
    SrcBTransposed = (float32_t *) malloc(rowSizeSrc * colSizeSrc * sizeof(float32_t));
    xTemp = (float32_t *) malloc(rowSizeSrc * sizeof(float32_t));  
    yTemp = (float32_t *) malloc(rowSizeSrc * sizeof(float32_t)); // colSizeSrcA must be same as the rowSizeSrcB

    /* Initialize xtemp and ytemp */
    VectorInit(xTemp, rowSizeSrc, 0, OFF);
    VectorInit(yTemp, rowSizeSrc, 0, OFF);

    /* Print The two Input Matrices */
    MatrixPrint(SrcA, "SrcA", rowSizeSrc, colSizeSrc);
    MatrixPrint(SrcB, "SrcB", rowSizeSrc, colSizeSrc);

    /* Embed Transpose */
    
    MatrixTranspose(SrcB, SrcBTransposed, rowSizeSrc, colSizeSrc); /* y = transpose(B) */
    MatrixPrint(SrcBTransposed, "SrcBTransposed", colSizeSrc, rowSizeSrc);
    /* Matrix Multiplications */
    matMul(SrcA, SrcBTransposed, Dst, rowSizeSrc, colSizeSrc, rowSizeSrc); /* -2xy */
    MatrixPrint(Dst, "MatMul Result", rowSizeSrc, rowSizeSrc);
    /* Sum the elements of each row */
    MatToVectorSum(SrcA, xTemp, rowSizeSrc, colSizeSrc); /* reduce(x, 'i d -> i', sum) */
    MatToVectorSum(SrcB, yTemp, rowSizeSrc, colSizeSrc); /* reduce(y, 'i d -> i', sum) */

    VectorPrint(xTemp, "xTemp", rowSizeSrc);
    VectorPrint(yTemp, "yTemp", rowSizeSrc);
    /* Add x and y*/
    VectorToMatrixAdd(xTemp, yTemp, sumResult, rowSizeSrc, rowSizeSrc); /* x + y */
    MatrixPrint(sumResult, "SumResult", rowSizeSrc, rowSizeSrc);    
    /* Add the result of matrix multiplication and sum of x and y */
    MatrixAdd(Dst, sumResult, Dst, rowSizeSrc, rowSizeSrc); /* -2xy + x + y */
    MatrixPrint(Dst, "Result", rowSizeSrc, rowSizeSrc); /* -2xy + x + y */

}





void MatrixAddTest()
{
    float32_t *A;
    float32_t *B;
    float32_t *C; 
    A = (float32_t *) malloc(N_COL*N_ROW * sizeof(float32_t));
    B = (float32_t *) malloc(N_COL*N_ROW * sizeof(float32_t));
    C = (float32_t *) malloc(N_ROW * N_ROW * sizeof(float32_t));

    
    // Initialize the matrices
    MatrixInit(A, N_ROW, N_COL);
    MatrixInit(B, N_ROW, N_COL);
    MatrixInit(C, N_ROW, N_ROW);

    // Print the matrices
    MatrixPrint(A, "A", N_ROW, N_COL);
    MatrixPrint(B, "B", N_ROW, N_COL);

    // Add the matrices
    MatrixAdd(A, B, C, N_ROW, N_COL);

    // Print the result
    MatrixPrint(C, "C", N_ROW, N_COL);
}


void cdist_test()
{
    float32_t *A;
    float32_t *B;
    float32_t *C; 
    A = (float32_t *) malloc(N_COL*N_ROW * sizeof(float32_t));
    B = (float32_t *) malloc(N_COL*N_ROW * sizeof(float32_t));
    C = (float32_t *) malloc(N_ROW * N_ROW * sizeof(float32_t));

    
    // Initialize the matrices
    MatrixInit(A, N_ROW, N_COL );
    MatrixInit(B, N_ROW, N_COL );
    MatrixInit(C, N_ROW, N_ROW );

    // Print the matrices
    cdist(A, B, C, N_ROW, N_COL);
}


/* Program Entry. */
int main(void)
{
    printf("\n\n\t *** PMSIS HelloWorld ***\n\n");
    printf("Entering main controller\n");

    uint32_t errors = 0;
    
    // MatrixTransposeTest();
    // VectorAddTest();
    // MatrixAddTest();
    cdist_test();
    printf("Bye !\n");

    return errors;
}
