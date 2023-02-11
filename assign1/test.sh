#!/bin/bash
for i in {1..5}
do
    ./run.sh
    mv plot.png plot$i.png
    mv data.csv data$i.csv
done
