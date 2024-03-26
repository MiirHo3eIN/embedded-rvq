import torch 
import torch.nn as nn

import numpy as np 
import pandas as pd
import matplotlib.pyplot as plt






if __name__ == '__main__':

    # Load the codebook 

    codebook = torch.load('codebooks.pt', map_location=torch.device('cpu'))
    # codebook = codebook.to('cpu')   
    print(type(codebook))

    print(codebook.shape)
