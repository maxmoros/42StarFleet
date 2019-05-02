#!/bin/bash
if [ $# -eq 2 ]
	then
		for filename in actors/marvin_superstars/SubReadyActors_nnm/$1/$2/*.pkl; do
			python3 marvin.py --mode p -l "$filename"
		done
	else
		for filename in actors/marvin_superstars/SubReadyActors_nnm/*/*/*.pkl; do
			python3 marvin.py --mode p -l "$filename"
		done
fi
