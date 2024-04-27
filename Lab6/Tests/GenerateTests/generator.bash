#!/bin/bash

from=$1
to=$2
step=$3
maxVal=$4
testsDir=$5

generate="./generate"

for ((size=from; size<=to; size+=step)); do
        $generate $size $maxVal > "$testsDir/${size}.in"
done