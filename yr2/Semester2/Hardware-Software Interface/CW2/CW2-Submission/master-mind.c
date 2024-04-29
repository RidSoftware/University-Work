/*
 * MasterMind implementation: template; see comments below on which parts need to be completed
 * CW spec: https://www.macs.hw.ac.uk/~hwloidl/Courses/F28HS/F28HS_CW2_2022.pdf
 * This repo: https://gitlab-student.macs.hw.ac.uk/f28hs-2021-22/f28hs-2021-22-staff/f28hs-2021-22-cwk2-sys

 * Compile: 
 gcc -o master-mind master-mind.c
 * Run:     
 sudo ./master-mind

 ***********************************************************************
 * The Low-level interface to LED, button, and LCD is based on:
 * wiringPi libraries by
 * Copyright (c) 2012-2013 Gordon Henderson.
 ***********************************************************************
 * See:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
*/

/* ======================================================= */
/* SECTION: includes                                       */
/* ------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

#include <unistd.h>
#include <string.h>
#include <time.h>

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ioctl.h>

/* --------------------------------------------------------------------------- */
/* Config settings */
/* you can use CPP flags to e.g. print extra debugging messages */
/* or switch between different versions of the code e.g. digitalWrite() in Assembler */
#define DEBUG
#undef ASM_CODE

// =======================================================
// Tunables
// PINs (based on BCM numbering)
// For wiring see CW spec: https://www.macs.hw.ac.uk/~hwloidl/Courses/F28HS/F28HS_CW2_2022.pdf
// GPIO pin for green LED
#define DATALED 13
// GPIO pin for red LED
#define CTRLLED 5
// GPIO pin for button
#define BUTTON 19
// =======================================================
// delay for loop iterations (mainly), in ms
// in mili-seconds: 0.2s
#define DELAY   200
// in micro-seconds: 3s
#define TIMEOUT 3000000
// =======================================================
// APP constants   ---------------------------------
// number of colours and length of the sequence
#define COLS 3
#define SEQL 3
// =======================================================

// generic constants

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


// =======================================================
// Wiring (see inlined initialisation routine)

#define STRB_PIN 24
#define RS_PIN   25
#define DATA0_PIN 23
#define DATA1_PIN 10
#define DATA2_PIN 27
#define DATA3_PIN 22

/* ======================================================= */
/* SECTION: constants and prototypes                       */
/* ------------------------------------------------------- */

// =======================================================
// char data for the CGRAM, i.e. defining new characters for the display

static unsigned char newChar [8] = 
{
  0b11111,
  0b10001,
  0b10001,
  0b10101,
  0b11111,
  0b10001,
  0b10001,
  0b11111,
} ;

/* Constants */

static const int colors = COLS;
static const int seqlen = SEQL;

static char* color_names[] = { "red", "green", "blue" };

static int* theSeq = NULL;

static int *seq1, *seq2, *cpy1, *cpy2;

/* --------------------------------------------------------------------------- */

// data structure holding data on the representation of the LCD
struct lcdDataStruct
{
  int bits, rows, cols ;
  int rsPin, strbPin ;
  int dataPins [8] ;
  int cx, cy ;
} ;

static int lcdControl ;

/* ***************************************************************************** */
/* INLINED fcts from wiringPi/devLib/lcd.c: */
// HD44780U Commands (see Fig 11, p28 of the Hitachi HD44780U datasheet)

#define	LCD_CLEAR	0x01
#define	LCD_HOME	0x02
#define	LCD_ENTRY	0x04
#define	LCD_CTRL	0x08
#define	LCD_CDSHIFT	0x10
#define	LCD_FUNC	0x20
#define	LCD_CGRAM	0x40
#define	LCD_DGRAM	0x80

// Bits in the entry register

#define	LCD_ENTRY_SH		0x01
#define	LCD_ENTRY_ID		0x02

// Bits in the control register

#define	LCD_BLINK_CTRL		0x01
#define	LCD_CURSOR_CTRL		0x02
#define	LCD_DISPLAY_CTRL	0x04

// Bits in the function register

#define	LCD_FUNC_F	0x04
#define	LCD_FUNC_N	0x08
#define	LCD_FUNC_DL	0x10

#define	LCD_CDSHIFT_RL	0x04

// Mask for the bottom 64 pins which belong to the Raspberry Pi
//	The others are available for the other devices

#define	PI_GPIO_MASK	(0xFFFFFFC0)

static unsigned int gpiobase ;
static uint32_t *gpio ;

static int timed_out = 0;

int button_press_count = 0; //variable for tracking num of imes a button has been pressed
int timer_running = 0;      //variable 1 or 0 forstate of timer

/* ------------------------------------------------------- */
// misc prototypes

int failure (int fatal, const char *message, ...);
void waitForEnter (void);
void waitForButton (uint32_t *gpio, int button);

