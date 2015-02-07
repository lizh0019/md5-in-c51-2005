#include <stdio.h>
#include <string.h>
#include "com.h"

//#include "mainloop.h"
//#include "isr.h"
//#include "protozlg.h"
//#include "ptk_misc_MessageDigest.h"
//typedef unsigned long dword_t;
typedef unsigned char byte_t;
//typedef unsigned int size_t;

//extern CONTROL_XFER ControlData;
typedef struct MD5CheckSum
{
	unsigned long int state[4];
}MD5CheckSum;

void MD5(MD5CheckSum* md5CheckSum, const void* pBuffer, unsigned  int bufferSize);
void MD5_Init(MD5CheckSum* md5CheckSum);
void MD5_Block(MD5CheckSum* md5CheckSum, const void* pBuffer, unsigned int bufferSize);

void MD5_RemainderBlock(MD5CheckSum* md5CheckSum, const void* pBuffer, unsigned int bufferSize);

void delay(unsigned int ti);
void int2hex( unsigned long num );

//Main C function that start the interrupt-driven serial I/O.



//void MD5(MD5CheckSum * md5CheckSum, const void* pBuffer, unsigned int bufferSize);


unsigned char xdata tmpBuf[100];
int xdata tmpcount = 0;
int xdata isusb=0;
unsigned int  number=0;
unsigned char xdata Rec_flag;
unsigned char command;
unsigned char pa[5];
unsigned char xdata windbuf[64];

/*
//*************************************************************************
//  Public static data
//*************************************************************************
*/
MD5CheckSum md5out1;
//extern EPPFLAGS bEPPflags;
//extern unsigned char idata GenEpBuf[];
//extern unsigned char idata EpBuf[];
//unsigned char* buffer;


void main (void) 
{
	
  	// œµÕ≥≥ı ºª
   delay(1000);

	P0 = 0xFF;				//≥ı ºªØI/Oø⁄
	P1 = 0xFF;
	P2 = 0xFF;
	P3 = 0xFF;

	AUXR = 0x01;			//setup ex_ram 8K    0x8E  ALE  ‰≥ˆŒﬁ–ß

	IT0 = 0;				//≥ı ºªØ÷–∂œ  Tcon.0
	///EX0 = 1;//
	EX0 = 0;				//  IEN0.0
	PX0 = 0;//				//   IP.2
	Rec_flag = 0;				
	
	EA = 1;
	
	
	com_initialize (); 		// initialize COM

    putbuf("###MCU Runing OK\r\n");//œÚ…œŒªª˙∑¢ÀÕ›	
    //putbuf("suanfa");
/***********************************************************/
   
 

    pa[0]='1';
	pa[1]='2';
	pa[2]='3';
    pa[3]='4';
    pa[4]='5';
    MD5(&md5out1,pa, 5);
    
    putbuf("md5CheckSum\r\n");
	
    int2hex( md5out1.state[0]);
    putbuf("\r\n");
	int2hex( md5out1.state[1]);
    putbuf("\r\n");
	int2hex( md5out1.state[2]);
    putbuf("\r\n");
	int2hex( md5out1.state[3]);
    putbuf("\r\n");
    //putbuf(&md5out);
    
    
/*****************************************************************/

	while(1);
	
}






void delay(unsigned int ti)
{
  unsigned int pti;
  for(pti=0; pti<ti; pti++)
    {
      ;
      ;
      ;
    }
}



void int2hex( unsigned long num )
{
	char s_int[8];
	int i;
	for ( i=0; i<8; i++)
	{
		s_int[7-i] = num % 16;
		num /= 16;
		s_int[7-i] += ( s_int[7-i]<10 ) ? '0' : ('A'-10);
	/*
	if ( s_int[8-i]<10 )
	s_int[8-i]+='0';
	else
	sint[8-i]+='A';
	*/
	}
     //D12_WriteEndpoint(5, 8, &s_int[0]);
	for ( i=0; i<8; i++ )
		{
			putachar( s_int[i] );
	       
		}
}


