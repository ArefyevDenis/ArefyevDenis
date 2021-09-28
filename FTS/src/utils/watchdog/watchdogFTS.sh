#!/bin/sh

if [ $# -ge 2 ]
then
    export FTS_MODULES_CFG_PATH=${2}/../../../cfg
    cd ${2}/../../../bin
else
    export FTS_MODULES_CFG_PATH=${PWD}/../../../cfg
    cd ${PWD}/../../../bin
fi

export LD_LIBRARY_PATH=:${PWD}:${LD_LIBRARY_PATH}
export TMPDIR=/tmp


if [ $# -ge 1 ]
then
    while [ 1 ] 
    do
    ps auxw | grep "FTSKonsole ${1}" | grep -v grep | grep -v watchdogFTS.sh | grep -v bin > /dev/null
    if [ $? != 0 ]
    then
        if [ $# -ge 2 ]
        then
            ./FTSKonsole ${1} > ../log/${1}.log
        else
            ./FTSKonsole ${1}
        fi
    fi
    sleep 1
    done
else
    echo "Need PROGRAM_ID"
fi

exit 0
