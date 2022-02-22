#!/bin/bash

pkill -9 client
pkill -9 server

./server &

rm input1.pipe 
rm input2.pipe

mkfifo input1.pipe
mkfifo input2.pipe

tail -f input1.pipe | ./client > log.client1 &
tail -f input2.pipe | ./client > log.client2 &

(echo -e "add;test1C1\nget;1\nadd;test2C1\ndelete;test1C1\nget;0\ndelete;ana" > input1.pipe) & (echo -e "add;test1C2\nadd;test2C2\ndelete;test1C2\nget;0" > input2.pipe)

sleep 1

echo "exit" > input1.pipe ; echo "exit" > input2.pipe