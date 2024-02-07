// Blinking LED, now really standalone; LED controlled from C level
// Compile: gcc  -o  t1 tut_led.c
// Run:     sudo ./t1

#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include <poll.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ioctl.h>

// =======================================================
// Tunables
// The OK/Act LED is connected to BCM_GPIO pin 47 (RPi 2)
#define ACT  47

#define GREEN 10
#define YELLOW 11
#define RED 13
// delay for blinking
#define DELAY 1000
// =======================================================

#ifndef	TRUE
#define	TRUE	(1==1)
#define	FALSE	(1==2)
#endif

#define	PAGE_SIZE		(4*1024)
#define	BLOCK_SIZE		(4*1024)

#define	INPUT			 0
#define	OUTPUT			 1

#define	LOW			 0
#define	HIGH			 1


static volatile unsigned int gpiobase ;
static volatile uint32_t *gpio ;

// -----------------------------------------------------------------------------

int failure (int fatal, const char *message, ...)
{
  va_list argp ;
  char buffer [1024] ;

  if (!fatal) //  && wiringPiReturnCodes)
    return -1 ;

  va_start (argp, message) ;
  vsnprintf (buffer, 1023, message, argp) ;
  va_end (argp) ;

  fprintf (stderr, "%s", buffer) ;
  exit (EXIT_FAILURE) ;

  return 0 ;
}

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* HaWo: tinkering starts here */
/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

int main (void)
{
  int pinACT = ACT; // ,  pinLED = LED, pinButton = BUTTON;
  int pinGREEN = GREEN, pinYELLOW = YELLOW, pinRED = RED;
  int fSel, shift, pin, clrOff, setOff;
  int   fd ;
  int   j;
  int theValue, thePin;
  unsigned int howLong = DELAY;
  uint32_t res; /* testing only */

  printf ("Raspberry Pi trafficLight LEDs %d, %d, %d\n", pinGREEN, pinYELLOW, pinRED) ;

  if (geteuid () != 0)
    fprintf (stderr, "setup: Must be root. (Did you forget sudo?)\n") ;

  // -----------------------------------------------------------------------------
  // constants for RPi2
  gpiobase = 0x3F200000 ;

  // -----------------------------------------------------------------------------
  // memory mapping 
  // Open the master /dev/memory device

  if ((fd = open ("/dev/mem", O_RDWR | O_SYNC) ) < 0)
    return failure (FALSE, "setup: Unable to open /dev/mem: %s\n", strerror (errno)) ;

  // GPIO:
  gpio = (uint32_t *)mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, gpiobase) ;
  if ((int32_t)gpio == -1)
    return failure (FALSE, "setup: mmap (GPIO) failed: %s\n", strerror (errno)) ;
  else
    fprintf(stderr, "NB: gpio = %x for gpiobase %x\n", gpio, gpiobase);

  // -----------------------------------------------------------------------------
  // setting the modes
  fprintf(stderr, "setting GREEN pin %d to %d ...\n", pinGREEN, OUTPUT);
  fSel =  1;    // GPIO 10 lives in register 1 (GPFSEL)
  shift =  0;  // GPIO 10 sits in slot 0 of register 1, thus shift by 0*3 (3 bits per pin)
  *(gpio + fSel) = (*(gpio + fSel) & ~(7 << shift)) | (1 << shift) ;  // Sets bits to one = output
  
  fprintf(stderr, "setting YELLOW pin %d to %d ...\n", pinYELLOW, OUTPUT);
  fSel =  1;    // GPIO 11 lives in register 1 (GPFSEL)
  shift =  3;  // GPIO 11 sits in slot 3 of register 1, thus shift by 1*3 (3 bits per pin)
  *(gpio + fSel) = (*(gpio + fSel) & ~(7 << shift)) | (1 << shift) ;  // Sets bits to one = output
  
    fprintf(stderr, "setting RED pin %d to %d ...\n", pinRED, OUTPUT);
  fSel =  1;    // GPIO 13 lives in register 1 (GPFSEL)
  shift =  9;  // GPIO 13 sits in slot 9 of register 1, thus shift by 3*3 (3 bits per pin)
  *(gpio + fSel) = (*(gpio + fSel) & ~(7 << shift)) | (1 << shift) ;  // Sets bits to one = output

  // -----------------------------------------------------------------------------

  // should probalby send both 7/8 & 10/11 codes for robustness
  // now, start a loop, listening to pinButton and if set pressed, set pinLED
 fprintf(stderr, "starting traffic lights ...\n");

  // setup

  *(gpio + 7) = 1 << (pinRED & 31) ; 
  *(gpio + 7) = 1 << (pinYELLOW & 31) ; 
  *(gpio + 7) = 1 << (pinGREEN & 31) ; 

  // INLINED delay 
  // !! should instanciate this once, and just call when needed !!
  {
    struct timespec sleeper, dummy ;

    // fprintf(stderr, "delaying by %d ms ...\n", howLong);
    sleeper.tv_sec  = (time_t)(howLong / 1000) ;
    sleeper.tv_nsec = (long)(howLong % 1000) * 1000000 ;

    nanosleep (&sleeper, &dummy) ;
  }

  *(gpio + 10) = 1 << (pinRED & 31) ; 
  *(gpio + 10) = 1 << (pinYELLOW & 31) ; 
  *(gpio + 10) = 1 << (pinGREEN & 31) ;   

  
  //r1 y0 g0

  *(gpio + 7) = 1 << (pinRED & 31) ; 
  *(gpio + 10) = 1 << (pinYELLOW & 31) ; 
  *(gpio + 10) = 1 << (pinGREEN & 31) ; 

  // INLINED delay
  {
    struct timespec sleeper, dummy ;

    // fprintf(stderr, "delaying by %d ms ...\n", howLong);
    sleeper.tv_sec  = (time_t)(howLong / 1000) ;
    sleeper.tv_nsec = (long)(howLong % 1000) * 1000000 ;

    nanosleep (&sleeper, &dummy) ;
  }
  
  //r1 y1 g0

  *(gpio + 7) = 1 << (pinRED & 31) ; 
  *(gpio + 7) = 1 << (pinYELLOW & 31) ; 
  *(gpio + 10) = 1 << (pinGREEN & 31) ; 

  // INLINED delay
  {
    struct timespec sleeper, dummy ;

    // fprintf(stderr, "delaying by %d ms ...\n", howLong);
    sleeper.tv_sec  = (time_t)(howLong / 1000) ;
    sleeper.tv_nsec = (long)(howLong % 1000) * 1000000 ;

    nanosleep (&sleeper, &dummy) ;
  }

  //r0 y0 g1

  *(gpio + 10) = 1 << (pinRED & 31) ; 
  *(gpio + 10) = 1 << (pinYELLOW & 31) ; 
  *(gpio + 7) = 1 << (pinGREEN & 31) ; 

  // INLINED delay
  {
    struct timespec sleeper, dummy ;

    // fprintf(stderr, "delaying by %d ms ...\n", howLong);
    sleeper.tv_sec  = (time_t)(howLong / 1000) ;
    sleeper.tv_nsec = (long)(howLong % 1000) * 1000000 ;

    nanosleep (&sleeper, &dummy) ;
  }


  //trigger for button press


  //r0 y0 g1 --still

  *(gpio + 10) = 1 << (pinRED & 31) ; 
  *(gpio + 10) = 1 << (pinYELLOW & 31) ; 
  *(gpio + 7) = 1 << (pinGREEN & 31) ; 

  // INLINED delay
  {
    struct timespec sleeper, dummy ;

    // fprintf(stderr, "delaying by %d ms ...\n", howLong);
    sleeper.tv_sec  = (time_t)(howLong / 1000) ;
    sleeper.tv_nsec = (long)(howLong % 1000) * 1000000 ;

    nanosleep (&sleeper, &dummy) ;
  }

  //r0 yblinking g0

  *(gpio + 10) = 1 << (pinRED & 31) ; 

  *(gpio + 10) = 1 << (pinGREEN & 31) ; 

  // INLINED delay
  for (j=0; j<1000; j++)
  {
    theValue = ((j % 2) == 0) ? HIGH : LOW;

    if ((pinYELLOW & 0xFFFFFFC0 /* PI_GPIO_MASK */) == 0)	// bottom 64 pins belong to the Pi	
      {
        //GPSSET0/GPCLR0 required because there are only 32 pins on rpi2, and GPSET1/GPCLR1 covers pins 32-53
	int off = (theValue == LOW) ? 10 : 7; // if the current loop value is LOW, set off to 11, else 8
        *(gpio + off) = 1 << (pinYELLOW & 31) ; // 1<<(pinGREEN&31) adds a bitmask of 1 on the pinGREEN
      }
      else
      {
        fprintf(stderr, "only supporting on-board pins\n");          
        exit(1);
       }

    // INLINED delay
    {
      struct timespec sleeper, dummy ;

      // fprintf(stderr, "delaying by %d ms ...\n", howLong);
      sleeper.tv_sec  = (time_t)(howLong / 1000) ;
      sleeper.tv_nsec = (long)(howLong % 1000) * 1000000 ;

      nanosleep (&sleeper, &dummy) ;
    }
  }

  //r1 y0 g0

  *(gpio + 7) = 1 << (pinRED & 31) ; 
  *(gpio + 10) = 1 << (pinYELLOW & 31) ; 
  *(gpio + 10) = 1 << (pinGREEN & 31) ; 

  // INLINED delay
  {
    struct timespec sleeper, dummy ;

    // fprintf(stderr, "delaying by %d ms ...\n", howLong);
    sleeper.tv_sec  = (time_t)(howLong / 1000) ;
    sleeper.tv_nsec = (long)(howLong % 1000) * 1000000 ;

    nanosleep (&sleeper, &dummy) ;
  }



