import numpy as np
from actor import Actor
import random as rand
import pickle
import time
import datetime
import os


class Director:
    
    pop = 6
    noise = 0.1
    random = 0
    survive = 1

    def __init__(self, pop=100, noise=0.1, train=True):
        self.actors = []
        if train:
            self.pop = pop
            self.noise = noise
            self.survive = pop // 10
            self.random = pop // 20
            for i in range(pop):
                self.actors.append(Actor())
                self.actors[i].randomize_actor()
        print("population = {pop}\nnoise = {noise}\nsurvive = {survive}\nrandom = {random}".format(pop=pop, noise=noise, survive=self.survive, random=self.random))

    def get_actor(self, index):
        assert index < len(self.actors)
        return self.actors[index]

    def make_path(self, group, instance, epoch):
        os.system("sh create_dir.sh " + str(group) + " " + str(instance) + " " + str(epoch))

    def export_top_actor(self, fitness_scores, instance=0, generation=0, epoch=0):
        st = datetime.datetime.fromtimestamp(time.time()).strftime('%m-%d_%H:%M_')
        top_actor = self.actors[np.argsort(fitness_scores)[-1:][0]]
        if instance > 0:
            st = str(instance) + "/" + str(epoch) + "/" + str(st) + str(generation)
        self.make_path("top_actors", instance, epoch)
        with open("./top_actors/" + st + ".pkl", 'wb') as output:
            pickle.dump(top_actor, output, pickle.HIGHEST_PROTOCOL)

    def export_super_actor(self, fitness_scores, instance=0, generation=0, epoch=0):
        st = datetime.datetime.fromtimestamp(time.time()).strftime('%m-%d_%H:%M_')
        top_actor = self.actors[np.argsort(fitness_scores)[-1:][0]]
        if instance > 0:
            st = str(instance) + "/" + str(epoch) + "/" + str(st) + str(generation)
        self.make_path("super", instance, epoch)
        with open("./super_actors/" + st + ".pkl", 'wb') as output:
            pickle.dump(top_actor, output, pickle.HIGHEST_PROTOCOL)

    def import_actor(self, filename):
        print(filename)
        top_actor = pickle.load(open(filename, 'rb'))
        self.actors.append(top_actor)
        return top_actor

    def mutate_actors(self, fitness_scores):
        top_actors = []
        for i in np.argsort(fitness_scores)[-self.survive:]: #SURVIVE? scalar?
            new_actor = Actor()
            new_actor.set_weights(self.get_actor(i).W)
            new_actor.set_biases(self.get_actor(i).B)
            top_actors.append(new_actor)
        for i in range(len(self.actors) - self.survive - self.random):
            new_weights = []
            new_biases = []
            for j in range(len(top_actors[0].W)):
                rand_index = (rand.randint(0, self.survive * 2 - 1) % (self.survive * 5 // 3)) % self.survive
                new_weights.append(top_actors[rand_index].W[j] + self.noise * rand.uniform(-1, 1))
            for j in range(len(top_actors[0].B)):
                rand_index = (rand.randint(0, self.survive * 2 - 1) % (self.survive * 5 // 3)) % self.survive
                new_biases.append(top_actors[rand_index].B[j] + self.noise * rand.uniform(-1, 1))
            self.actors[i].set_weights(new_weights)
            self.actors[i].set_biases(new_biases)
        for i in range(self.survive):  #SURVIVE
            self.actors[self.pop - i - 1 - self.random].set_weights(top_actors[i].W)
            self.actors[self.pop - i - 1 - self.random].set_biases(top_actors[i].B)
        for i in range(self.random):  #RANDOM
            self.actors[self.pop - i - 1].randomize_actor()
