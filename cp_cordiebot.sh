#!/bin/bash

# copy any cordiebot files to the current directory
if [ -f $1/cordiebot ]; then
    unlink ./cordiebot
    cp $1/cordiebot .
    chmod a+x cordiebot
fi
if [ -f $1/cordiebot_listen ]; then
    unlink ./cordiebot_listen
    cp $1/cordiebot_listen .
    chmod a+x cordiebot_listen
fi
if [ -f $1/cp_cordiebot.sh ]; then
    cp $1/cp_cordiebot.sh .
fi
if [ -f $1/cp_wpa_conf.sh ]; then
    cp $1/cp_wpa_conf.sh .
fi
if [ -f $1/keys.js ]; then
    cp $1/keys.js .
fi
eject /media/pi/CORDIEBOT