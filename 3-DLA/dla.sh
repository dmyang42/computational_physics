#!/bin/zsh

num=$1

gcc dla.c -o dla
./dla $num > test_$num
python plot.py $num
python plot_sandbox.py $num
python plot_boxcounting.py $num
mkdir result_$num && mv *_$num* ./result_$num