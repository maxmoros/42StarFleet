#!/bin/bash
if [ $# -eq 2 ]
	then
		for filename in top_actors/$1/$2/*.pkl; do
			python3 marvin.py "$filename"
		done
	else
		for filename in top_actors/*/*/*.pkl; do
			python3 marvin.py "$filename"
		done
fi
