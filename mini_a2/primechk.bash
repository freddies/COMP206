#!/bin/bash

#Freddie Liu, Faculty of Science, freddie.liu@mail.mcgill.ca

# one input
# -f is used to indicate that the next argument to the script is the name of a file.
# -l is an optional argument to indicate whether the script should only print the largest prime number in its output.

OPT=$1   # option
FILE=$2  # filename
OPT2=$3  # option 2

# 2.2 Make sure that there is an argument
if [[ $# == 0 ]]; then
        echo "Error_1: No Input"
        exit 1
fi


# optionF & optionL
case $OPT in
  -f)
        #optionF: Determine if filename inputs correctly, if so, execute primechk.    
        # 2.5 both options
       	[ -z $FILE ] && { echo "Error_1: File Name Missing"; exit 1; } ||

           if [[ "$OPT2" == "-l" ]]; then
                for i in $(cat $FILE); do

        if /home/2013/jdsilv2/206/mini2/primechk $i > /dev/null = "The number is a prime number"
        then
		if [[ -z $i ]]; then
                        echo "Error_3: No Prime Numbers"
                else

			max=0
			if [ $i -gt $max ]
			then
				max=$i
			fi
			echo $max
		fi
        fi
        done
else # 2.4 only option F w/o option L
        for i in $(cat $FILE); do
        if /home/2013/jdsilv2/206/mini2/primechk $i > /dev/null = "The number is a prime number"
        then
                if [[ -z $i ]]; then
                        echo "Error_3: No Prime Numbers"
                else
                        echo $i
                fi
        fi
        done
           fi

        ;;
 -l)
	#optionL: Determine if input format is correct, if so, execute primechk.
        [ -f $FILE ] && { echo "Error_1: Incorrect Format"; exit 1; } ||
        if [[ "$OPT2" == "-f" ]] && [[ -f $FILE ]]; then # 2.5 both options
        for i in $(cat $FILE); do

        if /home/2013/jdsilv2/206/mini2/primechk $i > /dev/null = "The number is a prime number"
        then
                if [[ -z $i ]]; then
                        echo "Error_3: No Prime Numbers"
                else
                        max=0
                        if [ $i -gt $max ]
                        then
                                max=$i
                        fi
                        echo $max
                fi
        fi
        done
        fi
        ;;
   *)
    echo "Error_1: Incorrect Usage" 
    exit 1
    ;;
esac

#2.3 Determine if file exists
if [ ! -f "$FILE" ]; then
        echo "Error_2: Unable to locate this file."
        exit 2
fi

