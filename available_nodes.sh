#!/bin/bash
rm -f machinefile
av_l=()
av_ls=()
ind=0
for i in {1..60}
do
    timeout 1 mpirun --hosts csews$i hostname >/dev/null 2>&1
    if [ $? == 0 ]
    then
        us=$(mpirun --hosts csews$i ./get_cpus.sh)
        av_l+=("csews$i")
        av_ls+=($us)
        echo "csews$i : $us"
        ((ind++))
    fi
done
for (( i = 0; i<$ind; i++ ));
do
    for (( j = 0; j<$ind-i-1; j++ ));
    do

        if [ ${av_ls[j]} -gt ${av_ls[$((j+1))]} ]
        then
            # swap
            temp=${av_ls[j]}
            av_ls[$j]=${av_ls[$((j+1))]}
            av_ls[$((j+1))]=$temp
            temp=${av_l[j]}
            av_l[$j]=${av_l[$((j+1))]}
            av_l[$((j+1))]=$temp
        fi
    done
done
printf "%s\n" "${av_l[@]}" > machinefile
