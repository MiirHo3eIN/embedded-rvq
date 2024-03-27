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
    float32_t cdist_current = 0.0f, cdist_next = 0.0f;
    int32_t k_current = 0;
    input_data = (float32_t *) malloc(N_ROW * N_COL * sizeof(float32_t));
    
    printf("Main script of the vanilla application\n");
    /* Let's read the first two inputs */
    for (int i = 0; i < 1; i++) /*  Iterate over 100 input samples */
    {   
        // Reset the cdist value for the given input sample to a high value since we want to find the minimum.
        cdist_current = 100000000; 
  
        for (int k =0 ; k < CODEBOKE_DIM; k++) 
        {        
            for (int j = 0; j < N_ROW * N_COL; j++)  // This is the second dimension of the input and codebook matrix  
            { 
            
                input_data[j] = input[i][j]; // An unseen input array in the latent space 
   
            }
            pi_perf_conf(1 << PI_PERF_CYCLES | 1 << PI_PERF_ACTIVE_CYCLES);   
            pi_perf_reset(); 
            pi_perf_start();      
            cdist_next = cdist(input_data, &codebook[k][0], N_ROW, N_COL, OFF);
            // printf("cdist: %f\t for codeword %d\n ", cdist_next, k);
            pi_perf_stop();
            uint32_t cycles = pi_perf_read(PI_PERF_ACTIVE_CYCLES);
            uint32_t tim_cycles = pi_perf_read(PI_PERF_CYCLES);
            printf("Performance of the dist func : %d cycles Timer : %d cycles\n", cycles, tim_cycles);
            
    
            if (cdist_next < cdist_current)
            {
                cdist_current = cdist_next;
                k_current = k;
            }

            

        }/* Iterate over 100 input samples */

        printf("Sample %d:\t The lowest cdist= %f\t for codeword %d\n", i, cdist_current, k_current);
        
    }

    printf("Bye !\n");

    return errors;
}
