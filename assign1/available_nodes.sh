#!/bin/bash
for i in {1..2}
do
    timeout 1 mpirun --hosts csews$i hostname >/dev/null 2>&1
    if [ $? == 0 ]
    then
        echo "csews$i"
    fi
done
