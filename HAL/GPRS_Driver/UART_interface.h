/*
 * UART_interface.h
 *
 *  Created on: Apr 18, 2016
 *      Author: Bassam
 */

#ifndef _UART_INTERFACE_H_
#define _UART_INTERFACE_H_





extern void uart_init(void);
extern void uart_putc(unsigned char c);
extern void uart_puts(const char *s);
//extern void uart_write_int16( int16_t in);
extern unsigned char uart_available(void);
extern char uart_read(void);

#endif /* UART_INTERFACE_H_ */
