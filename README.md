# Cordiebot2
This bot was created from a brass lamp found in a resale store. CordieBot 2 is a remake of the original Arduino version which was made as a present for my granddaughter's 11th birthday. The original Arduino version can be found in the repository: https://github.com/Breidenbach/CordieBot .

Note that the CordieBot is a bot named after my granddaughter Cordie (duh).

The new and improved CordieBot uses a Raspberry Pi model 3 A+ with logic written in C++.

- Another version is here on github in Python, but had many mysterious memory leaks and could only run a few hours before it used up all system memory resources.  Clearly that was unacceptable, so this version was created in the hopes that I could control memory leaks better in C++ than in Python.

This version uses logic similar to the original for the light show, but now has new features:
- Uses the Cepstral voice for better speach.
- Senses the number of times the touch switch is pressed in a short time:
  -  1 touch and CordieBot says the time of day and date, possibly followed by a proclamation.
  -  2 touches and she says the current weather based on the location of the CordieBot, possibly followed by a proclamation.
  -  3 touches and she says the quote for the day from BrainyQuote.com.
  -  4 touches to repeat the previous proclamation.
  -  5 touches and she tells her verion.
  -  8 touches and she tells her origin story.
  -  9 touches and she tells her internal temperature.
- Holding the button for more than 5 seconds causes a shutdown of the system, so that a reboot can occur.  CordieBot must be powered off and powered back on to reboot.
- Checks for a USB drive on start up, and when internet access is disrupted.  If the USB drive is found, checks for a new wpa_supplicant.conf file or cordiebot executable files.  If either is found, copy the file(s) using special scripts into the appropriate directory. Thus this version has the capability of changing the WIFI name and password without a keyboard as well as updating the software.  It is expected that the USB drive will be removed during the reboot process.
- This version uses multithreading to overlap the light show and speech.
- The CordieBot has an internal fan and temperature sensor, so that when the internal temperature is high the fan may help cool its logic.

## PROCLAMATIONS

After the weather and time messages, the CordieBot will randomly make a proclamation drawn from a file of messages.  There are three types of proclamations:  for a specific date, for a specific month and day of any year, and for any date.  Proclamation examples:  "Today is mom's birthday" and "I am not the droid you are looking for".  The random selection is prioritized to most often select the current day's statements, followed by those that are for any year on the current date, followed by any other statements.

The proclamation file can be updated remotely using PubNub as a secure communication channel to the CordieBot and cbot_communication on a host computer.  Messages may be added, updated, deleted, and retrieved.  Using the cordieBot_listen program on a local RaspberryPi, the messages can be checked for how they will sound when they are spoken.  Sometimes phonetic editing is required to make a message sound good.  The message text may be altered using the Speech Synthesis Markup Language (https://www.w3.org/TR/speech-synthesis11/) and then tested using a local RaspberryPi.

## DEPENDENCIES

wiringPi is used to access the Pi hardware inputs and outputs.  aoss is used to speak the phrases.

## FILES

### Library modules:
- cbotLights (.cpp and .h) provides the ramping and color change routines for the tri-color LEDs.
- cbotButton (.cpp and .h) debounces and counts presses of the touch switch.
- GPIOtoWiringpi.h maps RaspberryPi GPIO numbers to Wiring Pi numbers.
- messages (.cpp and .h) handles many functions relating to loading, updating, and storing the proclamation file.
- wiringPiMCP3002 (.cpp and .h) connects to the MCP3002 chip over SPI to read temperature values from the TMP36 sensor.
- wiringPiTLC59711 (.cpp and .h) sends data to the adafruit TLC59711 LED PWM board.

### The CordieBot application:
  - cordiebot: the main script
  - CordieBot update scripts, executed when a USB drive is sensed:
    - cp_cordiebot.sh: copies cordiebot files from a USB drive to the current directory
    - cp_wpa_conf.sh: copies the wpa_supplicant.conf file from a USB drive to /etc/wpa_supplicant/
  - cordiebot_listen:  uses PubNub to communicate with the html app on home computer   
### Scripts to remotely update the proclamation file:
  - cbot_communication.html:  communicates from a host computer to the CordieBot to maintain the file of proclamations spoken after the time.
  - Cbot_style.css:  style definitions used by cbot_communication.html
### Support files:
  - createproclamationfile.py:  Used to create an initial list of statements for the CordieBot to recite.
  - keys.js:  container for the CordieBot PubNub keyes used for communication to the CordieBot.  This file is used in all the files used in the PubNub communications - the host computer HTML file and CordieBot's listen program.
  - cordiebot.service.txt and cordiebot_listen.service.txt: These files, with the .txt extension removed, should be place in the /etc/systemd/system/ directory to start the CordieBot applications when the system is booted.

## DIRECTORY STRUCTURE

Make files and execution defaults are dependent on the file structure below.  Note that after building the application files, the executables must be moved to /home/[user]/CordiBot2 to be used automatically on boot.

/home/[user]/CordieBot2/ (executables and scripts for running CordieBot)

/home/[user]/ccpCordie/ (files for building CordieBot)
  - cbot/ (cordiebot main source files)
  - lib/ (specific libraries created for cordiebot features)
  - c-core/ (PubNub files)

## BOOT STARTUP

To start CordieBot on reboot, move the cordiebot.service.txt and cordiebot_listen.service.txt files to /etc/systemd/system/ with the .txt extension removed.  Then execute the following commands:

  - sudo systemctl daemon-reload
  - sudo systemctl enable cordiebot
  - sudo systemctl enable cordiebot_listen
  
  
  
## PRINTED CIRCUIT BOARD

To simplify connecting to external devices and provide some interface logic, a small PCB as been developed in the format similar to the RaspberryPi HAT.  The major diference is that this board does not have the ROM to identify it to the RaspberryPi.  The board was developed using KiCad, and files for the board are included in this repository in the PCB directory.

## HARDWARE

As mentioned above, the computer for the CordieBot is a RaspberryPi model 3A+.  Additional logic includes:
-  TMP36GT9Z temperature sensor
-  MCP3002 analog to digital converter (for reading the temperature sensor)
-  PAM8302A audio amplifier
-  AT42QT1010 adafruit momentary touch sensor
-  TLC59711 adafruit 12 channel 16 bit PWM LED driver
-  Sunon GM0501PFB3-8 fan
-  HEP170 diode and 2N2222 transistor for the fan driver
-  Miscellaneos resistors, capacitors, wiring.
