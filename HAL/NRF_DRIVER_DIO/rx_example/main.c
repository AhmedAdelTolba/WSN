#include"../DIO-interface.h"
#include <stdint.h>
#include "../nrf24.h"
#include <util/delay.h>


int main()
    {
    uint8_t counter =2 ;

    uint16_t outer_counter = 0;

    uint8_t data_array[4];

    uint8_t tx_address[5] =
	{
//		0xee, 0xff, 0x12, 0xcb, 0x57
		0xaa,0xff,0x12,0xcb,0x57
	};
    uint8_t rx_address[5] =  //////////my address as a reciever
		{
		0xaa, 0xee, 0x12, 0xcb, 0x57
//			0xaa, 0xaa, 0xaa, 0xaa, 0xaa

		};

    uint8_t sent_packet[4] =
	{
		0,0,0,0//0x44, 0x44, 0x44, 0x44
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

    while (1)
	{
	outer_counter++;

	if (nrf24_dataReady())
	    {

	    nrf24_getData(data_array);

	    for (int i = 0; i < 4; i++)
		{
		sent_packet[i]=counter;
		//PORTD = ~data_array[i];
		DIO_u8WritePortVal(DIO_u8PORT3, ~data_array[i]);
		}
	    _delay_ms(30);

	    nrf24_powerUpTx();
	    nrf24_send(sent_packet);
	    while (nrf24_isSending())
		;
	    nrf24_powerUpRx();

	    counter++;
	    }

	}
    return 0;
    }
/* ------------------------------------------------------------------------- */