unsigned long code MD5_T01 = 0xd76aa478;
unsigned long code MD5_T02 = 0xe8c7b756;
unsigned long code MD5_T03 = 0x242070db;
unsigned long code MD5_T04 = 0xc1bdceee;
unsigned long code MD5_T05 = 0xf57c0faf;
unsigned long code MD5_T06 = 0x4787c62a;
unsigned long code MD5_T07 = 0xa8304613;
unsigned long code MD5_T08 = 0xfd469501;
unsigned long code MD5_T09 = 0x698098d8;
unsigned long code MD5_T10 = 0x8b44f7af;
unsigned long code MD5_T11 = 0xffff5bb1;
unsigned long code MD5_T12 = 0x895cd7be;
unsigned long code MD5_T13 = 0x6b901122;
unsigned long code MD5_T14 = 0xfd987193;
unsigned long code MD5_T15 = 0xa679438e;
unsigned long code MD5_T16 = 0x49b40821;

unsigned long code MD5_T17 = 0xf61e2562;
unsigned long code MD5_T18 = 0xc040b340;
unsigned long code MD5_T19 = 0x265e5a51;
unsigned long code MD5_T20 = 0xe9b6c7aa;
unsigned long code MD5_T21 = 0xd62f105d;
unsigned long code MD5_T22 = 0x02441453;
unsigned long code MD5_T23 = 0xd8a1e681;
unsigned long code MD5_T24 = 0xe7d3fbc8;
unsigned long code MD5_T25 = 0x21e1cde6;
unsigned long code MD5_T26 = 0xc33707d6;
unsigned long code MD5_T27 = 0xf4d50d87;
unsigned long code MD5_T28 = 0x455a14ed;
unsigned long code MD5_T29 = 0xa9e3e905;
unsigned long code MD5_T30 = 0xfcefa3f8;
unsigned long code MD5_T31 = 0x676f02d9;
unsigned long code MD5_T32 = 0x8d2a4c8a;

unsigned long code MD5_T33 = 0xfffa3942;
unsigned long code MD5_T34 = 0x8771f681;
unsigned long code MD5_T35 = 0x6d9d6122;
unsigned long code MD5_T36 = 0xfde5380c;
unsigned long code MD5_T37 = 0xa4beea44;
unsigned long code MD5_T38 = 0x4bdecfa9;
unsigned long code MD5_T39 = 0xf6bb4b60;
unsigned long code MD5_T40 = 0xbebfbc70;
unsigned long code MD5_T41 = 0x289b7ec6;
unsigned long code MD5_T42 = 0xeaa127fa;
unsigned long code MD5_T43 = 0xd4ef3085;
unsigned long code MD5_T44 = 0x04881d05;
unsigned long code MD5_T45 = 0xd9d4d039;
unsigned long code MD5_T46 = 0xe6db99e5;
unsigned long code MD5_T47 = 0x1fa27cf8;
unsigned long code MD5_T48 = 0xc4ac5665;

