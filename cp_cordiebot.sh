#!/bin/bash

# copy any cordiebot files to the current directory
if [ -f $1/cordiebot ]; then
   cp $1/cordiebot .
if [ -f $1/cordiebot_listen ]; then
   cp $1/cordiebot_listen .
if [ -f $1/cp_cordiebot.sh ]; then
   cp $1/cp_cordiebot.sh .
fi