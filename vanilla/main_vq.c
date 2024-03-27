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
#define CODEBOKE_DIM 128



/* Program Entry. */
int main(void)
{
    printf("\n\n\t *** PMSIS HelloWorld ***\n\n");
    printf("Entering main controller\n");

    uint32_t errors = 0;
    float32_t *input_data;
    float32_t *code_word;
    float32_t cdist_current = 0.0f, cdist_next = 0.0f;
    
    input_data = (float32_t *) malloc(N_ROW * N_COL * sizeof(float32_t));
    code_word = (float32_t *) malloc(N_ROW * N_COL * sizeof(float32_t));
    printf("Main script of the vanilla application\n");
    /* Let's read the first two inputs */
    for (int i = 0; i < 2; i++) /*  Iterate over 100 input samples */
    {   
                    
        cdist_current = 2000; // Reset the cdist value for the given input sample
        printf("Analysing Input Sample %d\n", i);
        for (int k =0 ; k < CODEBOKE_DIM; k++) 
        {        
            for (int j = 0; j < N_ROW * N_COL; j++)  // This is the second dimension of the input and codebook matrix  
            { 
            
                input_data[j] = input[i][j]; // An unseen input array in the latent space 
                // code_word[j] = codebook[k][j]; // A codeword from the codebook matrix

            }

                            
            cdist_next = cdist(input_data, &codebook[k][0], N_ROW, N_COL);
            printf("cdist: %f\t for codeword %d\n ", cdist_next, k);

            if (cdist_next < cdist_current)
            {
                cdist_current = cdist_next;
                printf("The lowest cdist: %f\t for codeword %d \n", cdist_current, k);
            }

        }/* Iterate over 100 input samples */

        MatrixPrint((float32_t *)input_data, "Sample", N_ROW, N_COL);
    }

    printf("Bye !\n");

    return errors;
}
