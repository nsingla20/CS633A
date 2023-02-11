#!/bin/bash
echo "source,destination,size,time">"data.csv"
mpicc code1.c
list=( $( ./available_nodes.sh ) )
len=${#list[@]}
for k in {1..3}
do
    i=$(($RANDOM % $len))
    j=$(($RANDOM % $len))
    if [[ $i == $j ]]
    then
        j=$((($i+1)%$len))
    fi
    while read -r size
    do
            for z in {1..10}
            do
                pairs="${list[$i]},${list[$j]}"
                t=$(mpirun -n 2 --hosts $pairs ./a.out $size </dev/null)
                echo "$pairs,$size,$t">>"data.csv"
            done
    done < "size.txt"
done

python3 plot.py
