#!/bin/bash
str="input4."
for ((i=0;i<4;i++))
do
echo “=========================================================”
echo "test case $i"
str2=${str}"$i"".txt"
echo "input:"
cat $str2
echo ">>>>>>>>>>>>>>>>>"
echo "output"
./numerics $str2
echo “=========================================================”
done
