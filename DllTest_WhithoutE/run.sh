#!/bin/bash

# set -xv

rm -f core*

make

if [ $? -eq 0 ]
then
	echo "Make Sucess"
else
	echo "Make Fail"
fi

CurDir=`pwd`
echo "hellow!"${CurDir}

ulimit -c unlimited

echo "LD_LIBRARY_PATH="${LD_LIBRARY_PATH}
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CurDir}
echo "LD_LIBRARY_PATH="${LD_LIBRARY_PATH}


echo "Input Shared libyary use method: 1. Link, 2. Dynamic Load"
read input
echo "Input is: "${input}

if [ ${input} = 1 ] 
then
	./main
else
	./mainWithDynamicLoad
fi

