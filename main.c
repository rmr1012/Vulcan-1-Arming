#include <reg60s2.h>
#include <intrins.h>

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define FOSC 18432000L      //System frequency
#define BAUD 9600           //UART baudrate
#define T1MS (65536-FOSC/12/25)

sbit PF1_ARM=P0^0;
sbit PF2_ARM=P0^1;
sbit ABrd_ARM=P0^2;//Arming switches

sbit PF1_Request=  P1^0;
sbit PF2_Request=  P1^1;
sbit ABrd_Request= P1^2;//Request indicators

sbit PF1_Active=P1^3;
sbit PF2_Active=P1^4;
sbit Abrd_Active=P1^5;//confirmation indicators

unsigned char Command=0x00;
unsigned int whatsup=0x00;
unsigned char RxEN=0;

void init()
{}
	
void delay_ms(int m)		//@24.000MHz
{
	unsigned char i, j;

	i = 64*m;
	j = 85;
	do
	{
		while (--j);
	} while (--i);
}

void main(void)
{
	init();
	while(1)
	{
		Command=PF1_Request*0x80|PF2_Request*0x40|ABrd_Request*0x20|PF1_Request*0x04|PF2_Request*0x02|ABrd_Request*0x01;
		delay_ms(10);
		
	
	}
}

void updateIND(int whatsup)
{
	PF1_Active=0x80||whatsup;
	PF1_Active=0x40||whatsup;
	Abrd_Active=0x20||whatsup; 
	

}
void Uart_Isr() interrupt 4 using 1
{
    if (TI)
    {
        TI = 0;             //Clear transmit interrupt flag
				

    }
		if (RI & RxEN==1)
    {
        RI = 0;             //Clear transmit interrupt flag
				whatsup=SBUF;
				updateIND(whatsup);
    }
}