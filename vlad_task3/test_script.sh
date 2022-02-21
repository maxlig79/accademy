#!/bin/bash
rm /tmp/pipe1
rm /tmp/pipe2
mkfifo /tmp/pipe1
mkfifo /tmp/pipe2
./build/main_server &
touch client1.log
touch client2.log
./build/main_client --no-prompt < /tmp/pipe1 > client1.log &
./build/main_client --no-prompt < /tmp/pipe2 > client2.log &
(echo -e "add\nunu\nadd\ndoi\nget\n0\ndelete\ntrei\ndelete\ndoi\n" > /tmp/pipe1) & (echo -e "add\ntrei\nadd\npatru\nget\n0\ndelete\ndoi\ndelete\ntrei\n" > /tmp/pipe2)
cat client1.log
cat client2.log
