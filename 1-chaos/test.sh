#!/bin/zsh

lambda_start=$1
lambda_end=$2
lambda_update=$3
x=$4
i=$5

gcc chaos.c -o chaos -lm
./chaos $lambda_start $lambda_end $lambda_update $x > test_$i
python plot.py $lambda_start $lambda_end $lambda_update $i > peak_$i
