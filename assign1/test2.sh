#!/bin/bash

list=( $( ./available_nodes.sh ) )
len=${#list[@]}

for (( i=0; i<$len ;i++));
do
    pairs="csews3,${list[$i]}"
    t=$(mpirun -n 2 --hosts $pairs ./a.out 1000 </dev/null)
    echo "$pairs,$t"
done
