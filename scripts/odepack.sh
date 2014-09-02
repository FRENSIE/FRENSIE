#!/bin/bash
#
for FILE in `ls -1 *.f`;
do
  gfortran -c -O3 $FILE >& compiler.txt
  if [ $? -ne 0 ]; then
    echo "Errors compiling " $FILE
    exit
  fi
  rm compiler.txt
done
ar qc libodepack.a *.o
rm *.o
