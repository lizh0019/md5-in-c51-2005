//#include <c8051sr.h>
#include "com.h"	

#define OLEN 600							// size of serial transmission buffer

int  ostart; 						// transmission buffer start index
int  oend; 						// transmission buffer end index
unsigned char xdata  outbuf[OLEN]; 			// storage for transmission buffer


#define ILEN 1024					// size of serial receiving buffer
int  istart; 				// receiving buffer start index
int  iend; 				// receiving buffer end index
unsigned char  xdata inbuf[ILEN]; 			// storage for receiving buffer

bit sendfull; 						// flag: marks transmit buffer full
bit sendactive; 					// flag: marks transmitter active


//Serial Interrupt Service Routine
static void com_isr (void) interrupt 4 using 1 
{
	char c;

	/*----- Received data interrupt. ----------------------------------------*/
	if (RI) 
	{
		c = SBUF; 	// read character
		RI = 0; 	// clear interrupt request flag
		
		inbuf[iend] = c;
		iend++;

		if(iend >= ILEN)
			iend = 0;		
	}

	/*------ Transmitted data interrupt. ------------------------------------*/
	if (TI != 0) 
	{
		
		if (ostart != oend) 
		{ 
			// if characters in buffer and
			SBUF = outbuf[ostart];//++ & (OLEN-1)]; // transmit character
			ostart++;
			if(ostart >= OLEN)
				ostart = 0;
			sendfull = 0; // clear 'sendfull' flag
		}
		else 
		{ 	
			// if all characters transmitted
			sendactive = 0; // clear 'sendactive'
		}
		TI = 0; // clear interrupt request flag
	}
}

// Function to initialize the serial port and the UART baudrate.

void com_initialize (void) 
{
	istart = 0; // empty transmit buffers
	iend = 0;
	ostart = 0; // empty transmit buffers
	oend = 0;
	sendactive = 0; // transmitter is not active
	sendfull = 0; // clear 'sendfull' flag
	
	// Configure timer 1 as a baud rate generator
	///PCON |= 0x80; // 0x80=SMOD: set serial baudrate doubler
	///TMOD |= 0x20; // put timer 1 into MODE 2
	///TH1 = 0xfa;		//0xff 115200 0xe8 4800
	///TR1 = 1; // start timer 1
    // Configure timer 2 as a baud rate generator
	//add at 04.08.12

	RCAP2H = 0xff;
	RCAP2L = 0xe2;

    T2CON  = 0x34;    

	S0CON = 0x50; // serial port MODE 1, enable serial receiver
	ES0 = 1; // enable serial interrupts
}

//putbuf: write string to SBUF or transmission buffer
void putbuf(char *pch)
{
	int len = strlen(pch);
	putlenbuf(pch, len);
}

void putlenbuf (char *pch, int len)
{
	int i;
	for(i = 0 ;i < len ; i++)
	{
		do
		{
		}while(putachar(pch[i]) == -1);
	}
}

//putachar: write a character to SBUF or transmission buffer
int putachar (char c) 
{
	int endfullflag;
	if (!sendfull) 
	{ 
		// transmit only if buffer not full
		if (!sendactive) 
		{ 
			// if transmitter not active:
			sendactive = 1; // transfer first character direct
			SBUF = c; 		// to SBUF to start transmission
		}
		else 
		{
			ES0 = 0; 						// disable serial interrupts during buffer update
			outbuf[oend] = c; //++ & (OLEN-1)] = c; 	// put char to transmission buffer
			
			endfullflag = oend + 1;
			if(endfullflag >= OLEN)
				endfullflag = 0;
			if(endfullflag == ostart)
 		    {
				sendfull = 1;
				ES0 = 1; // enable serial interrupts again
				return -1;
			}
			else 
			{
				oend++;
				if(oend >= OLEN)
					oend = 0;
					sendfull = 0;
			} // set flag if buffer is full
			
			ES0 = 1; // enable serial interrupts again
			
		}
		
		return 1;
	}
	else 
		return -1;
}
// Replacement routine for the standard library _getkey routine.
// The getchar and gets functions uses _getkey to read a character.
/*char GetKey (char * C) 
{
	//char c;
	//if buffer have no data
	if (iend == istart) 
		return -1;
	ES0 = 0; // disable serial interrupts during buffer update
	*C = inbuf[istart];
	istart ++;
	if(istart >= ILEN)
		istart = 0;
	ES0 = 1; // enable serial interrupts again
	return 1;
}

void ClearRcvBuf()
{
	istart = 0; // empty transmit buffers
	iend = 0;
}
*/
