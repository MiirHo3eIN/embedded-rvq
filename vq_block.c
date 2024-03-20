/* PMSIS includes */
#include "pmsis.h"
#include "stdio.h"
#include <stdint.h>
#include <math.h>
/* Scenarios to explore 

    1. 
*/

/* Variables used. */
typedef float float32_t;

#define N_ROW 10 // row size
#define N_COL 20 // column size



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

void vector_sum(float32_t *src, float dst[N_ROW],int rowSize, int colSize)
{

    /* Sum the elements of each row */
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
           
            dst[i] += (src[i*colSize + j]*src[i*colSize + j] );
        }

        printf("Sum of %d row is %f\n", i, dst[i]);
    }
}


void MatrixInit(float32_t *pSrc, int rowSize, int colSize)
{
    int i;
    int j;
    for (i = 0; i < rowSize; i++)
    {
        for (j = 0; j < colSize; j++)
        {
            pSrc[i * colSize + j] = (i*colSize) +1 + j; // A[i][j] = i*colSize + j + 1
        }
    }
}
void matrix_print(float *A, char *matrix_name, int rowSize, int colSize)
{   
    printf("%s=", matrix_name); 
    for (int i = 0; i < rowSize; i++) 
    {   printf("[");
        for (int j = 0; j < colSize; j++) 
        {
            printf("%f, ", A[i*colSize + j]);
            // printf("]");
        }
        printf("];\n");

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
            pDst[i + j] = pSrcA[i] + pSrcB[j];
        }
    }
}


void VectorInit(float32_t *pSrc, int rowSize, float value)
{
    int i;
    for (i = 0; i < rowSize; i++)
    {
        pSrc[i] = i *value;
    }
}

void VectorPrint(float32_t *pSrc, char *name , int rowSize)
{
    int i;
    printf("Vector %s = \n", name);
    for (i = 0; i < rowSize; i++)
    {   
        printf("%f\n", pSrc[i]);
    }
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

    VectorInit(A, N_ROW, 10);
    VectorInit(B, N_COL, 5);

    VectorToMatrixAdd(A, B, C, N_ROW, N_COL);

    VectorPrint(C, "C", N_ROW*N_COL);

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
