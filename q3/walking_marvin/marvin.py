import sys
sys.path.insert(0, './nets')
import gym
from director import Director
from actor import Actor
from nnm import NeuralNetM
import numpy as np
import sys

from args import get_args


def input_delta(list1, list2):
    """Calculates the cumulative difference between two lists."""
    delta = 0.0
    for i in range(len(list1)):
        delta += abs(list1[i] - list2[i])
    return delta

def get_director(args):
    """Creates a new director based on args."""
    director = Director(args.pop, args.noise)
    if args.survive is not None:
        director.survive = args.survive
    if args.random is not None:
        director.random = args.random
    if args.silent == False:
        print("population = {pop}\nnoise = {noise}\nsurvive = {survive}\nrandom = {random}".format(pop=director.pop, noise=director.noise, survive=director.survive, random=director.random))
    return director

def main():
    """Main function:

    Gets command line arguments and dispatches to preview mode or
    training mode as necessary.
    """
    args = get_args()
    env = gym.make('Marvin-v0')
    director = get_director(args)

    if args.mode == 'p':
        if args.path is None:
            print('No actor provided. Use [--load PATH] to set a path.')
            sys.exit()
        actor = director.import_actor(args.path)
        if args.silent == False:
            print(actor.W)
            print(actor.B)
        preview(args, env, actor)
    if args.mode == 't':
        train(args, env, director)

def preview(args, env, actor):
    """Preview mode.

    Runs the given actor through a attempt on the env
    and renders the attempt.
    """
    neural_net = NeuralNetM()
    inputs = [0] * 24
    fitness = 0.0
    action = [0.0, 0.0, 0.0, 0.0]
    env.reset()
    while True:
        prev_inputs = inputs
        inputs, delta_fitness, done, prob = env.step(action)
        fitness += delta_fitness
        action = neural_net.compute_action(actor, inputs)
        env.render(mode='human')
        if done:
            break
        if input_delta(prev_inputs, inputs) < 0.001:
            fitness += -100
            break
    if args.silent == False:
        print(fitness)

def train(args, env, director):
    """Training mode.

    Trains successive generations of actors and checks each generation for
    its best results. Exports any actors that express a fitness above a given threshold.
    """
    neural_net = NeuralNetM()
    generation = 0
    overall_top_fitness = -100
    top_fitness = -100
    top_actors = 0
    instance = args.inst
    epoch = 0
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
        top_fitness = np.amax(fitness_scores)
        if top_fitness > overall_top_fitness:
            overall_top_fitness = top_fitness
        if args.silent == False:
            print(generation)
            print(['%.f' % elem for elem in sorted(fitness_scores, reverse=True)])
            print("         Overall top actor = %d" % overall_top_fitness)
            print("This generations top actor = %d" % top_fitness)
        if top_fitness > 300:
            top_actors = -10
            director.export_super_actor(fitness_scores, instance, generation, epoch)
        elif top_fitness > 200:
            top_actors += 1
            if args.custom_path is not None:
                director.export_top_to_path(fitness_scores, args.custom_path)
            else:
                director.export_top_actor(fitness_scores, instance, generation, epoch)
        if top_actors >= 20:
            top_actors = 0
            del director
            director = get_director(args)
            epoch += 1
        elif generation > 500 or (generation > 100 and overall_top_fitness < 0):
            generation = 0
            del director
            director = get_director(args)
            if top_actors > 0:
                epoch += 1
            top_actors = 0
        else:
            director.mutate_actors(fitness_scores)
        generation += 1
        if args.silent == True:
            print('.', end='', flush=True)

if __name__== "__main__":
    main()
