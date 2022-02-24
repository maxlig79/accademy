#!/bin/bash

pkill -9 client 
pkill -9 server
./server &
> client1.log > client2.log > output.client1 > output.client2
(tail -f client1.log | ./client&) >> output.client1
echo -e "add;test1\nget;0\nadd;test2\nget;1\ndelete;test3" >> client1.log 
(tail -f client2.log | ./client&) >> output.client2
echo -e "add;silvana\nget;0\nadd;domnica\nget;1\nadd;paula\nget;2\ndelete;paula\nget;2" >> client2.log
sleep 1
echo -e "exit" >> client1.log
echo -e "exit" >> client2.log