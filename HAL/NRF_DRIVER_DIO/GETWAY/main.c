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
#include "../DIO-interface.h"

#define mx_retransmetion 15

uint8_t temp;
uint8_t q = 1;
uint8_t data_array[4];
uint8_t akc_array[4]={255,255,255,255};
uint8_t tx_addressNODE[5] = {0xcf,0xcf,0xcf,0xcf,0xcf}; // bet7ot el address beta3 el module elly bteb3atlo lw enta tx
uint8_t tx_addressCOR[5] = {0xff,0xff,0xff,0xff,0xff};
uint8_t rx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7}; // bt7ot el address bta3ak law enta rx
uint8_t rx_arr[4]={0};
uint32_t x ;
uint8_t counter=0 ,flag=0 ;
uint8_t count =0 ;
/* ------------------------------------------------------------------------- */
void Auto_ACK() ;

int main()
{

	DIO_voidInit();
    /* init hardware pins */
    nrf24_init();
    
    /* Channel #2 , payload length: 4 */
    nrf24_config(2,4);

    /* Set the device addresses */

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
        nrf24_powerUpRx();
        	_delay_ms(200);
  if(nrf24_dataReady())
  {
	   nrf24_getData(rx_arr);
	   if (count==0)
	   {
		nrf24_tx_address(tx_addressNODE);
		nrf24_send(rx_arr);
        while(nrf24_isSending());
        count=1 ;
	   }
	   else if (count==1)
	   {
		   nrf24_tx_address(tx_addressCOR);
		   nrf24_send(rx_arr);
		   while(nrf24_isSending());
		   count=0 ;
	   }
  }
        /* Wait for transmission to end */


		 /* Optionally, go back to RX mode ... */


    }
}
/* ------------------------------------------------------------------------- */
void Auto_ACK()
{


while(counter<mx_retransmetion)
{
	nrf24_powerUpRx();
	_delay_ms(200);

		if(nrf24_dataReady())
		{
			nrf24_getData(rx_arr);

			if(rx_arr[0]==1)
			{
				q++;
				counter=0;
				break ;
			}
			else
			{
				counter++ ;
				nrf24_send(data_array);
				 while(nrf24_isSending());
			}

		}
		else
		{
			counter++ ;
			nrf24_send(data_array);
			   while(nrf24_isSending());
		}


}

if(counter==15)
       	flag=1 ;
}