/* ======================================================= */
/* SECTION: hardware interface (LED, button, LCD display)  */
/* ------------------------------------------------------- */
/* low-level interface to the hardware */


/* send a @value@ (LOW or HIGH) on pin number @pin@; @gpio@ is the mmaped GPIO base address */
void digitalWrite (uint32_t *gpio, int pin, int value){
    
    
    if (value == 1) {
      *(gpio + 7) = 1 << (pin & 31) ;   //sends a high value to the desired pin if value passed == 1
    } else if (value == 0) {
      *(gpio + 10) = 1 << (pin & 31) ;  //sends a low value to the desired pin if value passed == 0
    } 

  /* Assembly version compiles but does not fully run due to Segmentation Fault
  //printf("gpio: %d, pin: %d, value: %d\n\n", gpio, pin, value);
  
  if (value == 1) {
      __asm__ volatile (
          "\tLDR R3, [%[gpio], %[offset1]] \n"    // Load gpio + 7 address into r3
          "\tMOV R2, %[pin] \n"            // Load the pin value into r2
          "\tAND R2, R2, #31 \n"           // Mask the pin value to 31
          "\tMOV R4, #1 \n"                // Load the value 1 into r4
          "\tLSL R4, R4, R2\n"             // Sets the pin's bit to 1
          "\tSTR R4, [R3] \n"              // Store the value of r4 in gpio  7
          :                                     // Outputs
          : [gpio] "r" (gpio),[pin] "r" (pin), [offset1] "i" (28)  // Inputs
          : "r2","r3","r4","memory"             // Clobbered regs
      );
      
  } 
  else if (value == 0) {
      __asm__ volatile (
          "\tLDR R3, [%[gpio], %[offset2]] \n"     // Load gpio + 10 address into r3
          "\tMOV R2, %[pin] \n"             // Load pin value into r2
          "\tAND R2, R2, #31 \n"            // Mask the pin value to 31
          "\tMOV R4, #1 \n"                 // Load the value 1 into r4
          //"\tLSL R4, R4, R2\n"              // Inverts the pin's bit
          "\tMVN R4, R4\n"
          "\tBIC R4, R3, R4 \n"
          "\tSTR R4, [R3] \n"               // Store the value of r4 in gpio  7
          : 
          : [gpio] "r" (gpio),[pin] "r" (pin), [offset2] "i" (40) 
          : "r2","r3","r4","memory"
      );
  }*/
  
}

/* set the @mode@ of a GPIO @pin@ to INPUT or OUTPUT; @gpio@ is the mmaped GPIO base address */
void pinMode(uint32_t *gpio, int pin, int mode){
  
  int fsel = 0;             //
  while ((pin-10) > 0)      //  calculates the fsel and shift values for the gpio pin
  {                         //    
    pin -= 10;              //
    fsel++;                 //
  }                         //
  int shift = pin * 3;      // 


  if (mode == 1) {
    *(gpio + fsel) = (*(gpio + fsel) & ~(7 << shift)) | (1 << shift); //sets the i/o mode of the pin to output if mode passed == 1
  } else if (mode == 0) {
    *(gpio + fsel) = (*(gpio + fsel) & ~(7 << shift)) | (1 << shift); //sets the i/o mode of the pin to input if mode passed == 0
  } 

  /* Assembly version compiles but does not fully work
  __asm__ volatile (
    
    "\tMOV %[fsel1], #0 \n"                   // Sets fsel to 0
    "\tloop: \n"                              // Start the loop
    "\tSUB %[pin1], %[pin1], #10 \n"          // Decrement pin by 10
    "\tADD %[fsel1], %[fsel1], #1 \n"         // Increment fsel by 1
    "\tCMP %[pin1], #10 \n"                   // Compare pin with 10
    "\tBGT loop \n"                           // Branch if compare ans is greater than 10
    "\tMOV %[shift1], %[shift1], LSL #1 \n"   // Calculate the shift value by doing (pin*3)
    "\tADD %[shift1], %[shift1], %[pin1]"
    : [fsel] "+r" (fsel), [pin] "+r" (pin)                        // asm outputs
    : [pin1] "r" (pin), [fsel1] "r" (fsel), [shift1] "r" (shift)  // asm inputs
    :                                                             // No clobbered regs
  );
  
  // Separated the sections for better readability and easier maintainability
  // Top section does the while loop and shift calculation
  // Bottom section handles the mode if elif decision
  
  __asm__ volatile (
  
  "\tMOV R2, %[gpio] \n"               // Load gpio into r2
  // Calculates the address by adding the offset, left shifted by 2 (same as multiplying by 4), to the base address
  "\tLDR R3, [R2, %[fsel], LSL #2] \n" // And loads it into r3
  "\tMOV R4, #7 \n"                       // Load the value 7 into r4
  "\tMOV R5, #1 \n"                       // Load the value 1 into r5
  "\tLSL R4, R4, %[shift] \n"          // Left shifts r4 by the value in shift
  "\tMVN R4, R4 \n"                    // Uses a binary NOT to invert all the bits in r4
  "\tAND R3, R3, R4 \n"                // Clears the pins binary bits in r3
  "\tLSL R5, R5, %[shift] \n"          // Left shift R5 by the shift value
  "\tORR R3, R3, R5 \n"                // Uses binary OR to set the r3 to 1
  "\tSTR R3, [R2, %[fsel], LSL #2] \n" // Stores the mode value in the calculated address used before
  :
  : [gpio] "r" (gpio), [fsel] "r" (fsel), [shift] "r" (shift) // asm inputs
  : "r2","r3","r4","r5","cc"
  );
  */

}

