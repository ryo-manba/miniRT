#!/bin/bash
CYAN="\033[36m"
find ./rtfiles/invalid_rtfiles -name "*.rt" | sort > tempfile
echo "---INVALID RTFILE TEST---"
while read line
do
    echo -en $CYAN[CASE]
    filename=(${line//\// })
    echo ${filename[3]}
    ./miniRT $line
done < tempfile
rm tempfile
