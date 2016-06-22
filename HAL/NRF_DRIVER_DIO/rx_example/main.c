//#include <avr/io.h>
//#include<avr/delay.h>
//int main()
//    {
//
//    DDRD = 0xff;
//    PORTD=0xff;
//    while (1)
//
//	{
//	_delay_ms(1000);
//	PORTD ^= 0xff;
//	}
//
//    return 0;
//    }
//#include"../DIO-interface.h"
//#include <stdint.h>
//#include "../nrf24.h"
//# define F_CPU 1600000UL
//#include <util/delay.h>
//#include "../commands.h"
//
//char x = 3;
//void handle_command(uint8_t state)
//    {
//
//    uint8_t sent_packet[4];
//
//    switch (state)
//	{
//    case GET_DATA:
//	if (x == 3)
//	    {
//	    sent_packet[0] = x;
//	    sent_packet[1] = x;
//	    sent_packet[2] = x;
//	    sent_packet[3] = 1;
//	    //_delay_ms(10);
//	    nrf24_powerUpTx();
//	    nrf24_send(sent_packet);
//	    while (nrf24_isSending())
//		;
//	    x++;
//	    //x++;
//	    //x++;
//	    }
//	else
//	    {
//	    sent_packet[0] = x++;
//	    sent_packet[1] = x++;
//	    sent_packet[2] = x++;
//	    sent_packet[3] = 0;
//	    //_delay_ms(10);
//	    nrf24_powerUpTx();
//	    nrf24_send(sent_packet);
//	    while (nrf24_isSending())
//		;
//	    }
////	sent_packet[0] = 0x00;
////	sent_packet[1] = 1;
////	sent_packet[2] = 2;
////	sent_packet[3] = 3;
////	_delay_ms(10);
////	nrf24_send(sent_packet);
////	while (nrf24_isSending())
////	    ;
////
////
////
////	sent_packet[0] = 0xED;
////	sent_packet[1] = 0xED;
////	sent_packet[2] = 0xED;
////	sent_packet[3] = 0xED;
////	_delay_ms(3000);
////	nrf24_send(sent_packet);
////	while (nrf24_isSending())
////	    ;
//	nrf24_powerUpRx();
//
//	break;
//
//    default:
//	break;
//	}
//
//    return;
//    }
//
//int main()
//    {
////    uint8_t counter = 2;
////
////    uint16_t outer_counter = 0;
//
//    uint8_t data_array[4];
//
//    uint8_t tx_address[5] =
//	{
////		0xee, 0xff, 0x12, 0xcb, 0x57
//		0xaa,
//		0xff,
//		0x12,
//		0xcb,
//		0x57
//	};
//    uint8_t rx_address[5] =  //////////my address as a reciever
//		{
//		0xaa, 0xee, 0x12, 0xcb, 0x57
////			0xaa, 0xaa, 0xaa, 0xaa, 0xaa
//
//		};
//
//    uint8_t sent_packet[4] =
//	{
//	0, 0, 0, 0
//	//0x44, 0x44, 0x44, 0x44
//	    };
//    ///////////////////
//
//    DIO_u8WritePortDir(DIO_u8PORT3, 0xff);
//
//    /* init hardware pins */
//    nrf24_init();
//
//    /* Channel #2 , payload length: 4 */
//    nrf24_config(2, 4);
//    //   0010 0000
//    /* Set the device addresses */
//    nrf24_tx_address(tx_address);
//
//    nrf24_rx_address(rx_address);
//    //set_bit(DDRC, 0);
//
//    DIO_u8WritePortVal(DIO_u8PORT3, 0x33);
//
//    while (1)
//	{
//	//outer_counter++;
//
//	if (nrf24_dataReady())
//	    {
//
//	    nrf24_getData(data_array);
//
//	    if (data_array[1] == 0) //check my id ,myid=1
//		{
//
//		handle_command(data_array[2]);
//
//		//counter++;
//		}
//	    }
//	}
//    return 0;
//    }
///* ------------------------------------------------------------------------- */
#include"../DIO-interface.h"
#include <stdint.h>
#include "../nrf24.h"
# define F_CPU 1600000UL
#include <util/delay.h>

int main()
    {
    uint8_t counter = 2;

    uint16_t outer_counter = 0;

    uint8_t data_array[4];

    uint8_t tx_address[5] =
	{
	0xee, 0xff, 0x12, 0xcb, 0x57
//		0xaa,0xff,0x12,0xcb,0x57
	    };
    uint8_t rx_address[5] =  //////////my address as a reciever
		{
		0xaa, 0xee, 0x12, 0xcb, 0x57
//			0xaa, 0xaa, 0xaa, 0xaa, 0xaa

		};

    uint8_t sent_packet[4] =
	{
		0xf0, 0xf0, 0xf0, 0xf0
	//0x44, 0x44, 0x44, 0x44
	    };
    ///////////////////

    DIO_u8WritePortDir(DIO_u8PORT3, 0xff);

    /* init hardware pins */
    nrf24_init();

    /* Channel #2 , payload length: 4 */
    nrf24_config(2, 4);
    //   0010 0000
    /* Set the device addresses */
    nrf24_tx_address(tx_address);

    nrf24_rx_address(rx_address);
    //set_bit(DDRC, 0);

    DIO_u8WritePortVal(DIO_u8PORT3, 0x33);
//while(1)
//    {
//
//    }
    while (1)
	{

//	if (nrf24_dataReady())
//	    {
//	    sent_packet[0]++;
//	    nrf24_getData(data_array);
//	DIO_u8WritePortVal(DIO_u8PORT3, data_array[1]);
//			    nrf24_powerUpTx();
//			    nrf24_send(sent_packet);
//			    while (nrf24_isSending())
//				;
//			    nrf24_powerUpRx();
//
//
//	    }
//
	if (nrf24_dataReady())
	    {

	    nrf24_getData(data_array);

	    if (data_array[3] == (data_array[0] ^ data_array[1] ^ data_array[2]))
		{
		if (data_array[0] == 1)

		    {
		    DIO_u8WritePortVal(DIO_u8PORT3, data_array[1]);
		    nrf24_powerUpTx();
		    nrf24_send(sent_packet);
		    while (nrf24_isSending())
			;
		    nrf24_powerUpRx();

		    }
		else
		    {

		    }
		}
	    else
		{
		DIO_u8WritePortVal(DIO_u8PORT3, 0xf0);
		}

	    }
	}

    return 0;
    }
///* ------------------------------------------------------------------------- */
