#!/usr/bin/bash

for var in $(ls result/ | grep -oP '(..?[0-9]+)')
do
    x=$(head -n 1 result/${var}.csv | awk '{print $2;}')
    y=$(./check.o params/${var} 0 1 | sed -n 2p)
    echo ${var} $x $y >> comparison
done

