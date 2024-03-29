# f28hs-2023-24-SysPrg-Tut1-PythonLED

Scripts to make an LED on the Raspberry Pi blink, in Python (and also using wiringPi and Linux SysFS)

Use this repo together with the following lab sheet: [Labsheet Python LED](http://www.macs.hw.ac.uk/~hwloidl/Courses/F28HS/LabSheet24_LedButton_Python.pdf)

## 1. Wiring of your RPi

This tutorial works with a RPi, using the wiring shown on the [Labsheet](http://www.macs.hw.ac.uk/~hwloidl/Courses/F28HS/LabSheet24_LedButton_Python.pdf), with 1 LEDs connected:
- yellow LED on GPIO pin 12

You can ignore the button (on pin 16) that is connected on the right hand side of the diagram.

Note these are the pin numbers using BCM numbering (see last section on the Labsheet for an explanation)

## 2. Use Python for GPIO control

The file `test_led.py` contains Python code for controlling an LED.
Check the setting of `ledPin` in the script, and change it to the pin number
of the LED in your wiring: 12.

Then run:

> python3 test_led.py

This is probably the easiest way of controlling an LED, but it needs a full Python VM running to do so.
In this course we will learn how control such an LED in C, and then in ARM Assembler.
This script will still be useful when testing that your wiring is correct.

## 3. Install the wiringPi library

In Step 4 we will use the wiringPi library and command-line interface. This is very flexible and powerful, thus
recommended for testing your wiring. However, latest versions of Rasbpian no longer have this library pre-installed. So you need to download and install the library, using the steps (on your command-line) below:

> wget http://www.macs.hw.ac.uk/~hwloidl/Courses/F28HS/Resources/wiringpi-latest.deb

> sudo dpkg -i wiringpi-latest.deb

Now you should be able find a command 'gpio' in your path. Test this with:

> which gpio

/usr/bin/gpio 

You can print GPIO pin layout with this command:

> gpio readall 


## 4. Use wiringPi library with gpio front end

An alternative to using the above Python script is to install and use the
**wiringPi** library for the RPi. To do so, follow the instructions on page 2
of the [Labsheet](http://www.macs.hw.ac.uk/~hwloidl/Courses/F28HS/LabSheet22_LedButton_Python.pdf)
under heading "Option 2: WiringPi library and interface".

Once you have installed the library, try these instructions, to configure the pins as output devices:

> gpio -g mode 2 out

> gpio -g mode 12 out

Then turn the red LED on, and then off again, with these two lines:

> gpio -g write 2 1

> gpio -g write 2 0

Then turn the yellow LED on, and then off again, with these two lines:

> gpio -g write 12 1

> gpio -g write 12 0

Note that you can get a picture of the state of all pins using this command:

> gpio readall

You can make the yellow LED blink, by using this construct on the command-line:

> while [ 1 -eq 1 ] ;  do gpio -g write 12 1 ; sleep 2s ; gpio -g write 12 0 ; sleep 2s ; done

## Task: Developing a simple Python script for a blinking LED

The main task of this lab is to write a simple Python script to make an LED blink in the same way as
discussed in class for the on-chip ACT LED (pin 47). The LED should be connected via the breadboard to
pin 12. The code needs to configure this pin for output, and then in a loop turn the LED on/off, with a fixed
delay between state changes.

Start from the sample code discussed in class: `test_led.py`, which implements this control for the ACT
LED. You will have to change the code to work with pin 12.

## External Resources

Some useful videos to get you started are here:
- [GPIO pins](https://www.raspberrypi.com/documentation/computers/os.html#gpio-and-the-40-pin-header), from the official Raspberry Pi Docu
- ["How to set up your Raspberry Pi"](https://www.youtube.com/watch?v=wjWZhV1v3Pk), YouTube 
- ["Raspberry Pi Tutorial (Model B+) - Using a Breadboard and LED's"](https://www.youtube.com/watch?v=6Hau75Zkpj4) , YouTube 
