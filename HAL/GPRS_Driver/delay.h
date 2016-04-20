/*
 * delay.h
 *
 *  Created on: Feb 2, 2016
 *      Author: bassam
 */

#ifndef DELAY_H_
#define DELAY_H_


#define DELAY_voidDELAY(Copy_u8DelayVal)  do{ \
							uint32_t Local_u32Duration;\
							for(Local_u32Duration=(Copy_u8DelayVal*114.285714);Local_u32Duration>0;Local_u32Duration --)\
							{__asm__("NOP");}} while(0)

#endif /* DELAY_H_ */
