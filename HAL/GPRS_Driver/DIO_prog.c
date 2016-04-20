/*
 * DIO_prog.c
 *
 *  Created on: Jan 27, 2016
 *      Author: bassam
 */
#include "types.h"
#include "util.h"
#include "DIO_interface.h"
#include "DIO_config.h"
#include "DIO_private.h"
/*
static uint8_t *const DIO_PINarr[4]={PINA,PINB,PINC,PIND};
static uint8_t *const DIO_u8DDRarr[4]= {DDRA,DDRB,DDRC,DDRD};
static uint8_t *const DIO_u8PORTarr[4]= {PORTA,PORTB,PORTC,PORTD};
*/

void DIO_voidInit(void)
	{
	DDRA=DIO_u8PORTADIR;
	DDRB=DIO_u8PORTBDIR;
	DDRC=DIO_u8PORTCDIR;
	DDRD=DIO_u8PORTDDIR;

	PORTA|=(DIO_u8PORTADIR) & (DIO_u8PORTAVAL);
	PORTB|=(DIO_u8PORTBDIR) & (DIO_u8PORTBVAL);
	PORTC|=(DIO_u8PORTCDIR) & (DIO_u8PORTCVAL);
	PORTD|=(DIO_u8PORTDDIR) & (DIO_u8PORTDVAL);

	}

uint8_t DIO_u8ReadPinVal(uint8_t Copy_u8PinIdx,uint8_t* Copy_u8PtrToVal)

{
	uint8_t local_u8DIOPinIdx=(Copy_u8PinIdx) % (u8PORTSPINNUM) ;
	uint8_t local_u8DIOReadStatus=OK;
	switch (Copy_u8PinIdx/u8PORTSPINNUM)
	{
	case DIO_u8PORT0	:
		*Copy_u8PtrToVal = GetBit(PINA,local_u8DIOPinIdx);
		break;
	case DIO_u8PORT1	:
		*Copy_u8PtrToVal = GetBit(PINB,local_u8DIOPinIdx);
		break;
	case DIO_u8PORT2	:
		*Copy_u8PtrToVal = GetBit(PINC,local_u8DIOPinIdx);
		break;
	case DIO_u8PORT3	:
		*Copy_u8PtrToVal = GetBit(PIND,local_u8DIOPinIdx);
		break;
	default:
		local_u8DIOReadStatus=NOT_OK;
		break;
	}
	return local_u8DIOReadStatus;
}

uint8_t DIO_u8WritePinVal(uint8_t Copy_u8PinIdx,uint8_t Copy_u8PinVal)
{

uint8_t local_u8DIOPinWriteStatus=OK;
uint8_t local_u8DIOPinIdx=(Copy_u8PinIdx) % (u8PORTSPINNUM) ;

/*
 if(local_u8DIOPinIdx<=u8PINSNUM)
 {

 }
 */

switch (Copy_u8PinIdx/u8PORTSPINNUM)
	{
		case DIO_u8PORT0	:
			switch(Copy_u8PinVal)
				{
			case DIO_u8LOW:
				ClrBit(PORTA,local_u8DIOPinIdx);
				break;
			default:
				SetBit(PORTA,local_u8DIOPinIdx);
				break;
				}
			break;
		case DIO_u8PORT1	:
			switch(Copy_u8PinVal)
					{
					case DIO_u8LOW:
						ClrBit(PORTB,local_u8DIOPinIdx);
					break;
					default:
						SetBit(PORTB,local_u8DIOPinIdx);
					break;
					}
			break;
		case DIO_u8PORT2	:
			switch(Copy_u8PinVal)
					{
					case DIO_u8LOW:
						ClrBit(PORTC,local_u8DIOPinIdx);
					break;
					default:
						SetBit(PORTC,local_u8DIOPinIdx);
					break;
					}

			break;
		case DIO_u8PORT3	:
			switch(Copy_u8PinVal)
					{
					case DIO_u8LOW:
						ClrBit(PORTD,local_u8DIOPinIdx);
					break;
					default:
						SetBit(PORTD,local_u8DIOPinIdx);
					break;
					}
			break;
		default:
			local_u8DIOPinWriteStatus=NOT_OK;
			break;
	}
return local_u8DIOPinWriteStatus;
}
uint8_t DIO_u8WritePortVal(uint8_t Copy_u8PortIdx, uint8_t Copy_u8PortVal)
{
uint8_t local_u8WritePortStatus=OK;
/*
 if(Copy_u8PortIdx<PORTSNUM)
 	 {
 	 	 *DIO_u8PORTarr[Copu_u8PortIdx]=Copy_u8PortVal;
 	 }
 else
 	 {
 	 	 local_u8WritePortStatus=NOT_OK;
 	 }

  */
switch(Copy_u8PortIdx)
	{
		case DIO_u8PORT0	:
			PORTA= (Copy_u8PortVal);
			break;
		case DIO_u8PORT1	:
			PORTB= (Copy_u8PortVal);
			break;
		case DIO_u8PORT2	:
			PORTC= (Copy_u8PortVal);
			break;
		case DIO_u8PORT3	:
			PORTD= (Copy_u8PortVal);
			break;
		default:
			local_u8WritePortStatus=NOT_OK;
			break;
	}
return local_u8WritePortStatus;
}

