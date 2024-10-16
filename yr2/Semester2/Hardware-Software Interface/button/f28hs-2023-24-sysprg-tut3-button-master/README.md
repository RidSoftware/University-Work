# f28hs-2023-24-sysprg-tut3-button

Tutorial on C code to read input from a button input device (F28HS: Sys Prging)

Use this repo together with the following lab sheet: [Labsheet Button](http://www.macs.hw.ac.uk/~hwloidl/Courses/F28HS/LabSheet24_LedButton.pdf)

This builds on the [Tutorial 3 of SysPrg in F28HS](http://www.macs.hw.ac.uk/~hwloidl/Courses/F28HS/slides24_SysPrg_Tut3.pdf).

## Wiring

An **LED**, as output device, should be connected to the RPi2 using **GPIO pin 12.**

A **Button**, as input device, should be connected to the RPi2 using **GPIO pin 16.**

You will need resistors to control the current to the LED and from the Button.

The Fritzing diagram below visualises this wiring. You should now use the entire wiring.

![Fritzing Diagram](fritz_Button_LED_bb.png "Fritzing Diagram with LED and Button")

## Task: Developing a C program for a blinking LED (Week 3)}

The main task of this lab is to write a C program to read input
from a button and let the LED blink, whenever you press the
button. The button should be connected via the breadboard to **pin 16**
of the RPi2 (see the Fritzing diagram above for the complete wiring needed in this lab).

The C code for controlling a button is discussed in[Tutorial 3](http://www.macs.hw.ac.uk/~hwloidl/Courses/F28HS/slides24_SysPrg_Tut3.pdf).
Start from the sample code discussed in class:
[tut_button.c}](http://www.macs.hw.ac.uk/~hwloidl/Courses/F28HS/srcs/tut_button.c),
which implements a button-controlled LED and adjust it to use the pins specified above.

*Note,* that this sample source has a ``bug'' in that the LED is on at the start and
is turned off by pressing the button. The desired behaviour should be the inverse: the
LED should be off at the start and turned on when pressing a button. It's suggested that
you first make the small change to the code, to achieve this behaviour, and then move on
to the main task, of a button-controlled LED, with pin usage discussed above.