/* send a @value@ (LOW or HIGH) on pin number @pin@; @gpio@ is the mmaped GPIO base address */
/* can use digitalWrite(), depending on your implementation */
void writeLED(uint32_t *gpio, int led, int value){

  digitalWrite (gpio, led, value);  //simply calls digitalWrite to write the desired value to the pin of the LED

}

/* read a @value@ (LOW or HIGH) from pin number @pin@ (a button device); @gpio@ is the mmaped GPIO base address */
int readButton(uint32_t *gpio, int button) {

  if ((*(gpio + 13) & (1 << (button & 31))) != 0) {   //returns the value of the buttons pin
    return HIGH;
  } else {
    return LOW;
  }

  /* Assembly compiles but runs into error
  uint32_t result;
  __asm__ volatile (
    
    "\tLDR R2, [%[gpio], #52] \n"   // Loads gpio + 13 into r2
    "\tAND R3, %[button], #31 \n"   // Mask the button value to 31
    "\tLDR R4, [R2] \n"             // Load the value in r2 into r4
    "\tMOV R5, #1 \n"               // Load the value 1 into r5
    "\tLSL R5, R5, R3 \n"           // Shift r5 left by the value in r3
    "\tAND %[result], R4, R5 \n"    // Performs a binary AND between the value in r4 and r5, storing the answer in result
    : [result] "=r" (result)                    // Asm outputs
    : [gpio] "r" (gpio), [button] "r" (button)  // Asm inputs
    : "r2","r3","r4","r5","cc"                  // Clobbered regs
  );
  
  return ( (result != 0) ? HIGH : LOW ); //Depending on result's value, returns high or low
  */

}

/* wait for a button input on pin number @button@; @gpio@ is the mmaped GPIO base address */
/* can use readButton(), depending on your implementation */
void waitForButton (uint32_t *gpio, int button) {
	//this interacts with the timer via the timer_running global variable

  while(1) {
    if (readButton(gpio, button) == 1) {
      button_press_count++;     //increments counter when value red from buttons pin is 1
      fprintf(stdout, "button presses: %d\n", button_press_count);
      delay(DELAY);             //delays the loop so it doesnt recount the same button press
    }

    if(!timer_running){break;}    //  breaks the loop once the timer has complete
    delay(10);  // minor delay between button checks
  }

}

/* ======================================================= */
/* SECTION: game logic                                     */
/* ------------------------------------------------------- */
/* AUX fcts of the game logic */

/* initialise the secret sequence; by default it should be a random sequence */
void initSeq() {

  srand(time(NULL));    //  creates a time based seed for the random number
  
  *seq1 = (int *)malloc(sizeof(int) * seqlen);    //  allocates space for the sequence
    if (seq1 == NULL) {   //  catches err when allocating memory
        fprintf(stderr, "memory allocation for matches failed\n");
      }

  for (int i = 0; i < seqlen; i++) {
    *(seq1 + i) = rand() % colors + 1;  //  generates and assigns a rand number within the range of colors THEN assign to the seq[i]
  }
  
}

/* display the sequence on the terminal window, using the format from the sample run in the spec */
void showSeq(int *seq) {

  fprintf(stdout, "Secret: %d %d %d\n", *seq, *(seq + 1), *(seq + 2));  //  uses pointer arithmetic to access elements in the sequence

}

#define NAN1 8
#define NAN2 9


 
int countMatches(int *seq1, int *seq2) {
  
  int *matches = (int *) malloc(2 * sizeof(int)); //  allocates memory for the matches
    if (matches == NULL) {
      fprintf(stderr, "Error - Memory allocation for matches failed\n");
    }

  for (int exc=0; exc<seqlen; exc++){
    // Calculates Exact Matches
    if (seq1[exc] == seq2[exc]) {
      matches[0]++;
    }
    // Calculates Total Matches
    if (seq1[exc]==seq2[0] || seq1[exc]==seq2[1] || seq1[exc]==seq2[2]) {
      matches[1]++;
    }
  }

  // Makes sure Total matches isnt counting some twice
  matches[1] = matches[1]-matches[0];

  return matches; //  returns matches encoded matches[0]==exact, matches[1]==approx
  
}


