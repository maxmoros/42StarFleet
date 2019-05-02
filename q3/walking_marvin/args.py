import argparse

def get_args():
	"""Get command line arguments with argparse.
	"""
	parser = argparse.ArgumentParser()
	parser.add_argument('--mode', choices=['t', 'p'], required=True,
						help='Sets training or preview mode. (t/p)')
	parser.add_argument('--silent', action='store_true', default=False, dest='silent',
						help='Silence command-line output.')
	parser.add_argument('-s', '--save', type=int, default=0, dest='inst',
						help='Set the instance number to save to.')
	parser.add_argument('-l', '--load', dest='path',
						help='Define a file to load from.')
	parser.add_argument('--pop', type=int, default=50, dest='pop',
						help='Set population size for training mode.')
	parser.add_argument('--noise', type=float, default=0.1, dest='noise',
						help='Set noise value for training mode.')
	parser.add_argument('--survivors', type=int, dest='survive',
						help='Set survivors value for training mode.')
	parser.add_argument('--rand', type=int, dest='random',
						help='Set the number of random actors for training mode.')
	parser.add_argument('--path', dest='custom_path',
						help='Set a custom save path for top actors. (eg. "./top_actors_directory")')

	args = parser.parse_args()
	return args
