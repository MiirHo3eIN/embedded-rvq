import matplotlib.pyplot as plt

import torch
from torch import nn, einsum
import torch.nn.functional as F

import seaborn as sns
from einops import rearrange, repeat, reduce, pack, unpack
import numpy as np

import argparse
parser_help = r"""
    The implemented tests are: 
        - vector_sum_test: Test the vector sum function in C and Torch
        - matMul_test: Test the matrix multiplication function in C and Torch
        - vq_block_test: Test the VQ block
"""
parser = argparse.ArgumentParser(description='Type of test to be performed')
parser.add_argument('test', type=str, help=parser_help, choices=['vector_sum', 
                                                                 'cdist', 
                                                                 'matMul', 
                                                                 'vector_to_matrix', 
                                                                 'mat_transpose'])

# Parse the arguments
args = parser.parse_args()


__doc__ = r"""  

        This file contains several blocks to evaluate the inference mode of 
        Residual Vector Quantization (VQ).
        The VQ is a method to compress the input data by mapping it to a discrete set of values.
        It contains a core setting based on Euclidean distance or SinCos distance, and a set of 
        defined codewords where they are determined at the train mode.   
    """


N_ROW = 10
N_COL = 2

N_ROW_A = 10
N_COL_A = 20

N_ROW_B = 20
N_COL_B = 10



def vector_sum(x_in ):
    x = reduce(x_in**2, 'i d -> i', 'sum')
    x_c = torch.sum(x_in**2, dim=1)
    return x, x_c

def vector_sum_test():
    
    x = torch.Tensor(np.arange(1, N_ROW*N_COL+1, 1))
    x = x.view(N_ROW, N_COL)
    x_res, x_c_res = vector_sum(x)
    print("Value Generated by the Vector Quantization Repo Code:")
    print(x_res)
    print("*"*10)
    print("The implemented version in C:")
    print(x_c_res)

def vector_to_matrix_sum(x, y):
    __doc__ = r"""
        This kind of summation turns a vector into a matrix by summing the
        elements of the vector in a certain way.
    """
    x_rearranged = rearrange(x, 'i -> i 1') 
    y_rearranged = rearrange(y, 'j -> 1 j')
    print(x_rearranged.size(), y_rearranged.size())
    x_sum = x_rearranged + y_rearranged
  
    return x_sum

def vector_to_matrix_test(): 
    x = torch.Tensor(np.arange(1, N_ROW +1, 1))  
    y = torch.Tensor(np.arange(1, N_COL +1, 1))
    x_sum = vector_to_matrix_sum(x, y)
    print(x_sum.size())
    print(x_sum)


def matMul(x_in, y_in):
    x = einsum('i d, j d -> i j', x_in, y_in)*-2
    x_c = torch.mm(x_in, y_in.T)*-2
    return x, x_c

def mat_transpose_test(): 

    x = torch.Tensor(np.arange(1, N_ROW*N_COL+1, 1))
    x = x.view(N_ROW, N_COL)
    x_t = x.T   
    for i , j  in zip(range(N_ROW), range(N_COL) ):
        print(f"x = {x[i, :]},\n x_t = {x_t[j, :]}")
    print("*"*10)

def matMul_test():
    x = torch.Tensor(np.arange(1, N_ROW*N_COL+1, 1))
    x = x.view(N_ROW, N_COL)
    y = torch.Tensor(np.arange(1, N_ROW*N_COL+1, 1))
    y = y.view(N_COL, N_ROW)
    print(x.size(), y.size())
    print(f"x = {x[0, :]},\n y = {y[0, :]}")
    x_res, x_c_res = matMul(x, y)
    print("Value Generated by the Vector Quantization Repo Code:")
    print(x_res)
    print("*"*10)
    print("The implemented version in C:")
    print(x_c_res)



def distance_euclidean(x, embeds):
    __doc__ = r"""
        This is the distance function that is used in the VQ library at
        the high level Pytorch implementation for trainig and inference.
    """
    xy = einsum('i d, j d -> i j', x, embeds)*-2 # i*j
    x2 = reduce(x ** 2, 'i d -> i', 'sum') # i
    y2 = reduce(embeds ** 2, 'i d -> i', 'sum') 
    # j Since we already consider the embeds as a transposed matrix. 
    # In real implementation, we need to transpose the embeds matrix.
    # This is just for the sake of testing and developing the code. 
    # For real Implementation, other test codes and functions should be used.
    print(x2.size(), y2.size())
    print(xy.size()) 
    return torch.sqrt(rearrange(x2, 'i -> i 1') + rearrange(y2, 'j -> 1 j') + xy)

def distance_euclidean_c_level(x, embeds): 
    __doc__ = r"""
        This is the distance function that is used in the VQ library at
        the low level C implementation for inference. We are going to 
        use these values to compare the GAP9 results with the Pytorch ones. 
    """

    _, xy = matMul(x, embeds)
    print("xy:")
    print(xy.detach().numpy())
    _, x = vector_sum(x)
    print("x:")
    print(x.detach().numpy())
    _, y = vector_sum(embeds)
    print("y:")
    print(y.detach().numpy())   

    print(x.size(), y.size())
    x_sum = vector_to_matrix_sum(x, y) # Verified Version of this line is implemented in C
    print("x + y:")
    print(x_sum.detach().numpy())
    print("Fianl Summation:")
    print((x_sum + xy).detach().numpy() )
    return torch.sqrt(x_sum + xy)
    # return x_sum + xy


def euclidean_distance_test(): 

    # Test the VQ block
    # x = torch.randn(1, 128, 100)
    x = torch.Tensor(np.arange(1, N_ROW*N_COL+1, 1))
    x = x.view(N_ROW, N_COL)
    embeds = torch.Tensor(np.arange(1, N_ROW*N_COL+1, 1))
    embeds = embeds.view(N_ROW, N_COL)
    print(x.size(), embeds.size())
    print(f"x = {x[0, :]},\n embeds = {embeds[0, :]}")
    print("Value Generated by the Vector Quantization Repo Code:")
    x_res = distance_euclidean(x, embeds)
    print(x_res)
    print("*"*10)
    print("The implemented version in C:")
    x_c_res = distance_euclidean_c_level(x, embeds)
    print(x_c_res)


if __name__ == "__main__":
    print(f"The selected test is {args.test}\n")
    if args.test == 'cdist':
        euclidean_distance_test()
    elif args.test == 'vector_sum':
        vector_sum_test()
    elif args.test == 'matMul':
        matMul_test()
    elif args.test == 'vector_to_matrix':
        vector_to_matrix_test()
    elif args.test == 'mat_transpose': 
        mat_transpose_test()