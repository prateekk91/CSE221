#!/bin/bash
g++ -O0 good_contention.cpp -o contention
outfile=$(mktemp)
count=1

for (( i=1; i <= 20; i++ ))
do
	for (( j=1;j<=$i;j++))
	do
		(./contention "f"$j) >> "${outfile}$i" &
	done
	wait
done
wait

rm resultContention

for (( i=1; i <= 20; i++ ))
do
	summ=0
	while IFS='' read -r line || [[ -n "$line" ]]; do
		typeset -i x=${line}
	    summ=`expr $summ + $x` 
	done < "${outfile}$i"
	summ=`expr $summ / $i`
	echo "i=" $i ":" $summ >> resultContention
done
