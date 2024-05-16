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
        for ((k = 1; k <= numberOfTests; k += 1)); do
                $generate $size $maxVal >  "$testsDir/${size}_${k}.tmp"
                $stdQSort $size < "$testsDir/${size}_${k}.tmp" > "$testsDir/${size}_${k}.in"

                rm -rf $testsDir/${size}_${k}.tmp
        done
done