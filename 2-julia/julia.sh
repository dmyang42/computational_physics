#!/bin/zsh

x_0=$1
y_0=$2
num=$3

gcc julia.c -o julia -lm
./julia $x_0 $y_0 $num > julia_${x_0}_${y_0}_$num
python plot.py $x_0 $y_0 $num