#!/bin/bash
git pull origin master
for i in {10..16}
do 
    ssh kim@node$i-bigdata << EOF
cd xresearch
git pull origin master
logout
EOF
done
