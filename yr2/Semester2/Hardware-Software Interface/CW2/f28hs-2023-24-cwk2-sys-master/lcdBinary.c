/* ***************************************************************************** */
/* You can use this file to define the low-level hardware control fcts for       */
/* LED, button and LCD devices.                                                  */ 
/* Note that these need to be implemented in Assembler.                          */
/* You can use inline Assembler code, or use a stand-alone Assembler file.       */
/* Alternatively, you can implement all fcts directly in master-mind.c,          */  
/* using inline Assembler code there.                                            */
/* The Makefile assumes you define the functions here.                           */
/* ***************************************************************************** */


#ifndef	TRUE
#  define	TRUE	(1==1)
#  define	FALSE	(1==2)
#endif

#define	PAGE_SIZE		(4*1024)
#define	BLOCK_SIZE		(4*1024)

#define	INPUT			 0
#define	OUTPUT			 1

#define	LOW			 0
#define	HIGH			 1


// APP constants   ---------------------------------

// Wiring (see call to lcdInit in main, using BCM numbering)
// NB: this needs to match the wiring as defined in master-mind.c

#define STRB_PIN 24
#define RS_PIN   25
#define DATA0_PIN 23
#define DATA1_PIN 10
#define DATA2_PIN 27
#define DATA3_PIN 22

// -----------------------------------------------------------------------------
// includes 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <time.h>

// -----------------------------------------------------------------------------
// prototypes

int failure (int fatal, const char *message, ...);

// -----------------------------------------------------------------------------
// Functions to implement here (or directly in master-mind.c)

/* send a @value@ (LOW or HIGH) on pin number @pin@; @gpio@ is the mmaped GPIO base address */
void digitalWrite (uint32_t *gpio, int pin, int value){
    
    if (value = HIGH) {
      *(gpio + 7) = 1 << (pin & 31) ;
    } else if (value = LOW) {
      *(gpio + 10) = 1 << (pin & 31) ;
    } //space for err handling
  
}

/* set the @mode@ of a GPIO @pin@ to INPUT or OUTPUT; @gpio@ is the mmaped GPIO base address */
void pinMode(uint32_t *gpio, int pin, int mode){
  
  int fsel = 0;
  while (pin % 10 == 0)
  {
    pin = pin - 10;
    fsel++;
  }
  int shift = pin * 3;

  if (mode = OUTPUT) {
    *(gpio + fsel) = (*(gpio + fsel) & ~(7 << shift)) | (1 << shift);
  } else if (mode = INPUT) {
    *(gpio + fsel) = (*(gpio + fsel) & ~(7 << shift)) | (1 << shift);
  } //space for err handling

}

/* send a @value@ (LOW or HIGH) on pin number @pin@; @gpio@ is the mmaped GPIO base address */
/* can use digitalWrite(), depending on your implementation */
void writeLED(uint32_t *gpio, int led, int value){

  digitalWrite (gpio, led, value);

}

/* read a @value@ (LOW or HIGH) from pin number @pin@ (a button device); @gpio@ is the mmaped GPIO base address */
int readButton(uint32_t *gpio, int button) {

  if (*(gpio + 13) & (1 << (button & 31)) != 0) {
    return HIGH;
  } else {
    return LOW;
  }

}

/* wait for a button input on pin number @button@; @gpio@ is the mmaped GPIO base address */
/* can use readButton(), depending on your implementation */
void waitForButton (uint32_t *gpio, int button) {

  while(1) {
    if (readButton(gpio, button)) {
      break;
    }
    delay(1);
  }

}

/*  AUX FUNCTIONS
 * delay:
 *	Wait for some number of milliseconds
 *********************************************************************************
 */

void delay (unsigned int howLong)
{
  struct timespec sleeper, dummy ;

  sleeper.tv_sec  = (time_t)(howLong / 1000) ;
  sleeper.tv_nsec = (long)(howLong % 1000) * 1000000 ;

  nanosleep (&sleeper, &dummy) ;
}