//-----------------------------------------//
 /* loop unnecessary for trafic light logic
 for (j=0; j<1000; j++)
  {
    theValue = ((j % 2) == 0) ? HIGH : LOW;

    if ((pinYELLOW & 0xFFFFFFC0 ) == 0)	// bottom 64 pins belong to the Pi	
      {
        //GPSSET0/GPCLR0 required because there are only 32 pins on rpi2, and GPSET1/GPCLR1 covers pins 32-53
	  int off = (theValue == LOW) ? 10 : 7; // if the current loop value is LOW, set off to 11, else 8
        *(gpio + off) = 1 << (pinYELLOW & 31) ; // 1<<(pinGREEN&31) adds a bitmask of 1 on the pinGREEN
      }
      else
      {
        fprintf(stderr, "only supporting on-board pins\n");          
        exit(1);
       }

    // INLINED delay
    {
      struct timespec sleeper, dummy ;

      // fprintf(stderr, "delaying by %d ms ...\n", howLong);
      sleeper.tv_sec  = (time_t)(howLong / 1000) ;
      sleeper.tv_nsec = (long)(howLong % 1000) * 1000000 ;

      nanosleep (&sleeper, &dummy) ;
    }
  }
  */
 // Clean up: write LOW
 clrOff = 10; 
 *(gpio + clrOff) = 1 << (pinACT & 31) ;
 *(gpio + clrOff) = 1 << (pinRED & 31) ;
 *(gpio + clrOff) = 1 << (pinYELLOW & 31) ;
 *(gpio + clrOff) = 1 << (pinGREEN & 31) ;


 fprintf(stderr, "end main.\n");
}
