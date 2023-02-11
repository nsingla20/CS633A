#!/bin/bash
for i in {1..50}
do
    timeout 1 ping -c 1 -W 0.001 -s 10000 csews$i >/dev/null 2>&1
    if [ $? == 0 ]
    then
        timeout 1 mpirun --hosts csews$i hostname >/dev/null 2>&1
        if [ $? == 0 ]
        then
            echo "csews$i"
        fi
    fi
done
