#!/bin/bash

#Freddie Liu, Faculty of Science, freddie.liu@mail.mcgill.ca

#Requires two arguments
# 1. the input file
# 2. either the output file or the directory in which the output file is to be created

#1.2
if [[ -z $1 || -z $2 ]] # if <2 arguments given
then
    echo Error: Incorrect number of arguments.
    exit 1
elif [[ $1 = $2 ]] # if input == output
then 
    echo Error: Both input and output are the same.
    exit 2
elif [[ ! -r $1 ]] # if input DNE
then
    echo Error: The input file $1 does not exist and/or is not readable.
    exit 3
elif [[ ! -w $2 ]] # if output not writeable
then
    echo Error: The output file $2 cannot be written.
    exit 4
fi

#1.3
wrapper=$(basename $1) #name of the output file

if [[ -d $2 ]] #if output is a directory
then 
     /home/2013/jdsilv2/206/mini2/namefix $1 $2/$wrapper
     exit 0
elif [[ -f $2 ]] #if output is a file
then
     /home/2013/jdsilv2/206/mini2/namefix $1 $2
     exit 0
fi
