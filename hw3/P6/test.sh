#!/bin/bash

i=0

#while [ 1 ]
#do
  python generateList.py
  
  ./a.out < adjList1 > edgeList2
  
  python edgeList2adjList.py
  
  ans1=`md5sum adjList1|awk '{print $1}'`
  ans2=`md5sum adjList2|awk '{print $1}'`

  if [ "$ans1" == "$ans2" ]; then
      echo "PASS! ${i}"
  else
      echo "FAIL!"
      break
  fi
  ((i++))
#done
#
#echo "====== the correct edge list: ==============="
#cat edgeList1
#echo "========the correct adj list ============="
#cat adjList1
#echo "======= the edge list (a.out): =============="
#cat edgeList2
