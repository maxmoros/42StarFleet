#!/bin/bash
if [ $# -eq 2 ]
	then
		for filename in actors/top_actors/$1/$2/*.pkl; do
			python3 marvin.py --mode p -l "$filename"
		done
	else
		for filename in actors/top_actors/*/*/*.pkl; do
			python3 marvin.py --mode p -l "$filename"
		done
fi
