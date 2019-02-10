#!/bin/bash
if [ $# -eq 2 ]
	then
		for filename in ../SubReadyActors_nnm/$1/$2/*.pkl; do
			python3 marvin.py "$filename"
		done
	else
		for filename in ../SubReadyActors_nnm/*/*/*.pkl; do
			python3 marvin.py "$filename"
		done
fi
