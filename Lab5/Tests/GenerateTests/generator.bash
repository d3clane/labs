#!/bin/bash

type=$1
from=$2
to=$3
step=$4
numberOfTests=$5
val1=$6
val2=$7
testsDir=$8

generate="./generate"

for ((size=from; size<=to; size+=step)); do
    for ((k=1; k<=numberOfTests; k++)); do
        $generate $type $size $val1 $val2 > "$testsDir/${size}_${k}.in"
    done
done