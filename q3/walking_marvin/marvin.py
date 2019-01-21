import gym
from director import Director
from actor import Actor
from nn import NeuralNet
import numpy as np

FITNESS_GOAL = 100

env = gym.make('Marvin-v0')
director = Director()
neural_net = NeuralNet()
#for _ in range(100):
#    print(neural_net.output_layer(np.random.uniform(-1, 1, 60), np.random.uniform(-1, 1, 28), 0.0, 0.0, 0.0, 0.0))
top_fitness = -100
generation = 0
top_fitness = -100

def input_delta(list1, list2):
    delta = 0.0
    for i in range(len(list1)):
        delta += abs(list1[i] - list2[i])
#    print(delta)
    return delta

while True:
    fitness_scores = []
    inputs = [0] * 24
    for i in range(len(director.actors)):
        action = [0.0, 0.0, 0.0, 0.0]
        fitness = 0.0
        env.reset()
#        print("Rendered!")
        for _ in range(1000):
#            print("Reading state")
            prev_inputs = inputs
            inputs, delta_fitness, done, prob = env.step(action)
            fitness += delta_fitness
#            print("Computing action")
            action = neural_net.compute_action(director.get_actor(i), inputs)
            if generation >= 100 or top_fitness > 0:
                env.render()
            if input_delta(prev_inputs, inputs) < 0.001:
                fitness += -100
                break
            if done:
                break
        fitness_scores.append(fitness)
    print(generation)
    print(sorted(fitness_scores, reverse=True))
    top_fitness = np.amax(fitness_scores)
    print(top_fitness)
    print(top_fitness)
    print(top_fitness)
    if top_fitness > 100:
        director.export_top_actor(fitness_scores)
    director.mutate_actors(fitness_scores)
    generation += 1
#    break

