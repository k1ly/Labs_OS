#!/bin/bash

#ps -ef 

echo Name:$'\t'$(basename $0 .sh)
if [ $1 -gt 0 ] 
then
echo Pid:$'\t'$1
echo PPid:$'\t'$(ps -o ppid= -p $1)
else
echo Wrong pid!
exit
fi

if [ $2 = "fd" ]
then
fd=($(ls /proc/$1/fd))
for i in ${fd[*]}
do
echo fd = $i
done
fi
