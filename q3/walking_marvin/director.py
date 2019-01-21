import numpy as np
from actor import Actor
import random as rand
import pickle
import time
import datetime

SURVIVE = 10
RANDOM = 3
NOISE = 0.1

class Director:

    pop = 6

    def __init__(self, pop=100, train=True):
        self.actors = []
        if train:
            self.pop = pop
            for i in range(pop):
                self.actors.append(Actor())
                self.actors[i].randomize_actor()

    def get_actor(self, index):
        assert index < len(self.actors)
        return self.actors[index]

    def export_top_actor(self, fitness_scores):
        import datetime
        st = datetime.datetime.fromtimestamp(time.time()).strftime('%Y-%m-%d_%H:%M:%S')
        top_actor = self.actors[np.argsort(fitness_scores)[-1:][0]]
        with open("./top_actors/" + st + ".pkl", 'wb') as output:
            pickle.dump(top_actor, output, pickle.HIGHEST_PROTOCOL)

    def import_actor(self, filename):
        top_actor = pickle.load(open(filename, 'rb'))
        self.actors.append(top_actor)

    def mutate_actors(self, fitness_scores):
        top_actors = []
        for i in np.argsort(fitness_scores)[-SURVIVE:]: #SURVIVE? scalar?
            new_actor = Actor()
            new_actor.set_weights(self.get_actor(i).W)
            new_actor.set_biases(self.get_actor(i).B)
            top_actors.append(new_actor)
        for i in range(len(self.actors) - SURVIVE - RANDOM):
            new_weights = []
            new_biases = []
            for j in range(len(top_actors[0].W)):
                new_weights.append(top_actors[rand.randint(0, SURVIVE - 1)].W[j] + NOISE * rand.uniform(-1, 1))
            for j in range(len(top_actors[0].B)):
                new_biases.append(top_actors[rand.randint(0, SURVIVE - 1)].B[j] + NOISE * rand.uniform(-1, 1))
            self.actors[i].set_weights(new_weights)
            self.actors[i].set_biases(new_biases)
        for i in range(SURVIVE):  #SURVIVE
            self.actors[self.pop - i - 1 - RANDOM].set_weights(top_actors[i].W)
            self.actors[self.pop - i - 1 - RANDOM].set_biases(top_actors[i].B)
        for i in range(RANDOM):  #RANDOM
            self.actors[self.pop - i - 1].randomize_actor()