unsigned long code MD5_T49 = 0xf4292244;
unsigned long code MD5_T50 = 0x432aff97;
unsigned long code MD5_T51 = 0xab9423a7;
unsigned long code MD5_T52 = 0xfc93a039;
unsigned long code MD5_T53 = 0x655b59c3;
unsigned long code MD5_T54 = 0x8f0ccc92;
unsigned long code MD5_T55 = 0xffeff47d;
unsigned long code MD5_T56 = 0x85845dd1;
unsigned long code MD5_T57 = 0x6fa87e4f;
unsigned long code MD5_T58 = 0xfe2ce6e0;
unsigned long code MD5_T59 = 0xa3014314;
unsigned long code MD5_T60 = 0x4e0811a1;
unsigned long code MD5_T61 = 0xf7537e82;
unsigned long code MD5_T62 = 0xbd3af235;
unsigned long code MD5_T63 = 0x2ad7d2bb;
unsigned long code MD5_T64 = 0xeb86d391;


 void MD5_Init(MD5CheckSum* md5CheckSum)
{
	(*md5CheckSum).state[0] = 0x67452301;
	
	(*md5CheckSum).state[1] = 0xefcdab89;
	
	(*md5CheckSum).state[2] = 0x98badcfe;
	
	(*md5CheckSum).state[3] = 0x10325476;

    /*(*md5CheckSum).state[0] = 0x01234567;
	
	(*md5CheckSum).state[1] = 0x89abcdef;
	
	(*md5CheckSum).state[2] = 0xfedcba98;
	
	(*md5CheckSum).state[3] = 0x76543210;
*/
}

 unsigned  long MD5_F(unsigned  long bb, unsigned  long cc, unsigned  long dd)
{
	return ((bb & cc) | (~bb & dd));
}

 unsigned  long MD5_G(unsigned  long bb, unsigned  long cc, unsigned  long dd)
{
	return ((bb & dd) | (cc & ~dd));
}

