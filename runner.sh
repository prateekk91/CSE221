#!/bin/bash
if [ -f systemCallResults.txt ]
then 
rm systemCallResults.txt
fi
g++ -O0 systemCall.cpp
for ((i=0;i<1000;i++))
do
./a.out >> systemCallResults.txt
done
