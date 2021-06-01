#!/bin/bash


C=0


while true
do

python generate.py -s $1 -p $2 > input

ans1=`./a1.out < input | sha1sum|awk '{print $1}'`
#ans2=`./a2.out < input|sha1sum|awk '{print $1}'`
ans3=`python check.py < input|sha1sum|awk '{print $1}'`


if [[ "$ans1" != "$ans3" ]]; then
  echo "Oppp!"
  break
else
  echo "Pass! ${C}"
fi

C=$((C+1))

done
