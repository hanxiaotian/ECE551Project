#!/bin/bash
str="input3."
for ((i=0;i<6;i++))
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
