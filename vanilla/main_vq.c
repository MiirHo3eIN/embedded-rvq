/* PMSIS includes */
#include "pmsis.h"
#include "stdio.h"
#include <stdint.h>
#include <math.h>

#include "vq_block.h"
#include "input_v1.h"
#include "trained_codebook.h"


/* User Defines */
#define  N_ROW 1
#define  N_COL 100
#define  N_CHANNELS 9
#define CODEBOKE_DIM 250

// #define PROFILE 0


// TODO: Make a function called VQ_block in the following way: 
// vq_block(float)


/* Program Entry. */
int main(void)
{
    printf("\n\n\t *** PMSIS HelloWorld ***\n\n");
    printf("Entering main controller\n");

    uint32_t errors = 0;
    float32_t *input_data;
    
    float32_t cdist_current = 0.0f, cdist_next = 0.0f;
    float32_t *cdist_final, *codeword_id; 

    float32_t *quantized_val; 

    int32_t k_current = 0;
    
    input_data = (float32_t *) malloc(N_ROW * N_COL * sizeof(float32_t));
    cdist_final = (float32_t *) malloc(N_CHANNELS * sizeof(float32_t));
    codeword_id = (float32_t *) malloc(N_CHANNELS * sizeof(float32_t));
    quantized_val = (float32_t *) malloc(N_COL * N_CHANNELS* sizeof(float32_t));

    VectorInit(cdist_final, N_CHANNELS, 0, OFF); 
    VectorInit(codeword_id, N_CHANNELS, 0, OFF); 

    printf("Main script of the vanilla application\n");
    /* Let's read the first two inputs */
    for (int i = 0; i < N_CHANNELS; i++) /*  Iterate over number of channels */
    {   
        // Reset the cdist value for the given input sample to a high value since we want to find the minimum.
        cdist_current = 100000000; 
  
        for (int k =0 ; k < CODEBOKE_DIM; k++) 
        {        
            for (int j = 0; j < N_ROW * N_COL; j++)  // This is the second dimension of the input (a single channel) and codebook matrix  
            { 
            
                input_data[j] = input[i][j]; // An unseen input array in the latent space of a single channel
   
            }
            #if defined (PROFILE) 
            pi_perf_conf(1 << PI_PERF_CYCLES | 1 << PI_PERF_ACTIVE_CYCLES);   
            pi_perf_reset(); 
            pi_perf_start();
            #endif      
            cdist_next = cdist(input_data, &codebook[k][0], N_ROW, N_COL, OFF); // TODO: select the codebook channel in advance
            // printf("cdist: %f\t for codeword %d\n ", cdist_next, k);
            #if defined (PROFILE)   
            pi_perf_stop();
            uint32_t cycles = pi_perf_read(PI_PERF_ACTIVE_CYCLES);
            uint32_t tim_cycles = pi_perf_read(PI_PERF_CYCLES);
            printf("Performance of the dist func : %d cycles Timer : %d cycles\n", cycles, tim_cycles);
            #endif
    
            if (cdist_next < cdist_current)
            {
                cdist_current = cdist_next;
                k_current = k;
            }


            

        }/* Iterate over CODEBOOK */

        printf("Sample %d:\t The lowest cdist= %f\t for codeword %d\n", i, cdist_current, k_current);
        
        /* Save the current channel to export */

        cdist_final[i] = cdist_current; 
        codeword_id[i] = k_current; 
        // for (int j = 0; j < N_COL; j++)  // This is the second dimension of the input (a single channel) and codebook matrix
        // {
        //     quantized_val[i*N_COL] = (float32_t *)codebook[k_current+j]; // Save the quantized value to export

        // }

    } /* Iterate over the channels*/

    VectorPrint(cdist_final, "cdist= ", N_CHANNELS); 
    VectorPrint(codeword_id,  "codeword_id= ", N_CHANNELS);
    for (int i = 0; i < N_CHANNELS; i++)  // This is the second dimension of the input (a single channel) and codebook matrix
    {
        // printf("codeword of layer %d = %f\n", i, codeword_id[i]);
        float32_t temp = 0.0f; 
        temp = codeword_id[i];
        MatrixPrint(&codebook[(int32_t)(temp)][0], "quantized_val= ", 1, N_COL);
    }
    
    printf("Bye !\n");

    return errors;
}
