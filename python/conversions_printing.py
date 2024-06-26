import torch 
import torch.nn as nn

import numpy as np 
import pandas as pd
import matplotlib.pyplot as plt


from ndarrays2Carray import npy2Carray



if __name__ == '__main__':

    # Load the codebook 

    # codebook = torch.load('codebooks.pt', map_location=torch.device('cpu'))
    # codebook = codebook.to('cpu')   
    # print(type(codebook))

    # print(codebook.shape)

    input = np.load('inputs_v1.npy', allow_pickle=False)
    # codebook = np.load('codebooks.npy', allow_pickle=False)
    dists = np.load('trained_dists.npy', allow_pickle=False)

    codebook = np.load('trained_cb.npy', allow_pickle=False)

    print(codebook[0].shape)
    print("*"*100)
    print(dists.shape)
    print(input.shape)
    # print(dists[0, 0, :])
    # min_idx = np.argmin(dists, axis = -1)
    # for indx, val in enumerate(min_idx):
        # print(f"Sample {indx}:\t The lowest distance= {dists[indx, 0, val]}\t for codeword {val}")

    # Here we treat the inputs sepearately as a given input has dimension of [1x100]
    # Further, the codebook will be a 2D matrix in which we will have 128 rows and 100 columns

    npy2Carray(input[:, 0, :], 'input', 'input_v1.h', mode = 'w', fmt = '{}', ifndef = False)

    # for idx in range(input.shape[0]):
    #     if idx == 0:
    #         npy2Carray(input[:, 0, :], f'input_{idx}', f'c_samples/inputs.h', mode = 'w', fmt = '{}', ifndef = False)
    #     else: 
    #         npy2Carray(input[:, 0, :], f'input_{idx}', f'c_samples/inputs.h', mode = 'a', fmt = '{}', ifndef = False)
    # npy2Carray(input[0, 0, :], 'input', 'input.h', mode = 'w', fmt = '{}', ifndef = False)
    npy2Carray(codebook[0, :, :], 'codebook', 'trained_codebook.h', mode = 'w', fmt = '{}', ifndef = False)
