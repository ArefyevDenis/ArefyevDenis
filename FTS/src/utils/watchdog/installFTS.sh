#!/bin/sh

if [ $# -ge 1 ]
then
    cp ${1} output.tmp
    sudo sed -i "s%SET FTS_PATH%$PWD%g" output.tmp
    chmod +x output.tmp

    sudo sed -i '/FTS_PATH/d' /etc/environment
    echo FTS_PATH=\"$PWD\" | sudo tee -a /etc/environment
    . /etc/environment

    chmod +x watchdogFTS.sh

    sudo service ${1} stop
    sudo update-rc.d -f ${1} remove

    if [ -e /etc/init.d/${1} ]; 
    then
        sudo rm /etc/init.d/${1}
    fi

    sudo mv output.tmp /etc/init.d/${1}

    sudo update-rc.d ${1} defaults

    sudo service ${1} start

    echo "{1} installed and started"

else
    echo "Need NAME_deamon"
fi


exit 0