#!/bin/bash
if [ $# -eq 0 -o $# -gt 2 ]; then
	echo "Usage:"
	echo "With two arguments, './gfx <zappy-server-hostname> <zappy-server-port>'"
	echo "With one argument, './gfx <zappy-server-port>' (and assume that host='localhost')"
	echo "This client can be started before the server spins up, in which case it will wait until the server is ready."
	exit
fi
pkill -f node bridge.js
zport=""
zhost=""
if [ $# -eq 1 ]; then
	zhost="localhost"
	zport="$1"
else
	zhost="$1"
	zport="$2"
fi
(
	[ $(basename $(pwd)) = 'bin' ] && cd ..
	cd gfx
	echo "Waiting for $zhost:$zport"
	while ! nc -z $zhost $zport; do
	  sleep 0.1
	done
	node bridge.js $zhost $zport &1>/dev/null &2>/dev/null &
)
sleep 0.5
while ! nc -z localhost 3000; do
  sleep 0.1
done
python -m webbrowser -t "http://localhost:3000"