/* show the results from calling countMatches on seq1 and seq1 */
void showMatches(int /* or int* */ code, /* only for debugging */ int *seq1, int *seq2) {

  int *matches = countMatches(seq1, seq2);    //  creates a pointer to the matches

  fprintf(stdout, "%d %d\n", matches[0], matches[1]);

}

/* parse an integer value as a list of digits, and put them into @seq@ */
/* needed for processing command-line with options -s or -u            */
void readSeq(int *seq, int val) {
  //saves the sequesnce to the seq passed

  while (val-100 > 0)   //  the first number in the int is calculated
  {
    val -= 100;
    seq[0]++;
  }

  while (val-10 > 0)    //  the second number in the int is calculated
  {
    val -= 10;
    seq[1]++;
  }
  seq[2] = val;         //  the remaining value is the single digit value at the end

}

/* read a guess sequence fron stdin and store the values in arr */
/* only needed for testing the game logic, without button input */
int readNum(int max) {
  //never used
  
}

/* ======================================================= */
/* SECTION: TIMER code                                     */
/* ------------------------------------------------------- */
/* TIMER code */

/* timestamps needed to implement a time-out mechanism */
static uint64_t startT, stopT;


/* you may need this function in timer_handler() below  */
/* use the libc fct gettimeofday() to implement it      */
uint64_t timeInMicroseconds(){

  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  return (uint64_t)currentTime.tv_sec * 1000000 + (uint64_t)currentTime.tv_usec;
  
  
}

/* this should be the callback, triggered via an interval timer, */
/* that is set-up through a call to sigaction() in the main fct. */
void timer_handler (int signum) {

  /* Reset the timer */
  struct itimerval it_val;
  it_val.it_value.tv_sec = 0;
  it_val.it_value.tv_usec = 0;
  it_val.it_interval.tv_sec = 0;  // Do not repeat
  it_val.it_interval.tv_usec = 0;
  
  if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
    fprintf(stderr, "setitimer \n");
    return;
  }

  
  fprintf(stdout, "3s timer complete\n");
  timer_running=0;      //   timer state tracker updated
}


/* initialise time-stamps, setup an interval timer, and install the timer_handler callback */
void initITimer(uint64_t timeout){

  struct itimerval it_val;  //  declares the timervalue
  
  //  Get the start time
  startT = timeInMicroseconds();
  
  //  Set up the timer handler
  struct sigaction sa;
  sa.sa_handler = timer_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  if (sigaction(SIGALRM, &sa, NULL) == -1) {
    fprintf(stderr, "sigaction \n");
    return;
  }
  
  //  Set up the interval timer
  it_val.it_value.tv_sec = timeout / 1000000;
  it_val.it_value.tv_usec = timeout % 1000000;

  if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
    fprintf(stderr, "setitimer \n");
    return;
  }
    timer_running=1;    //   timer state tracker updated
}

/* ======================================================= */
/* SECTION: Aux function                                   */
/* ------------------------------------------------------- */
/* misc aux functions */

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

/*
 * waitForEnter:
 *********************************************************************************
 */

void waitForEnter (void)
{
  printf ("Press ENTER to continue: ") ;
  (void)fgetc (stdin) ;
}

/*
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

/* From wiringPi code; comment by Gordon Henderson
 * delayMicroseconds:
 *	This is somewhat intersting. It seems that on the Pi, a single call
 *	to nanosleep takes some 80 to 130 microseconds anyway, so while
 *	obeying the standards (may take longer), it's not always what we
 *	want!
 *
 *	So what I'll do now is if the delay is less than 100uS we'll do it
 *	in a hard loop, watching a built-in counter on the ARM chip. This is
 *	somewhat sub-optimal in that it uses 100% CPU, something not an issue
 *	in a microcontroller, but under a multi-tasking, multi-user OS, it's
 *	wastefull, however we've no real choice )-:
 *
 *      Plan B: It seems all might not be well with that plan, so changing it
 *      to use gettimeofday () and poll on that instead...
 *********************************************************************************
 */

void delayMicroseconds (unsigned int howLong)
{
  struct timespec sleeper ;
  unsigned int uSecs = howLong % 1000000 ;
  unsigned int wSecs = howLong / 1000000 ;

  /**/ if (howLong ==   0)
    return ;
#if 0
  else if (howLong  < 100)
    delayMicrosecondsHard (howLong) ;
#endif
  else
  {
    sleeper.tv_sec  = wSecs ;
    sleeper.tv_nsec = (long)(uSecs * 1000L) ;
    nanosleep (&sleeper, NULL) ;
  }
}

/* ======================================================= */
/* SECTION: LCD functions                                  */
/* ------------------------------------------------------- */
/* medium-level interface functions (all in C) */

/* from wiringPi:
 * strobe:
 *	Toggle the strobe (Really the "E") pin to the device.
 *	According to the docs, data is latched on the falling edge.
 *********************************************************************************
 */

