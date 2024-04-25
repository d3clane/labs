#!/bin/bash

from=$1
to=$2
step=$3
testsDir=$4

generate="./generate5"

for ((size=from; size<=to; size+=step)); do
    $generate $size > "$testsDir/${size}.in"
done