uint8_t DIO_u8ReadPortVal(uint8_t Copy_u8PortIdx, uint8_t* Copy_u8PtrToVal)
{
	uint8_t local_u8DIOReadPortStatus=OK;
	/*
	 if(Copy_u8PortIdx<PORTSNUM)
	 	 {
	 	 	 *Copy_u8PtrToVal=*DIO_u8PINarr[Copy_u8PortIdx];
	 	 }
	 	 else
	 	 {
	 	 local_u8DIOReadPortStatus=NOT_OK;
	 	 }
	 */
	switch(Copy_u8PortIdx)
	{
	case DIO_u8PORT0	:
		*Copy_u8PtrToVal=PINA;
		break;
	case DIO_u8PORT1	:
		*Copy_u8PtrToVal=PINB;
		break;
	case DIO_u8PORT2	:
		*Copy_u8PtrToVal=PINC;
		break;
	case DIO_u8PORT3	:
		*Copy_u8PtrToVal=PIND;
		break;
	default				:
		local_u8DIOReadPortStatus=NOT_OK;
		break;

	}
return local_u8DIOReadPortStatus;
}
uint8_t DIO_u8WritePinDir(uint8_t Copy_u8PinIdx, uint8_t Copy_u8PinDir)
{
	uint8_t local_u8WritePinDirStatus=OK;
	uint8_t local_u8DIOPinIdx=(Copy_u8PinIdx) % (u8PORTSPINNUM) ;

	switch (Copy_u8PinIdx/u8PORTSPINNUM)
		{
			case DIO_u8PORT0	:
				switch(Copy_u8PinDir)
					{
				case DIO_u8INPUT:
					ClrBit(DDRA,local_u8DIOPinIdx);
					break;
				default:
					SetBit(DDRA,local_u8DIOPinIdx);
					break;
					}
				break;
			case DIO_u8PORT1	:
				switch(Copy_u8PinDir)
									{
								case DIO_u8INPUT:
									ClrBit(DDRB,local_u8DIOPinIdx);
									break;
								default:
									SetBit(DDRB,local_u8DIOPinIdx);
									break;
									}
				break;
			case DIO_u8PORT2	:
				switch(Copy_u8PinDir)
									{
								case DIO_u8INPUT:
									ClrBit(DDRC,local_u8DIOPinIdx);
									break;
								default:
									SetBit(DDRC,local_u8DIOPinIdx);
									break;
									}

				break;
			case DIO_u8PORT3	:
				switch(Copy_u8PinDir)
									{
								case DIO_u8INPUT:
									ClrBit(DDRD,local_u8DIOPinIdx);
									break;
								default:
									SetBit(DDRD,local_u8DIOPinIdx);
									break;
									}
				break;
			default:
				local_u8WritePinDirStatus=NOT_OK;
				break;
		}
return local_u8WritePinDirStatus;
}

uint8_t DIO_u8WritePortDir(uint8_t Copy_u8PortIdx, uint8_t Copy_u8PortDir)
{
	uint8_t local_u8WritePortDirStatus=OK;
	switch(Copy_u8PortIdx)
		{
			case DIO_u8PORT0	:
				DDRA=Copy_u8PortDir;
				break;
			case DIO_u8PORT1	:
				DDRB=Copy_u8PortDir;
				break;
			case DIO_u8PORT2	:
				DDRC=Copy_u8PortDir;
				break;
			case DIO_u8PORT3	:
				DDRD=Copy_u8PortDir;
				break;
			default:
				local_u8WritePortDirStatus=NOT_OK;
				break;
		}
	return local_u8WritePortDirStatus;
}


uint8_t DIO_u8ReadPinDir(uint8_t Copy_u8PinIdx,uint8_t* Copy_u8PtrToDir)
{
	uint8_t local_u8ReadPinDirStatus=OK;

	uint8_t local_u8DIOPinIdx=(Copy_u8PinIdx) % (u8PORTSPINNUM) ;

		switch (Copy_u8PinIdx/u8PORTSPINNUM)
		{
		case DIO_u8PORT0	:
			*Copy_u8PtrToDir = GetBit(DDRA,local_u8DIOPinIdx);
			break;
		case DIO_u8PORT1	:
			*Copy_u8PtrToDir = GetBit(DDRB,local_u8DIOPinIdx);
			break;
		case DIO_u8PORT2	:
			*Copy_u8PtrToDir = GetBit(DDRC,local_u8DIOPinIdx);
			break;
		case DIO_u8PORT3	:
			*Copy_u8PtrToDir = GetBit(DDRD,local_u8DIOPinIdx);
			break;
		default:
			local_u8ReadPinDirStatus=NOT_OK;
			break;
		}
	return local_u8ReadPinDirStatus;
}
uint8_t DIO_u8ReadPortDir(uint8_t Copy_u8PortIdx,uint8_t* Copy_u8PtrToDir)
{
	uint8_t local_u8ReadPortDirStatus=OK;
		switch(Copy_u8PortIdx)
		{
		case DIO_u8PORT0	:
			*Copy_u8PtrToDir=DDRA;
			break;
		case DIO_u8PORT1	:
			*Copy_u8PtrToDir=DDRB;
			break;
		case DIO_u8PORT2	:
			*Copy_u8PtrToDir=DDRC;
			break;
		case DIO_u8PORT3	:
			*Copy_u8PtrToDir=DDRD;
			break;
		default				:
			local_u8ReadPortDirStatus=NOT_OK;
			break;
		}
		return local_u8ReadPortDirStatus;
}