void strobe (const struct lcdDataStruct *lcd)
{

  // Note timing changes for new version of delayMicroseconds ()
  digitalWrite (gpio, lcd->strbPin, 1) ; delayMicroseconds (50) ;
  digitalWrite (gpio, lcd->strbPin, 0) ; delayMicroseconds (50) ;
}

/*
 * sentDataCmd:
 *	Send an data or command byte to the display.
 *********************************************************************************
 */

void sendDataCmd (const struct lcdDataStruct *lcd, unsigned char data)
{
  register unsigned char myData = data ;
  unsigned char          i, d4 ;

  if (lcd->bits == 4)
  {
    d4 = (myData >> 4) & 0x0F;
    for (i = 0 ; i < 4 ; ++i)
    {
      digitalWrite (gpio, lcd->dataPins [i], (d4 & 1)) ;
      d4 >>= 1 ;
    }
    strobe (lcd) ;

    d4 = myData & 0x0F ;
    for (i = 0 ; i < 4 ; ++i)
    {
      digitalWrite (gpio, lcd->dataPins [i], (d4 & 1)) ;
      d4 >>= 1 ;
    }
  }
  else
  {
    for (i = 0 ; i < 8 ; ++i)
    {
      digitalWrite (gpio, lcd->dataPins [i], (myData & 1)) ;
      myData >>= 1 ;
    }
  }
  strobe (lcd) ;
}

/*
 * lcdPutCommand:
 *	Send a command byte to the display
 *********************************************************************************
 */

void lcdPutCommand (const struct lcdDataStruct *lcd, unsigned char command)
{
#ifdef DEBUG
  fprintf(stderr, "lcdPutCommand: digitalWrite(%d,%d) and sendDataCmd(%d,%d)\n", lcd->rsPin,   0, lcd, command);
#endif
  digitalWrite (gpio, lcd->rsPin,   0) ;
  sendDataCmd  (lcd, command) ;
  delay (2) ;
}

void lcdPut4Command (const struct lcdDataStruct *lcd, unsigned char command)
{
  register unsigned char myCommand = command ;
  register unsigned char i ;

  digitalWrite (gpio, lcd->rsPin,   0) ;

  for (i = 0 ; i < 4 ; ++i)
  {
    digitalWrite (gpio, lcd->dataPins [i], (myCommand & 1)) ;
    myCommand >>= 1 ;
  }
  strobe (lcd) ;
}

/*
 * lcdHome: lcdClear:
 *	Home the cursor or clear the screen.
 *********************************************************************************
 */

void lcdHome (struct lcdDataStruct *lcd)
{
#ifdef DEBUG
  fprintf(stderr, "lcdHome: lcdPutCommand(%d,%d)\n", lcd, LCD_HOME);
#endif
  lcdPutCommand (lcd, LCD_HOME) ;
  lcd->cx = lcd->cy = 0 ;
  delay (5) ;
}

void lcdClear (struct lcdDataStruct *lcd)
{
#ifdef DEBUG
  fprintf(stderr, "lcdClear: lcdPutCommand(%d,%d) and lcdPutCommand(%d,%d)\n", lcd, LCD_CLEAR, lcd, LCD_HOME);
#endif
  lcdPutCommand (lcd, LCD_CLEAR) ;
  lcdPutCommand (lcd, LCD_HOME) ;
  lcd->cx = lcd->cy = 0 ;
  delay (5) ;
}

/*
 * lcdPosition:
 *	Update the position of the cursor on the display.
 *	Ignore invalid locations.
 *********************************************************************************
 */

void lcdPosition (struct lcdDataStruct *lcd, int x, int y)
{
  // struct lcdDataStruct *lcd = lcds [fd] ;

  if ((x > lcd->cols) || (x < 0))
    return ;
  if ((y > lcd->rows) || (y < 0))
    return ;

  lcdPutCommand (lcd, x + (LCD_DGRAM | (y>0 ? 0x40 : 0x00)  /* rowOff [y] */  )) ;

  lcd->cx = x ;
  lcd->cy = y ;
}



/*
 * lcdDisplay: lcdCursor: lcdCursorBlink:
 *	Turn the display, cursor, cursor blinking on/off
 *********************************************************************************
 */

void lcdDisplay (struct lcdDataStruct *lcd, int state)
{
  if (state)
    lcdControl |=  LCD_DISPLAY_CTRL ;
  else
    lcdControl &= ~LCD_DISPLAY_CTRL ;

  lcdPutCommand (lcd, LCD_CTRL | lcdControl) ; 
}

void lcdCursor (struct lcdDataStruct *lcd, int state)
{
  if (state)
    lcdControl |=  LCD_CURSOR_CTRL ;
  else
    lcdControl &= ~LCD_CURSOR_CTRL ;

  lcdPutCommand (lcd, LCD_CTRL | lcdControl) ; 
}

void lcdCursorBlink (struct lcdDataStruct *lcd, int state)
{
  if (state)
    lcdControl |=  LCD_BLINK_CTRL ;
  else
    lcdControl &= ~LCD_BLINK_CTRL ;

  lcdPutCommand (lcd, LCD_CTRL | lcdControl) ; 
}

