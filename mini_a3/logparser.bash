#!/bin/bash

#Freddie Liu, 260551011, freddie.liu@mail.mcgill.ca
#remarks for myself
#add backslash\ when you want to fix the [bracket] in the string. (receiver, recive_time)

#1.1 if no params given
if [[ -z $1 ]]
then
    echo "Usage ./logparser.bash <logdir>"
    exit 1
fi

#1.2 if not a dir
if [[ !(-d $1) ]]
then
    echo "Error: $1 is not a valid directory name"
    exit 2
fi

#1.3 parsing with 6 entries
#find all files with .log
logfile=$(ls $1 |grep '.log' |sort)
for i in $logfile
do
        #first entry    
        broadcaster=$(basename -s .log $i |sort)
        #msg id in each log file
        msg_id=$(cat $1/$i | grep -oP '(?<=broadcastMsg FINE: Broadcast message request received. Translating to point-to-point messages : )[0-9]+' |sort -n)
        for j in $msg_id
        do
                #find all the receiving msg lines in all the files associated with broadcaster and msg_id
                matcher=$(grep -Rl "Received a message from. message: \[senderProcess:$broadcaster:val:$j\]" $1 |sort -n)
                #4th entry
                broadcast_time=$(cat $1/$i | grep -oP "\d{2}:\d{2}:\d{2}.\d{9}(?=.*broadcastMsg FINE: Broadcast message request received. Translating to point-to-point messages : $j( |$))" |sort -n)
                for k in $matcher
                do
                        #3rd entry
                        receiver=$(basename -s .log $k |sort -n)
                        #5th entry
                        receive_time=$(cat $k |grep -oP "\d{2}:\d{2}:\d{2}.\d{9}(?=.*FINE: $broadcaster: Received a message from. message: \[senderProcess:$broadcaster:val:$j\])")
                        #6th entry
                        deliver_time=$(cat $k | grep -oP "\d{2}:\d{2}:\d{2}.\d{9}(?=.*deliver INFO: Received :$j from : $broadcaster)")
                        echo $broadcaster $j $receiver $broadcast_time $receive_time $deliver_time >> logdata.csv
#echo $broadcaster $j $receive_time $deliver_time # $receiver $broadcast_time $receive_time $deliver_time # >> logdata.csv
                done
        done
done

#1.4 Generate shell output to csv
#find all the broadcasters and receivers
broadcast=$(awk '{print $1}' < logdata.csv | sort --unique)
receivers=$(awk '{print $3}' < logdata.csv | sort --unique)
receiversheader=$(echo $receivers |sed -e "s/ /,/g")
#header
echo "broadcaster,nummsgs,"$receiversheader >> stats.csv
for m in $broadcast
do
        #count the numbers of msg and sort per broadcasters
        allmsgnum=$(awk '$1 ~ /'"$m"'/{print $2}' < logdata.csv | sort --unique)
        msgnum=0
        for o in $(echo $allmsgnum)
        do
                msgnum=$(echo $msgnum+1 | bc)
        done
        #array: list the result horizontally
        status=()
        while IFS= read -r line
        do
                #count the numbers of msg delivered to each receiver
                allreceive=$(awk '$1 ~ /'"$m"'/ && $3 ~ /'"$line"'/{print $6}' < logdata.csv)
                receive=0
                for p in $(echo $allreceive)
                do
                        receive=$(echo $receive+1 | bc)
                done
                #calculate the percentage of delivery per receiver
                rawpercentage=$(echo "scale=4; $receive * 100 / $msgnum" | bc -l)
                #determine if percentage is an integer
                if percent=$(echo $rawpercentage | grep ".*.0000"); then
                        percentage=$(echo "$receive * 100 / $msgnum" | bc)
                else
                        percentage=$(echo "scale=4; $receive * 100 / $msgnum" | bc -l)
                fi
                status+=($percentage)
        done <<< "$receivers"
        (IFS=,; echo -e "$m,$msgnum,${status[*]}") >> stats.csv
done

#1.5 Convert from csv to html
echo "<HTML>" >> stats.html
echo "<BODY>" >> stats.html
echo "<H2>GC Efficiency</H2>" >> stats.html
echo "<table>" >> stats.html
print_header=true
while read INPUT ; do
  #distinguish header and data
  if $print_header;then
    echo "<tr><th>${INPUT//,/</th><th>}</th></tr>" ;
    print_header=false
    continue
  fi
  echo "<tr><td>${INPUT//,/</td><td>}</td></tr>" ;
done < stats.csv >> stats.html
echo "</table>" >> stats.html
echo "<BODY>" >> stats.html
echo "<HTML>" >> stats.html
