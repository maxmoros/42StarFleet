import gym
from director import Director
from actor import Actor
from nn import NeuralNet
from nn2 import NeuralNet2
from nn3 import NeuralNet3
from nnfc import NeuralNet4
from nnfc2 import NeuralNetFC
from nnm import NeuralNetM
from nnm_lite import NeuralNetM_lite
from nnmd import NeuralNetMD
import numpy as np
import sys

FITNESS_GOAL = 100

env = gym.make('Marvin-v0')
population = 50
noise = 0.1
if len(sys.argv) > 3:
    population = int(sys.argv[1])
    noise = float(sys.argv[2])

director = Director(population, noise)
neural_net = NeuralNetM_lite()
generation = 0
overall_top_fitness = -100
top_fitness = -100
top_actors = 0
instance = 0
epoch = 0

def input_delta(list1, list2):
    delta = 0.0
    for i in range(len(list1)):
        delta += abs(list1[i] - list2[i])
    return delta

if len(sys.argv) == 4:
    instance = int(sys.argv[3])

if len(sys.argv) == 2:
    actor = director.import_actor(sys.argv[1])
    print(actor.W)
    print(actor.B)
    inputs = [0] * 24
    fitness = 0.0
    action = [0.0, 0.0, 0.0, 0.0]
    env.reset()
    while True:
        prev_inputs = inputs
        inputs, delta_fitness, done, prob = env.step(action)
        fitness += delta_fitness
        action = neural_net.compute_action(actor, inputs)
        if generation >= 0 or top_fitness > 200:
            env.render()
        if done:
            break
        if input_delta(prev_inputs, inputs) < 0.001:
            fitness += -100
            break
    print(fitness)
    sys.exit()


while True:
    fitness_scores = []
    inputs = [0] * 24
    for i in range(len(director.actors)):
        action = [0.0, 0.0, 0.0, 0.0]
        fitness = 0.0
        env.reset()
        while True:
            prev_inputs = inputs
            inputs, delta_fitness, done, prob = env.step(action)
            fitness += delta_fitness
            action = neural_net.compute_action(director.get_actor(i), inputs)
            if done:
                break
            if input_delta(prev_inputs, inputs) < 0.001:
                fitness += -100
                break
        fitness_scores.append(fitness)
    print(generation)
    print(['%.f' % elem for elem in sorted(fitness_scores, reverse=True)])
    top_fitness = np.amax(fitness_scores)
    if top_fitness > overall_top_fitness:
        overall_top_fitness = top_fitness
    print(overall_top_fitness)
    print(top_fitness)
    print(generation)
    if top_fitness > 300:
        top_actors = -10
        director.export_super_actor(fitness_scores, instance, generation, epoch)
    elif top_fitness > 200:
        top_actors += 1
        director.export_top_actor(fitness_scores, instance, generation, epoch)
    if top_actors >= 20:
        top_actors = 0
        del director
        director = Director(population, noise)
        epoch += 1
    elif generation > 300 or (generation > 100 and overall_top_fitness < 0):
        generation = 0
        del director
        director = Director(population, noise)
        if top_actors > 0:
            epoch += 1
        top_actors = 0
    else:
        director.mutate_actors(fitness_scores)
    generation += 1