/*
 * lcdPutchar:
 *	Send a data byte to be displayed on the display. We implement a very
 *	simple terminal here - with line wrapping, but no scrolling. Yet.
 *********************************************************************************
 */

void lcdPutchar (struct lcdDataStruct *lcd, unsigned char data)
{
  digitalWrite (gpio, lcd->rsPin, 1) ;
  sendDataCmd  (lcd, data) ;

  if (++lcd->cx == lcd->cols)
  {
    lcd->cx = 0 ;
    if (++lcd->cy == lcd->rows)
      lcd->cy = 0 ;
    
    // TODO: inline computation of address and eliminate rowOff
    lcdPutCommand (lcd, lcd->cx + (LCD_DGRAM | (lcd->cy>0 ? 0x40 : 0x00)   /* rowOff [lcd->cy] */  )) ;
  }
}


/*
 * lcdPuts:
 *	Send a string to be displayed on the display
 *********************************************************************************
 */

void lcdPuts (struct lcdDataStruct *lcd, const char *string)
{
  while (*string)
    lcdPutchar (lcd, *string++) ;
}

/* ======================================================= */
/* SECTION: aux functions for game logic                   */
/* ------------------------------------------------------- */

/* ********************************************************** */
/* COMPLETE the code for all of the functions in this SECTION */
/* Implement these as C functions in this file                */
/* ********************************************************** */

/* --------------------------------------------------------------------------- */
/* interface on top of the low-level pin I/O code */

/* blink the led on pin @led@, @c@ times */
void blinkN(uint32_t *gpio, int led, int c) { 

  pinMode(gpio, led, c);
  for (int i=0; i<c; i++) {   //  writes the value in the led pin on and off with a small delay inbetween
      digitalWrite(gpio, led, HIGH);
      delay(500);
      digitalWrite(gpio, led, LOW);
      delay(500);
  }
  
}

/* ======================================================= */
/* SECTION: main fct                                       */
/* ------------------------------------------------------- */