unsigned  long MD5_H(unsigned  long bb, unsigned  long cc, unsigned  long dd)
{
	return (bb ^ cc ^ dd);
}

 unsigned  long MD5_I(unsigned  long bb, unsigned  long cc, unsigned  long dd)
{
	return (cc ^ (bb | ~dd));
}

 unsigned  long MD5_CYCLIC(unsigned  long w, unsigned  long s)
{
	return (w << s) | (w >> (32 - s));
}

 void MD5_FF(unsigned  long* aa, unsigned  long bb, unsigned  long cc, unsigned  long dd, unsigned  long k, unsigned  long s, unsigned  long t)
{
	(*aa) = bb + MD5_CYCLIC(((*aa) + MD5_F(bb, cc, dd) + k + t), s);
}

 void MD5_GG(unsigned  long* aa, unsigned  long bb, unsigned  long cc, unsigned  long dd, unsigned  long k, unsigned  long s, unsigned  long t)
{
	(*aa) = bb + MD5_CYCLIC(((*aa) + MD5_G(bb, cc, dd) + k + t), s);
}

 void MD5_HH(unsigned  long* aa, unsigned  long bb, unsigned  long cc, unsigned  long dd, unsigned  long k, unsigned  long s, unsigned  long t)
{
	(*aa) = bb + MD5_CYCLIC(((*aa) + MD5_H(bb, cc, dd) + k + t), s);
}

 void MD5_II(unsigned  long *aa, unsigned  long bb, unsigned  long cc, unsigned  long dd, unsigned  long k, unsigned  long s, unsigned  long t)
{
	(*aa) = bb + MD5_CYCLIC(((*aa) + MD5_I(bb, cc, dd) + k + t), s);
}

 void MD5_Packet(MD5CheckSum* md5CheckSum, const unsigned  long* pPacket)
{
 	unsigned  long aa =(*md5CheckSum).state[0];
	unsigned  long bb =(*md5CheckSum).state[1];
	unsigned  long cc =(*md5CheckSum).state[2];
	unsigned  long dd =(*md5CheckSum).state[3];
	
	MD5_FF(&aa, bb, cc, dd, pPacket[0],   7, MD5_T01);
	MD5_FF(&dd, aa, bb, cc, pPacket[1],  12, MD5_T02);
	MD5_FF(&cc, dd, aa, bb, pPacket[2],  17, MD5_T03);
	MD5_FF(&bb, cc, dd, aa, pPacket[3],  22, MD5_T04);
	MD5_FF(&aa, bb, cc, dd, pPacket[4],   7, MD5_T05);
	MD5_FF(&dd, aa, bb, cc, pPacket[5],  12, MD5_T06);
	MD5_FF(&cc, dd, aa, bb, pPacket[6],  17, MD5_T07);
	MD5_FF(&bb, cc, dd, aa, pPacket[7],  22, MD5_T08);
	MD5_FF(&aa, bb, cc, dd, pPacket[8],   7, MD5_T09);
	MD5_FF(&dd, aa, bb, cc, pPacket[9],  12, MD5_T10);
	MD5_FF(&cc, dd, aa, bb, pPacket[10], 17, MD5_T11);
	MD5_FF(&bb, cc, dd, aa, pPacket[11], 22, MD5_T12);
	MD5_FF(&aa, bb, cc, dd, pPacket[12],  7, MD5_T13);
	MD5_FF(&dd, aa, bb, cc, pPacket[13], 12, MD5_T14);
	MD5_FF(&cc, dd, aa, bb, pPacket[14], 17, MD5_T15);
	MD5_FF(&bb, cc, dd, aa, pPacket[15], 22, MD5_T16);
	
	MD5_GG(&aa, bb, cc, dd, pPacket[1],   5, MD5_T17);
	MD5_GG(&dd, aa, bb, cc, pPacket[6],   9, MD5_T18);
	MD5_GG(&cc, dd, aa, bb, pPacket[11], 14, MD5_T19);
	MD5_GG(&bb, cc, dd, aa, pPacket[0],  20, MD5_T20);
	MD5_GG(&aa, bb, cc, dd, pPacket[5],   5, MD5_T21);
	MD5_GG(&dd, aa, bb, cc, pPacket[10],  9, MD5_T22);
	MD5_GG(&cc, dd, aa, bb, pPacket[15], 14, MD5_T23);
	MD5_GG(&bb, cc, dd, aa, pPacket[4],  20, MD5_T24);
	MD5_GG(&aa, bb, cc, dd, pPacket[9],   5, MD5_T25);
	MD5_GG(&dd, aa, bb, cc, pPacket[14],  9, MD5_T26);
	MD5_GG(&cc, dd, aa, bb, pPacket[3],  14, MD5_T27);
	MD5_GG(&bb, cc, dd, aa, pPacket[8],  20, MD5_T28);
	MD5_GG(&aa, bb, cc, dd, pPacket[13],  5, MD5_T29);
	MD5_GG(&dd, aa, bb, cc, pPacket[2],   9, MD5_T30);
	MD5_GG(&cc, dd, aa, bb, pPacket[7],  14, MD5_T31);
	MD5_GG(&bb, cc, dd, aa, pPacket[12], 20, MD5_T32);
	
	MD5_HH(&aa, bb, cc, dd, pPacket[5],   4, MD5_T33);
	MD5_HH(&dd, aa, bb, cc, pPacket[8],  11, MD5_T34);
	MD5_HH(&cc, dd, aa, bb, pPacket[11], 16, MD5_T35);
	MD5_HH(&bb, cc, dd, aa, pPacket[14], 23, MD5_T36);
	MD5_HH(&aa, bb, cc, dd, pPacket[1],   4, MD5_T37);
	MD5_HH(&dd, aa, bb, cc, pPacket[4],  11, MD5_T38);
	MD5_HH(&cc, dd, aa, bb, pPacket[7],  16, MD5_T39);
	MD5_HH(&bb, cc, dd, aa, pPacket[10], 23, MD5_T40);
	MD5_HH(&aa, bb, cc, dd, pPacket[13],  4, MD5_T41);
	MD5_HH(&dd, aa, bb, cc, pPacket[0],  11, MD5_T42);
	MD5_HH(&cc, dd, aa, bb, pPacket[3],  16, MD5_T43);
	MD5_HH(&bb, cc, dd, aa, pPacket[6],  23, MD5_T44);
	MD5_HH(&aa, bb, cc, dd, pPacket[9],   4, MD5_T45);
	MD5_HH(&dd, aa, bb, cc, pPacket[12], 11, MD5_T46);
	MD5_HH(&cc, dd, aa, bb, pPacket[15], 16, MD5_T47);
	MD5_HH(&bb, cc, dd, aa, pPacket[2],  23, MD5_T48);
	
	MD5_II(&aa, bb, cc, dd, pPacket[0],   6, MD5_T49);
	MD5_II(&dd, aa, bb, cc, pPacket[7],  10, MD5_T50);
	MD5_II(&cc, dd, aa, bb, pPacket[14], 15, MD5_T51);
	MD5_II(&bb, cc, dd, aa, pPacket[5],  21, MD5_T52);
	MD5_II(&aa, bb, cc, dd, pPacket[12],  6, MD5_T53);
	MD5_II(&dd, aa, bb, cc, pPacket[3],  10, MD5_T54);
	MD5_II(&cc, dd, aa, bb, pPacket[10], 15, MD5_T55);
	MD5_II(&bb, cc, dd, aa, pPacket[1],  21, MD5_T56);
	MD5_II(&aa, bb, cc, dd, pPacket[8],   6, MD5_T57);
	MD5_II(&dd, aa, bb, cc, pPacket[15], 10, MD5_T58);
	MD5_II(&cc, dd, aa, bb, pPacket[6],  15, MD5_T59);
	MD5_II(&bb, cc, dd, aa, pPacket[13], 21, MD5_T60);
	MD5_II(&aa, bb, cc, dd, pPacket[4],   6, MD5_T61);
	MD5_II(&dd, aa, bb, cc, pPacket[11], 10, MD5_T62);
	MD5_II(&cc, dd, aa, bb, pPacket[2],  15, MD5_T63);
	MD5_II(&bb, cc, dd, aa, pPacket[9],  21, MD5_T64);
	
	
	(*md5CheckSum).state[0] += aa;
	(*md5CheckSum).state[1] += bb;
	(*md5CheckSum).state[2] += cc;
	(*md5CheckSum).state[3] += dd;
}

