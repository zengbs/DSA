#!/bin/bash




k=0

while [ 1 ]
do

  f=4
  t=7

  for i in 0 1 2 3 4 5 6 7 8 9
  do
  
    From=`python generate.py|head -n 1`
    To=`python generate.py|tail -n 1`
  
    sed -i "${t}s/.*/${From}/" data1 
    sed -i "${f}s/.*/${To}/"   data1 

    f=`python -c "print($f+6)"`
    t=`python -c "print($t+6)"`
  

  done


  ans1=`make|sed '1q;d' | awk '{print $2}'`
  ans2=`make|sed '2q;d' | awk '{print $2}'`
  ans3=`make|sed '3q;d' | awk '{print $2}'`
  ans4=`make|sed '4q;d' | awk '{print $2}'`


  if (( 0 > $ans1 || 0 > $ans2 || 0 > $ans3 || 0 > $ans4 )); then

     echo "FAIL!"
     break
  fi 
   echo "PASS! $k"

  k=$(( $k + 1 ))
exit
done
