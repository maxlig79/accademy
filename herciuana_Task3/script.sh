#!/bin/bash
pkill -9
./server &
> client1.log > client2.log 
(tail -f client1.log) | ./client &
echo -e "add;yes1\nadd;no1\nget;1" >> client1.log
(tail -f client2.log) | ./client &
echo -e "add;yes2\nadd;no2\nget;0" >> client2.log