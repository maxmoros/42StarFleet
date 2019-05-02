import numpy as np
import random

WEIGHTS_SHAPE = [632,]
BIASES_SHAPE = [632,]

class Actor:
    """Contains weights and biases for a neural network.

    Attributes:
        W: An array of floats representing weights.
        B: An array of floats representing biases.
    """
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
        self.W = np.array(weights)

    def set_biases(self, biases):
        self.B = np.array(biases)

    def randomize_actor(self):
        for i in range(len(self.W)):
            self.W[i] = random.uniform(-1.0, 1.0)
        for i in range(len(self.B)):
            self.B[i] = random.uniform(-1.0, 1.0)
