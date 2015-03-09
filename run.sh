#!/bin/bash

for (( x=$1; x<$1+4; x++ ))
do
    /home/kim/xresearch/main.o /home/kim/xresearch/params/m0$x
    /home/kim/xresearch/main.o /home/kim/xresearch/params/p0$x
    /home/kim/xresearch/main.o /home/kim/xresearch/params/s0$x
done
