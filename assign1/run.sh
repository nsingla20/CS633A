#!/bin/bash
echo "source,destination,size,time">"data.csv"

list=( $( ./available_nodes.sh ) )
len=${#list[@]}
while read -r size
do
    for (( i=0; i<$len; i++ ));
    do
        for (( j=i+1; j<$len; j++));
        do
            pairs="${list[$i]},${list[$j]}"

            for z in {1..10}
            do
                t=$(mpirun -n 2 --hosts $pairs ./a.out $size </dev/null)
                echo "$pairs,$size,$t">>"data.csv"
            done
        done
    done
done < "size.txt"
python3 analy.py
