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
#define N_COL 20 // column size

#define N_ROW_A 10
#define N_COL_A 20

#define N_ROW_B 20
#define N_COL_B 15



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


void cdist(float32_t *SrcA, float32_t *SrcB, float32_t *Dst, int rowSizeSrcA, int colSizeSrcA, int colSizeSrcB)
{
    
    float32_t *xTemp;
    float32_t *yTemp;
    float32_t *sumResult; 

    sumResult = (float32_t *) malloc(rowSizeSrcA * colSizeSrcB * sizeof(float32_t));
    xTemp = (float32_t *) malloc(rowSizeSrcA * sizeof(float32_t));  
    yTemp = (float32_t *) malloc(colSizeSrcA * sizeof(float32_t)); // colSizeSrcA must be same as the rowSizeSrcB

    /* Matrix Multiplications */
    matMul(SrcA, SrcB, Dst, rowSizeSrcA, colSizeSrcA, colSizeSrcB);
    MatrixPrint(Dst, "Result", rowSizeSrcA, colSizeSrcB);
    /* Sum the elements of each row */
    MatToVectorSum(SrcA, xTemp, rowSizeSrcA, colSizeSrcB);
    MatToVectorSum(SrcB, yTemp, colSizeSrcA, colSizeSrcB);

    VectorPrint(xTemp, "xTemp", rowSizeSrcA);
    VectorPrint(yTemp, "yTemp", colSizeSrcA);
    /* Add x and y*/
    VectorToMatrixAdd(xTemp, yTemp, sumResult, rowSizeSrcA, colSizeSrcA);

    /* Add the result of matrix multiplication and sum of x and y */

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
    MatrixInit(A, N_ROW, N_COL);
    MatrixInit(B, N_COL, N_ROW);
    MatrixInit(C, N_ROW, N_ROW);

    // Print the matrices
    cdist(A, B, C, N_ROW, N_COL, N_ROW);
}


/* Program Entry. */
int main(void)
{
    printf("\n\n\t *** PMSIS HelloWorld ***\n\n");
    printf("Entering main controller\n");

    uint32_t errors = 0;
    

    VectorAddTest();
    // float32_t *A;
    // float32_t *B;
    // float32_t *C; 
    // A = (float32_t *) malloc(N_COL*N_ROW * sizeof(float32_t));
    // B = (float32_t *) malloc(N_COL*N_ROW * sizeof(float32_t));
    // C = (float32_t *) malloc(N_ROW * N_ROW * sizeof(float32_t));

    
    // // Initialize the matrices
    // // MatrixInit(A, N_ROW, N_COL);
    // // MatrixInit(B, N_COL, N_ROW);
    // // MatrixInit(C, N_ROW, N_ROW);

    // // Print the matrices


    // printf("Result of matrix A:\n");
    // matrix_print( A, "A", N_ROW, N_COL);
    // matrix_print( B, "B", N_COL, N_ROW);

    // matMul(A, B, C, N_ROW, N_COL, N_ROW);

    // matrix_print(C, "Result", N_ROW, N_ROW);
    // // vector_sum(A, C, N_ROW, N_COL);
    
    // // Perform matrix multiplication
    // matrixMultiply((int*)A, (int*)B, (int*)C, m, n, p);
    
    // Print the resultant matrix C
    

    // printf("Result of Vector C:\n");
    // for (int i = 0; i < N_ROW; i++)
    // {
    //     printf("%f \n", C[i]);
    // }
    // // printf("Resultant matrix B:\n");
    // // matrix_print(B, n, p);
    printf("Bye !\n");

    return errors;
}
