#!/bin/zsh

x_0=$1
y_0=$2
num=$3

gcc julia_color.c -o julia_color -lm
./julia $x_0 $y_0 $num > julia_color_${x_0}_${y_0}_$num
python plot_color.py $x_0 $y_0 $num