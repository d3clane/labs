#!/bin/bash

from=$1
to=$2
step=$3
numberOfTests=$4
maxVal=$5
testsDir=$6

generate="./generate"
stdQSort="./stdQSort"

for ((size=from; size<=to; size+=step)); do
    for ((k=1; k<=numberOfTests; k++)); do
        $generate $size $maxVal > "$testsDir/${size}_${k}.in"
    done
done