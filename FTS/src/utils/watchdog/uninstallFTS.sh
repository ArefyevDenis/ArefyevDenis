#!/bin/sh

if [ $# -ge 1 ]
then
    sudo service ${1} stop

    sudo update-rc.d -f ${1} remove

    sudo sed -i '/FTS_PATH/d' /etc/environment
    . /etc/environment

    if [ -e /etc/init.d/${1} ]; 
    then
        sudo rm /etc/init.d/${1}
    fi
    chmod -x watchdogFTS.sh
    echo "${1} uninstalled"
else
    echo "Need NAME_deamon"
fi

exit 0
