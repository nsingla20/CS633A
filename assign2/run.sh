#!/bin/bash
echo "px,py,size,time">"data.csv"
mpicc code.c
list=( $( ./available_nodes.sh ) )
printf -v joined '%s,' "${list[@]}"
len=${#list[@]}
go(){
    local np=$(( $1*$2 ))
    t=$(mpirun -n $np --hosts $joined ./a.out $1 $2 $3 </dev/null)
    echo "$1,$2,$3,$t">>"data.csv"
}
for px in
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
