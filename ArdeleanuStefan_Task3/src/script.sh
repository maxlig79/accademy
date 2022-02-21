#!/bin/bash

pkill -f ./build/client 
pkill -f ./build/server

./build/server&

rm -rf tmp
mkdir tmp
mkfifo tmp/input.pipe
(tail -f tmp/input.pipe) | ./build/client > tmp/log.0 &
mkfifo tmp/input1.pipe
(tail -f tmp/input1.pipe) | ./build/client > tmp/log.1 &

(echo -e 'add;unu\nget;0\ndelete;doi' > tmp/input.pipe ) & (echo -e 'add;doi\nget;1\ndelete;doi' > tmp/input1.pipe)

sleep 0.5

echo 'exit' > tmp/input.pipe; echo 'exit' > tmp/input1.pipe