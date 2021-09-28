#!/bin/bash
#Используем программу так, чтобы параметр указывал путь, где будет создаваться файл buildnumber.h

FILENAME="buildnumber.h"

function CreateFile()
{
    NUM=$1
    if [ -z $1 ]
    then
	NUM=1
    fi

    echo "/* Generated by buildnumber.sh Version 0.1 */" > $FILENAME
    echo 						>> $FILENAME
    echo "#ifndef BUILD_NUMBER_H_" 			>> $FILENAME
    echo "#define BUILD_NUMBER_H_" 			>> $FILENAME
    echo 						>> $FILENAME
    echo "#define BUILDNUMBER $NUM"   			>> $FILENAME
    echo "#define BUILDNUMBER_STR \"$NUM\""		>> $FILENAME
    echo 						>> $FILENAME
    echo "#endif /* BUILD_NUMBER_H_ */"			>> $FILENAME

    return 0
}


if [ -z $1 ]
then
    echo "Usage: $0 <path to dir whith buildnumber>"
    exit 0
else
    if ! cd $1
    then
	echo "Не смог перейти в каталог $1, попробую его создать"
	if ! mkdirhier $1
	then
	    echo "Не смог создать каталог $1"
	    exit 1
	else
	    cd $1
	fi
    fi
fi

BUILDNUMBER=`cat $FILENAME | grep "BUILDNUMBER " | awk '{print $3}'`

if [ -z $BUILDNUMBER ]
then
    CreateFile 1
else
    let BUILDNUMBER=$BUILDNUMBER+1
    CreateFile $BUILDNUMBER
fi
