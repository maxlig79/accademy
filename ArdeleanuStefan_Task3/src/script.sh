#!/bin/bash

./build/server&
sleep 1
rm -rf tmp
mkdir tmp
mkfifo tmp/input.pipe
(tail -f tmp/input.pipe) | ./build/client > tmp/log.0 &
mkfifo tmp/input1.pipe
(tail -f tmp/input1.pipe) | ./build/client > tmp/log.1 &