int main (int argc, char *argv[])
{ // this is just a suggestion of some variable that you may want to use
  struct lcdDataStruct *lcd ;
  int bits, rows, cols ;
  unsigned char func ;

  int found = 0, attempts = 0, i, j, code;
  int c, d, buttonPressed, rel, foo;
  int *attSeq;

  int fSel, shift, pin,  clrOff, setOff, off, res;
  int fd ;



  // variables for command-line processing
  char str_in[20], str[20] = "some text";
  int verbose = 0, debug = 0, help = 0, opt_m = 0, opt_n = 0, opt_s = 0, unit_test = 0, res_matches = 0;
  
  // -------------------------------------------------------
  // process command-line arguments

  // see: man 3 getopt for docu and an example of command line parsing
  { // see the CW spec for the intended meaning of these options
    int opt;
    while ((opt = getopt(argc, argv, "hvdus:")) != -1) {
      switch (opt) {
      case 'v':
	verbose = 1;
	break;
      case 'h':
	help = 1;
	break;
      case 'd':
	debug = 1;
	break;
      case 'u':
	unit_test = 1;
	break;
      case 's':
	opt_s = atoi(optarg); 
	break;
      default: /* '?' */
	fprintf(stderr, "Usage: %s [-h] [-v] [-d] [-u <seq1> <seq2>] [-s <secret seq>]  \n", argv[0]);
	exit(EXIT_FAILURE);
      }
    }
  }

  if (help) {
    fprintf(stderr, "MasterMind program, running on a Raspberry Pi, with connected LED, button and LCD display\n"); 
    fprintf(stderr, "Use the button for input of numbers. The LCD display will show the matches with the secret sequence.\n"); 
    fprintf(stderr, "For full specification of the program see: https://www.macs.hw.ac.uk/~hwloidl/Courses/F28HS/F28HS_CW2_2022.pdf\n"); 
    fprintf(stderr, "Usage: %s [-h] [-v] [-d] [-u <seq1> <seq2>] [-s <secret seq>]  \n", argv[0]);
    exit(EXIT_SUCCESS);
  }
  
  if (unit_test && optind >= argc-1) {
    fprintf(stderr, "Expected 2 arguments after option -u\n");
    exit(EXIT_FAILURE);
  }

  if (verbose && unit_test) {
    printf("1st argument = %s\n", argv[optind]);
    printf("2nd argument = %s\n", argv[optind+1]);
  }

  if (verbose) {
    fprintf(stdout, "Settings for running the program\n");
    fprintf(stdout, "Verbose is %s\n", (verbose ? "ON" : "OFF"));
    fprintf(stdout, "Debug is %s\n", (debug ? "ON" : "OFF"));
    fprintf(stdout, "Unittest is %s\n", (unit_test ? "ON" : "OFF"));
    if (opt_s)  fprintf(stdout, "Secret sequence set to %d\n", opt_s);
  }

  seq1 = (int*)malloc(seqlen*sizeof(int));
  seq2 = (int*)malloc(seqlen*sizeof(int));
  cpy1 = (int*)malloc(seqlen*sizeof(int));
  cpy2 = (int*)malloc(seqlen*sizeof(int));

  // check for -u option, and if so run a unit test on the matching function
  if (unit_test && argc > optind+1) { // more arguments to process; only needed with -u 
    strcpy(str_in, argv[optind]);
    opt_m = atoi(str_in);
    strcpy(str_in, argv[optind+1]);
    opt_n = atoi(str_in);
    // CALL a test-matches function; see testm.c for an example implementation
    readSeq(seq1, opt_m); // turn the integer number into a sequence of numbers
    readSeq(seq2, opt_n); // turn the integer number into a sequence of numbers
    if (verbose)
      fprintf(stdout, "Testing matches function with sequences %d and %d\n", opt_m, opt_n);
    res_matches = countMatches(seq1, seq2);
    showMatches(res_matches, seq1, seq2);
    exit(EXIT_SUCCESS);
  } else {
    /* nothing to do here; just continue with the rest of the main fct */
  }

  if (opt_s) { // if -s option is given, use the sequence as secret sequence
    if (seq1==NULL)
      seq1 = (int*)malloc(seqlen*sizeof(int));
    readSeq(seq1, opt_s);
    if (verbose) {
      fprintf(stderr, "Running program with secret sequence:\n");
      showSeq(seq1);
    }
  }
  
  // -------------------------------------------------------
  // LCD constants, hard-coded: 16x2 display, using a 4-bit connection
  bits = 4; 
  cols = 16; 
  rows = 2; 
  // -------------------------------------------------------

  printf ("Raspberry Pi LCD driver, for a %dx%d display (%d-bit wiring) \n", cols, rows, bits) ;

  if (geteuid () != 0)
    fprintf (stderr, "setup: Must be root. (Did you forget sudo?)\n") ;



  
  
  // -----------------------------------------------------------------------------
  // constants for RPi2
  gpiobase = 0x3F200000 ;

  // -----------------------------------------------------------------------------
  // memory mapping 
  // Open the master /dev/memory device

  if ((fd = open ("/dev/mem", O_RDWR | O_SYNC | O_CLOEXEC) ) < 0)
    return failure (FALSE, "setup: Unable to open /dev/mem: %s\n", strerror (errno)) ;

  // GPIO:
  gpio = (uint32_t *)mmap(0, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, gpiobase) ;
  if ((int32_t)gpio == -1)
    return failure (FALSE, "setup: mmap (GPIO) failed: %s\n", strerror (errno)) ;

  // -------------------------------------------------------
  // Configuration of LED and BUTTON

    //sets the pinmodes for use
  pinMode(gpio, DATALED, OUTPUT);
  pinMode(gpio, CTRLLED, OUTPUT);
  pinMode(gpio, BUTTON, INPUT);
  
  
  // -------------------------------------------------------
  // INLINED version of lcdInit (can only deal with one LCD attached to the RPi):
  // you can use this code as-is, but you need to implement digitalWrite() and
  // pinMode() which are called from this code
  // Create a new LCD:
  lcd = (struct lcdDataStruct *)malloc (sizeof (struct lcdDataStruct)) ;
  if (lcd == NULL)
    return -1 ;

  // hard-wired GPIO pins
  lcd->rsPin   = RS_PIN ;
  lcd->strbPin = STRB_PIN ;
  lcd->bits    = 4 ;
  lcd->rows    = rows ;  // # of rows on the display
  lcd->cols    = cols ;  // # of cols on the display
  lcd->cx      = 0 ;     // x-pos of cursor
  lcd->cy      = 0 ;     // y-pos of curosr


  lcd->dataPins [0] = DATA0_PIN ;
  lcd->dataPins [1] = DATA1_PIN ;
  lcd->dataPins [2] = DATA2_PIN ;
  lcd->dataPins [3] = DATA3_PIN ;
  // lcd->dataPins [4] = d4 ;
  // lcd->dataPins [5] = d5 ;
  // lcd->dataPins [6] = d6 ;
  // lcd->dataPins [7] = d7 ;

  // lcds [lcdFd] = lcd ;

  digitalWrite (gpio, lcd->rsPin,   0) ; pinMode (gpio, lcd->rsPin,   OUTPUT) ;
  digitalWrite (gpio, lcd->strbPin, 0) ; pinMode (gpio, lcd->strbPin, OUTPUT) ;

  for (i = 0 ; i < bits ; ++i)
  {
    digitalWrite (gpio, lcd->dataPins [i], 0) ;
    pinMode      (gpio, lcd->dataPins [i], OUTPUT) ;
  }
  delay (35) ; // mS

// Gordon Henderson's explanation of this part of the init code (from wiringPi):
// 4-bit mode?
//	OK. This is a PIG and it's not at all obvious from the documentation I had,
//	so I guess some others have worked through either with better documentation
//	or more trial and error... Anyway here goes:
//
//	It seems that the controller needs to see the FUNC command at least 3 times
//	consecutively - in 8-bit mode. If you're only using 8-bit mode, then it appears
//	that you can get away with one func-set, however I'd not rely on it...
//
//	So to set 4-bit mode, you need to send the commands one nibble at a time,
//	the same three times, but send the command to set it into 8-bit mode those
//	three times, then send a final 4th command to set it into 4-bit mode, and only
//	then can you flip the switch for the rest of the library to work in 4-bit
//	mode which sends the commands as 2 x 4-bit values.

  if (bits == 4)
  {
    func = LCD_FUNC | LCD_FUNC_DL ;			// Set 8-bit mode 3 times
    lcdPut4Command (lcd, func >> 4) ; delay (35) ;
    lcdPut4Command (lcd, func >> 4) ; delay (35) ;
    lcdPut4Command (lcd, func >> 4) ; delay (35) ;
    func = LCD_FUNC ;					// 4th set: 4-bit mode
    lcdPut4Command (lcd, func >> 4) ; delay (35) ;
    lcd->bits = 4 ;
  }
  else
  {
    failure(TRUE, "setup: only 4-bit connection supported\n");
    func = LCD_FUNC | LCD_FUNC_DL ;
    lcdPutCommand  (lcd, func     ) ; delay (35) ;
    lcdPutCommand  (lcd, func     ) ; delay (35) ;
    lcdPutCommand  (lcd, func     ) ; delay (35) ;
  }


  if (lcd->rows > 1)
  {
    func |= LCD_FUNC_N ;
    lcdPutCommand (lcd, func) ; delay (35) ;
  }

  // Rest of the initialisation sequence
  lcdDisplay     (lcd, TRUE) ;
  lcdCursor      (lcd, FALSE) ;
  lcdCursorBlink (lcd, FALSE) ;
  lcdClear       (lcd) ;

  lcdPutCommand (lcd, LCD_ENTRY   | LCD_ENTRY_ID) ;    // set entry mode to increment address counter after write
  lcdPutCommand (lcd, LCD_CDSHIFT | LCD_CDSHIFT_RL) ;  // set display shift to right-to-left

  // END lcdInit ------
  // -----------------------------------------------------------------------------
  // Start of game
  fprintf(stderr,"Printing welcome message on the LCD display ...\n");
  /* ***  COMPLETE the code here  ***  */

  /* initialise the secret sequence */
  if (!opt_s)
    initSeq();
  if (debug)
    showSeq(seq1);

  // optionally one of these 2 calls:
  // waitForEnter () ; 
  // waitForButton (gpio, pinButton) ;

  // -----------------------------------------------------------------------------
  // +++++ main loop
  while (!found) {
    attempts++;
    

//LOOP FOR SEQ INPUT
for (int i=0; i<SEQL; i++){

//IN: waits for the button input for 3 seconds
      printf("waiting for input...\n");
      initITimer(TIMEOUT);
      waitForButton(gpio, BUTTON);

//OUT: <RED BLINK>
      printf("input accepted\n");
      blinkN(gpio, CTRLLED, 1);

//OUT: <GREEN BLINK button_press_count>
      printf("button press count: %d\n", button_press_count);
      blinkN(gpio, DATALED, button_press_count);
      seq2[i] = button_press_count;
      button_press_count=0;
}
      // red ctrl led, blinks twice
      printf("sequence input complete\n");
      blinkN(gpio, CTRLLED, 2);
      
      
      //  calculates the matches
      int *matchArr = (int *) malloc(2 * sizeof(int));
      matchArr = countMatches(seq1, seq2);
      

      //  blinks green for no of exact
      printf("exact matches %d\n", matchArr[0]);
      blinkN(gpio, DATALED, matchArr[0]);
      
      //  blinks green for no of approx
      printf("approx matches %d\n", matchArr[1]);
      blinkN(gpio, CTRLLED, 1);
      blinkN(gpio, DATALED, matchArr[1]);
      
      //blinks red as a spacer
      printf("--ROUND COMPLETE--\n");
      blinkN(gpio, CTRLLED, 3);


  // win condition
  if (matchArr[0] == SEQL) {
    found=1;
    digitalWrite(gpio, CTRLLED, HIGH);
    blinkN(gpio, DATALED, 3);
    digitalWrite(gpio, CTRLLED, LOW);
  }

    free(matchArr);
  }//while end
  
  
  
  if (found) {
      printf("SUCCESSFUL GUESS!!!\n");  
      printf("attempts:%d\n", attempts);
  } else {
    fprintf(stdout, "Sequence not found\n");
  }

  //frees allocated memory
  free(theSeq);
  free(seq1);
  free(seq2);

  return 0;
}
