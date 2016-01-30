#!/bin/bash
if [ -f systemCallResults.txt ]
then 
rm systemCallResults.txt
fi
g++ systemCall.cpp
for ((i=0;i<1000;i++))
do
sudo nice --19 ./a.out >> systemCallResults.txt
done
