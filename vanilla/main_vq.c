/* PMSIS includes */
#include "pmsis.h"
#include "stdio.h"
#include <stdint.h>
#include <math.h>

#include "vq_block.h"
#include "inputs.h"
#include "codebook.h"


/* User Defines */
#define  N_ROW 1
#define  N_COL 100



/* Program Entry. */
int main(void)
{
    printf("\n\n\t *** PMSIS HelloWorld ***\n\n");
    printf("Entering main controller\n");

    uint32_t errors = 0;
    float32_t *input_data;
    input_data = (float32_t *) malloc(N_ROW * N_COL * sizeof(float32_t));
    
    printf("Main script of the vanilla application\n");
    /* Let's read the first two inputs */
    for (int i = 0; i < 2; i++) /* To read different input values */
    {
        printf("Analysing Input Sample %d\n", i);
        
        for (int j = 0; j < N_ROW * N_COL; j++)
        {
            input_data[j] = input[i][j];
        }

        MatrixPrint((float32_t *)input_data, "Sample", N_ROW, N_COL);
    }

    printf("Bye !\n");

    return errors;
}
