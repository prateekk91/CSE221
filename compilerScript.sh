#!/bin/bash
g++ -O0 readingtime.cpp -o readingtime
g++ -O0 loop.cpp -o loop
g++ -O0 procCreate.cpp -o procCreate
g++ -O0 contextSwitch.cpp -o contextSwitch
g++ -O0 procedure.cpp -o procedure
g++ -O0 -pthread kernel_thread.cpp -o kernel_thread
./readingtime
./loop
./procCreate
./contextSwitch
./procedure

