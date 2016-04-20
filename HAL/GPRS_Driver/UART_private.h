/*
 * UART_private.h
 *
 *  Created on: Mar 16, 2016
 *      Author: Bassam
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_


#define Conc(x7,x6,x5,x4,x3,x2,x1,x0)	conc_helper(x7,x6,x5,x4,x3,x2,x1,x0)
#define conc_helper(x7,x6,x5,x4,x3,x2,x1,x0)	0b##x7##x6##x5##x4##x3##x2##x1##x0



//#define UDR			*((volatile uint8_t*) (0x2C))
//#define UCSRA		*((volatile uint8_t*) (0x2B))
//#define UCSRB		*((volatile uint8_t*) (0x2A))
//#define UCSRC		*((volatile uint8_t*) (0x40))
//#define	UBRRL		*((volatile uint8_t*) (0x29))
//#define	UBRRH		*((volatile uint8_t*) (0x40))

#define RXEN		4
#define TXEN		3
#define RXCIE		7
#define URSEL		7
#define UCSZ1		2
#define UCSZ0		1
#define UDRE		5



#endif /* UART_PRIVATE_H_ */
