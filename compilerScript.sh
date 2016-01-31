#!/bin/bash
g++ -O0 readingtime.cpp -o readingtime
g++ -O0 loop.cpp -o loop
g++ -O0 procCreate.cpp -o procCreate
g++ -O0 contextSwitch.cpp -o contextSwitch
g++ -O0 procedure.cpp -o procedure
g++ -O0 -pthread kernel_thread.cpp -o kernel_thread
sudo nice --19 ./readingtime
sudo nice --19 ./loop
sudo nice --19 ./procedure
sudo nice --19 ./procCreate
sudo nice --19 ./contextSwitch
sudo nice --19 ./sysCallRunner.sh
