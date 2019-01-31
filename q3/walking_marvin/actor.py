import numpy as np
import random

WEIGHTS_SHAPE = [632,]
BIASES_SHAPE = [632,]

class Actor:
    W = []
    B = []
    def __init__(self):
        self.W = np.zeros(WEIGHTS_SHAPE)
        self.B = np.zeros(BIASES_SHAPE)

    def get_weights(self):
        return self.W

    def get_biases(self):
        return self.B

    def set_weights(self, weights):
#        assert self.W.shape == weights.shape 
        self.W = np.array(weights)

    def set_biases(self, biases):
#        assert self.B.shape == biases.shape
        self.B = np.array(biases)

    def randomize_actor(self):
        for i in range(len(self.W)):
            self.W[i] = random.uniform(-1.0, 1.0)
        for i in range(len(self.B)):
            self.B[i] = random.uniform(-1.0, 1.0)
'''     #Stupid since permanent.
    def dropout_layer(self, droupout=0.1):
        for i in range(len(self.W)):
            x = random.randint(0, 1 // dropout)
            if x == 0:
                self.
'''
