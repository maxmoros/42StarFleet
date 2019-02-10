#!/bin/bash
$(
	[ $(basename $(pwd)) = 'bin' ] && cd ..
	cd client
	python load_bots.py $@
)
