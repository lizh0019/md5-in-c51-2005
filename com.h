#ifndef __COM_H
#define __COM_H

#include "reg66x.h"
#include <stdio.h>
#include <string.h>

// Function to initialize the serial port and the UART baudrate.
extern unsigned char xdata Rec_flag;

extern void com_initialize (void); 

//putachar: write a character to SBUF or transmission buffer
extern int putachar(char c);

//putbuf: write string to SBUF or transmission buffer
extern void putbuf (char *pch); 
extern void putlenbuf (char *pch, int len); 

// Replacement routine for the standard library _getkey routine.
// The getchar and gets functions uses _getkey to read a character.
extern char GetKey (char * C); 

extern void ClearRcvBuf();

#endif