void MD5_Block(MD5CheckSum* md5CheckSum, const void* pBuffer, unsigned int bufferSize)
{
	unsigned  char* pSrc = (byte_t*)pBuffer;
    unsigned  char packet[64];
	unsigned  int count = bufferSize/64;
	unsigned   int i;
	for(i = 0; i < count; ++i)
	{
		memcpy(packet, pSrc, 64);
		MD5_Packet(md5CheckSum, (unsigned  long*)packet);
		pSrc += 64;
	}
}

void MD5_RemainderBlock(MD5CheckSum* md5CheckSum, 
						const void* pBuffer, 
						unsigned  int bufferSize)
{
	byte_t packet[64];
	//size_t remainder = bufferSize % 64;	
    unsigned int remainder = bufferSize % 64;	
	byte_t* pSrc = (byte_t*)pBuffer + bufferSize - remainder;

	if(remainder < 56)
	{
		memcpy(packet, pSrc, remainder);
		packet[remainder] = 0x80;
		memset(&packet[remainder+1], 0, 56 - remainder - 1);
	    *((unsigned long int*)&packet[60]) = bufferSize >> 29;
		*((unsigned long int*)&packet[56]) = bufferSize << 3;//packet[56]=buffersize*8
		MD5_Packet(md5CheckSum, (unsigned  long*)packet);
	}
	else
	{
		memcpy(packet, pSrc, remainder);
		packet[remainder] = 0x80;
		memset(&packet[remainder+1], 0, 64 - remainder - 1);
		MD5_Packet(md5CheckSum, (unsigned long*)packet);
		memset(packet, 0, 56);
		*((unsigned long int*)&packet[60]) = bufferSize >> 29;
		*((unsigned long int*)&packet[56]) = bufferSize << 3;//packet[56]=buffersize*8
		MD5_Packet(md5CheckSum, (unsigned  long*)packet);
	}
}


void MD5(MD5CheckSum* md5CheckSum, const void* pBuffer, unsigned  int bufferSize)
{
	MD5_Init(md5CheckSum);
	MD5_Block(md5CheckSum, pBuffer, bufferSize);
	MD5_RemainderBlock(md5CheckSum, pBuffer, bufferSize);
}

