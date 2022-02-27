#!/bin/bash

#touch ../CordieBot2logs/ctl.log
LOG='../CordieBot2logs/ctl.log'
echo $LOG
chmod a+rw $LOG
date > $LOG
echo "In cordiebot_ctl.sh" >> $LOG
USB='/media/pi/CORDIEBOT'
mkdir $USB
if mount /dev/sda1 $USB; then
	# copy any cordiebot files to the current directory
	echo "found USB" >> $LOG
	# copy the wpa_supplicant.conf file to the system directory if it exists
	if [ -f $USB/wpa_supplicant.conf ]; then
	   cp $USB/wpa_supplicant.conf /etc/wpa_supplicant/
		echo "copied wpa_supplicant.conf" >> $LOG
	else
		echo "wpa_supplicant.conf not found" >> $LOG
	fi
	# copy the cordiebot executable if it is newer on the USB
	if [ $USB/cordiebot -nt cordiebot ]; then
		unlink ./cordiebot
		cp $USB/cordiebot .
		chmod a+x cordiebot
		echo "copied cordiebot" >> $LOG
	else
		echo "cordiebot not copied" >> $LOG
	fi
	# copy the cordiebot_listen executable if it is newer on the USB
	if [ $USB/cordiebot_listen -nt cordiebot_listen ]; then
		unlink ./cordiebot_listen
		cp $USB/cordiebot_listen .
		chmod a+x cordiebot_listen
		echo "copied cordiebot_listen" >> $LOG
	else
		echo "cordiebot_listen not copied" >> $LOG
	fi
	# copy the cordiebot_ctl shell script if it is newer on the USB
	if [ $USB/cordiebot_ctl.sh -nt cordiebot_ctl.sh ]; then
		cp $USB/cordiebot_ctl.sh .
		echo "copied cordiebot_ctl.sh" >> $LOG
	else
		echo "cordiebot_ctl.sh not copied" >> $LOG
	fi
	# copy the key file if it is newer on the USB
	if [ $USB/keys.js -nt keys.js ]; then
		cp $USB/keys.js .
		echo "copied keys.js" >> $LOG
	else
		echo "keys.js not copied" >> $LOG
	fi
	umount /dev/sda1
else
	echo "USB not found" >> $LOG
fi