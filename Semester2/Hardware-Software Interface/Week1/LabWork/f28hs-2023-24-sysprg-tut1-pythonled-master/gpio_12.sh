#!/bin/bash
#

# the pin to control
PIN=12

# HINT: use the pinout command (from the command-line) to visualise pin numbers

# check whether the gpio command (for the wiringPi library) is installed
if [ -z "`which gpio`" ]
then echo "gpio command not installed."
     exit 1
fi

# set pin to output device for an LED
# NB: use -g for BCM numpering
gpio -g mode $PIN out

while [ 1 -eq 1 ]
do
    gpio -g write $PIN 1
    sleep 1s
    gpio -g write $PIN 0
    sleep 1s
done

exit 0
