import numpy as np
from actor import Actor
from math import tanh

class NeuralNetM:
    def __init__(self):
        pass

    def compute_action(self, actor, inputs):
        return self.net(actor.W, actor.B, inputs)

    #takes 144W, 72B, 24S.
    def net(self, W, B, inputs):
        Hull_data = self.compute_hulls(W[624:632], B[624:632], inputs[0:4])
        Li_data = self.compute_lidar(inputs[14:24])
        return self.fc_net(W[0:624], B[0:624], Hull_data + tuple(inputs[4:8]) + tuple(inputs[9:13]), Li_data, inputs[8], inputs[13])

    def fc_net(self, W, B, S, Li, Lc1, Lc2):

        fc_f1 = self.fc_layer(W[0:144], B[0:144], S, 12, self.relu)
        fc_f1 = self.fc_layer(W[144:240], B[144:240], fc_f1, 8, self.relu)
        fc_f1 = self.fc_layer(W[240:295], B[240:295], fc_f1 + list(Li), 5, self.relu)
        fc_f1 = self.fc_layer(W[295:305], B[295:305], fc_f1, 2, None)
        
        fc_f2 = self.fc_layer(W[0:144], B[0:144], tuple(S[0:4]) + tuple(S[8:12]) + tuple(S[4:8]), 12, self.relu)
        fc_f2 = self.fc_layer(W[144:240], B[144:240], fc_f2, 8, self.relu)
        fc_f2 = self.fc_layer(W[240:295], B[240:295], fc_f2 + list(Li), 5, self.relu)
        fc_f2 = self.fc_layer(W[295:305], B[295:305], fc_f2, 2, None)
        
        fc_b1 = self.fc_layer(W[305:449], B[305:449], S, 12, self.relu)
        fc_b1 = self.fc_layer(W[449:545], B[449:545], fc_b1, 8, self.relu)
        fc_b1 = self.fc_layer(W[545:600], B[545:600], fc_b1 + list(Li), 5, self.relu)
        fc_b1 = self.fc_layer(W[600:620], B[600:620], fc_b1, 2, None)
        
        fc_b2 = self.fc_layer(W[305:449], B[305:449], tuple(S[0:4]) + tuple(S[8:12]) + tuple(S[4:8]), 12, self.relu)
        fc_b2 = self.fc_layer(W[449:545], B[449:545], fc_b2, 8, self.relu)
        fc_b2 = self.fc_layer(W[545:600], B[545:600], fc_b2 + list(Li), 5, self.relu)
        fc_b2 = self.fc_layer(W[600:620], B[600:620], fc_b2, 2, None)

        if Lc2 == 1:
            D1, D2 = self.leg_contact(W[620:622], B[620:622], fc_f1, Lc1)
        else:
            D1, D2 = self.leg_contact(W[622:624], B[622:624], fc_b1, Lc1)
        if Lc1 == 1:
            D3, D4 = self.leg_contact(W[620:622], B[620:622], fc_f2, Lc2)
        else:
            D3, D4 = self.leg_contact(W[622:624], B[622:624], fc_b2, Lc2)
        return D1, D2, D3, D4

    # n is number of output nodes
    # k is number of input signals
    #takes n*kW, n*kB, kS
    def fc_layer(self, W, B, S, n, A):
        output = []
        for i in range(n):
            node = 0.0
            k = len(S) * i
            for j in range(len(S)):
                node += S[j] * W[j + k] + B[j + k]
            if A:
                output.append(A(node))
            else:
                output.append(node)
        return output

    #takes 2W, 2B, 2S, 1Lc
    def leg_contact(self, W, B, S, Lc):
        O1 = tanh(S[0] + Lc * self.relu(S[0] * W[0] + B[0]))
        O2 = tanh(S[1] + Lc * self.relu(S[1] * W[1] + B[1]))
        return O1, O2

    #takes 8W, 8B, 4S.
    def compute_hulls(self, W, B, S):
        Hull_A = self.relu_sum(W[0:2], B[0:2], S[0])
        Hull_B = self.relu_sum(W[2:4], B[2:4], S[1])
        Hull_C = self.relu_sum(W[4:6], B[4:6], S[2])
        Hull_D = self.relu_sum(W[6:8], B[6:8], S[3])
        return Hull_A, Hull_B, Hull_C, Hull_D

   #reduces 10Lidar signals to three. Similar to a 1d conv. One unit signal overlap
    def compute_lidar(self, S):
        Li_top = tanh(S[0] + S[1] + S[2] + S[3])
        Li_mid = tanh(S[3] + S[4] + S[5] + S[6])
        Li_bot = tanh(S[6] + S[7] + S[8] + S[9])
        return Li_top, Li_mid, Li_bot

    #takes 2W, 2B, 1S. Sum of signal through weight/bias with same signal through ReLu.
    #puts result through tanh.
    def relu_sum(self, W, B, S):
        output = S * W[0] + B[0]
        output += self.relu(S * W[1] + B[1])
        return tanh(output)

    def relu(self, x):
        return x * (x > 0)
