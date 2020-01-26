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
eject /media/pi/CORDIEBOT