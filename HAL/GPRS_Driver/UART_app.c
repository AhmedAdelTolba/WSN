/*
 * UART_app.c
 *
 *  Created on: Apr 18, 2016
 *      Author: Bassam
 */


/*  UART implementation using the ATMEL ATMega32 MCU
    By - Nandan Banerjee (08/CSE/15)
         NIT Durgapur
         16/06/2010
*/

// UART Baud rate - 9600 bps
//#include "types.h"
#include <avr/pgmspace.h>
#include "util.h"
#include "UART_private.h"
#include "UART_interface.h"

#define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,used,externally_visible)); \
    void vector (void)

#define UBRR 25
uint8_t uart_buffer[250]={0x00};
uint8_t buffer_counter=0;
uint8_t recieve_flag=1;
static void (*uart_ptr_ISR)(void);

void uart_voidfun(void)
{
	}
void Set_EXT0_ISR(void (*ptr_callback_ISR)(void))
{
	uart_ptr_ISR=ptr_callback_ISR;
}

extern void uart_init()
{
    UBRRH = (uint8_t)(UBRR >> 8);
    UBRRL = (uint8_t)(UBRR);
    UCSRB = ((1<<RXEN) | (1<<TXEN) | (1<<RXCIE));   // Enable Receiver, Transmitter, Receive Interrupt
    UCSRC = ((1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0));     // 8N1 data frame
    uart_ptr_ISR=uart_voidfun;
}

extern void uart_putc(unsigned char c)
{
    // wait until UDR ready
    while(!(UCSRA & (1 << UDRE)));
    UDR = c;    // send character
    //UDR= 5;
}

extern void uart_puts(const char *s)
{
    //  loop until *s != NULL
    while(*s != '\0')
    {
        uart_putc(*(s++));
    }
}

/*extern void uart_write_int16(int16_t in)
{
    uint8_t started = 0;
    uint16_t pow = 10000;

    while (pow >= 1)
    {
        if (in/pow > 0 || started || pow == 1)
        {
            uart_putc((uint8_t) (in/pow) + '0');
            started = 1;
            in = in % pow;
        }
        pow = pow / 10;
    }
}
*/
extern char uart_read()
{
	char Data;
	recieve_flag=0;
	buffer_counter--;
	if(buffer_counter==255)
	{
		buffer_counter=0;
	}
	Data=uart_buffer[buffer_counter];
	recieve_flag=1;
	return Data;
}
extern unsigned char uart_available(void)
{
	return buffer_counter;
}
ISR(__vector_13)
{
    // USART RX interrupt
	uint8_t temp;
	if(recieve_flag==1)
	{
	uart_buffer[buffer_counter]=UDR;
	buffer_counter++;
	if(buffer_counter==250)
	{
		temp=UDR;
	}
	}
    // User code to handle the interrupt goes here.
}
