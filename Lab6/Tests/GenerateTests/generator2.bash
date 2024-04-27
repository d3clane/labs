#!/bin/bash

from=$1
to=$2
step=$3
maxVal=$4
testsDir=$5

generate="./generate"
stdQSort="./stdQSort"

for ((size=from; size<=to; size+=step)); do
        $generate $size $maxVal > "$testsDir/${size}.tmp"

        $stdQSort $size < "$testsDir/${size}.tmp" > "$testsDir/${size}.in"
done