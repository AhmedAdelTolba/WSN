/*
* ----------------------------------------------------------------------------
*
â€œTHE COFFEEWARE LICENSEâ€� (Revision 1):
* <ihsan@kehribar.me> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a coffee in return.
* -----------------------------------------------------------------------------
*/

#include "../nrf24.h"
#include <util/delay.h>

uint8_t temp;
uint8_t q = 1;
uint8_t data_array[4];
uint8_t akc_array[4]={255,255,255,255};
uint8_t tx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
uint8_t rx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};
uint32_t x ;
/* ------------------------------------------------------------------------- */
int main()
{


    /* init hardware pins */
    nrf24_init();
    
    /* Channel #2 , payload length: 4 */
    nrf24_config(2,4);

    /* Set the device addresses */
    nrf24_tx_address(tx_address);
    nrf24_rx_address(rx_address);    

    while(1)
    {                
        /* Fill the data buffer */
        data_array[0] = q;
        data_array[1] = q;
        data_array[2] = q;
        data_array[3] = q;
//
//        /* Automatically goes to TX mode */

        nrf24_send(data_array);

        /* Wait for transmission to end */
        while(nrf24_isSending());

        /* Make analysis on last tranmission attempt */
        temp = nrf24_lastMessageStatus();

        if(temp == NRF24_TRANSMISSON_OK)
        {                    

        }
        else if(temp == NRF24_MESSAGE_LOST)
        {                    

        }
        
		/* Retranmission count indicates the tranmission quality */
		temp = nrf24_retransmissionCount();
//		akc_array[0]=temp;
//		akc_array[1]=temp;
//		akc_array[2]=temp;
//		akc_array[3]=temp;
//
//		 nrf24_send(akc_array);
//		 /* Wait for transmission to end */
//		 while(nrf24_isSending());

		 /* Optionally, go back to RX mode ... */
		nrf24_powerUpRx();

		/* Or you might want to power down after TX */
		// nrf24_powerDown();            

		/* Wait a little ... */

		_delay_ms(3000);
		q++;
//		break;
    }
}
/* ------------------------------------------------------------------------- */
