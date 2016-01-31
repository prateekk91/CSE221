#!/bin/bash
if [ -f systemCallResults.txt ]
then 
rm systemCallResults.txt
fi
g++ -O0 systemCall.cpp
sum=0
for ((i=0;i<1000;i++))
do
out=`sudo nice --19 ./a.out`
echo $out >> systemCallResults.txt
((sum+=out))
done
((sum/=1000))
echo "System Call time mean= " $sum
