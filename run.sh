#!/bin/bash

for (( x=$1; x<$1+4; x++ ))
do
    /home/kim/xresearch/main.o /home/kim/xresearch/params/m$x
    /home/kim/xresearch/main.o /home/kim/xresearch/params/p$x
    /home/kim/xresearch/main.o /home/kim/xresearch/params/s$x
done
