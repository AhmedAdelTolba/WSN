#include "types.h"
#include "string.h"
#include "util.h"
#include "delay.h"
#include "Sim900.h"
#include "timer1.h"
#include "UART_interface.h"

extern void SetCommLineStatus(uint8_t new_status) {comm_line_status = new_status;}
extern uint8_t GetCommLineStatus(void) {return comm_line_status;}
extern void setStatus(int status) { _status = status; }

extern char SendATCmdWaitResp(char const *AT_cmd_string,
                uint16_t start_comm_tmout, uint16_t max_interchar_tmout,
                char const *response_string,
                uint8_t no_of_attempts)
		{
			uint8_t status;
			char ret_val = AT_RESP_ERR_NO_RESP;
			uint8_t i;
			 for (i = 0; i < no_of_attempts; i++) {
				 if(i>0)
				 {
					 DELAY_voidDELAY(500);
				 }
				 uart_puts(AT_cmd_string);
				 uart_puts("/n/r");
				 status=WaitResp(start_comm_tmout,max_interchar_tmout);
				 if(status==RX_FINISHED)
				 {
				      // something was received but what was received?
				      // ---------------------------------------------
					 if(IsStringReceived(response_string))
					 {
						 ret_val=AT_RESP_OK;
						 break;
					 }
					 else
					 {
						 ret_val=AT_RESP_ERR_DIF_RESP;
					 }
				 }
				 else
				 {
					 //nothing was recieved
					 ret_val=AT_RESP_ERR_NO_RESP;
				 }
			 }
			 WaitResp(1000,5000);
			 return(ret_val);
		}
				

extern int begin(long baud_rate)
{
	int response=-1;
	int cont=0;
	uint8_t norep=true;
	uint8_t turnedON=false;
	SetCommLineStatus(CLS_ATCMD);
	p_comm_buf = &comm_buf[0];
	setStatus(IDLE);
	// if no-reply we turn to turn on the module

	if (AT_RESP_OK == SendATCmdWaitResp("AT", 500, 100, "OK", 5)){
			turnedON=true;
				norep=false;
		}
	if (AT_RESP_ERR_DIF_RESP == SendATCmdWaitResp("AT", 500, 100, "OK", 5)&&!turnedON)
	{		//check OK

	DELAY_voidDELAY(100);

	if (AT_RESP_OK == SendATCmdWaitResp("AT", 500, 100, "OK", 5))
	{
					uart_puts("AT+IPR=");
					uart_puts(baud_rate);
					uart_puts("\r"); // send <CR>
					DELAY_voidDELAY(500);
					DELAY_voidDELAY(100);
					turnedON=true;
				}
	// communication line is not used yet = free
	SetCommLineStatus(CLS_FREE);
	p_comm_buf=&comm_buf[0];
	return 1;
	}
	else
	{
	return 0;
	}

}

//extern uint8_t readSMS(char* msg, int msglength, char* number, int nlength){}

extern uint8_t IsStringReceived(char const *compare_string)
{
	char *ch;
	uint8_t ret_val=0;
	if(comm_buf_len)
		{
		ch=strstr((char *)comm_buf, compare_string);
		  if (ch != '\0') {
		      ret_val = 1;
		    }
		  else
		  {

		  }
		}
	else
	{

	}
	return ret_val;
	}



extern uint8_t WaitResp2(uint16_t start_comm_tmout, uint16_t max_interchar_tmout,
	char const *expected_resp_string)
{
	uint8_t status;
	uint8_t ret_val;
	RxInit(start_comm_tmout,max_interchar_tmout);
	do{
		status=IsRxFinished();
	}while(status == RX_NOT_FINISHED);

	if(status == RX_FINISHED)
		{
	    // something was received but what was received?
	    // ---------------------------------------------

	    if(IsStringReceived(expected_resp_string)) {
	      // expected string was received
	      // ----------------------------
	      ret_val = RX_FINISHED_STR_RECV;

	    }
	    else {
		ret_val = RX_FINISHED_STR_NOT_RECV;
		}
	  }
	  else {
	    // nothing was received
	    // --------------------
	    ret_val = RX_TMOUT_ERR;
	  }
	  return (ret_val);
	}

extern uint8_t WaitResp(uint16_t start_comm_tmout, uint16_t max_interchar_tmout)
{
	uint8_t status;
RxInit(start_comm_tmout, max_interchar_tmout);
// wait until response is not finished
do {
  status = IsRxFinished();
} while (status == RX_NOT_FINISHED);
return (status);
}
	
extern void SimpleWrite(char *comm)
{
	uart_puts(comm);
}
extern void SimpleWriteln(char *comm)
{
	uart_puts(comm);
	uart_puts("\r");
}
extern int read(char* result, int resultlength)
{	char temp;
int i=0;
for(i=0; i<resultlength;i++){
	temp=uart_read();
	if(temp>0){
				result[i]=temp;
			}
	}
return i;
}

uint8_t IsRxFinished(void)
{
  uint8_t num_of_bytes;
  uint8_t ret_val = RX_NOT_FINISHED;  // default not finished

  // Rx state machine
  // ----------------

  if (rx_state == RX_NOT_STARTED) {
    // Reception is not started yet - check tmout
    if (uart_available()) {
      // still no character received => check timeout

      if ((unsigned long)(millis() - prev_time) >= start_reception_tmout) {
        // timeout elapsed => GSM module didn't start with response
        // so communication is takes as finished
		/*
			#ifdef DEBUG_GSMRX
				DebugPrint("\r\nDEBUG: RECEPTION TIMEOUT", 0);
			#endif
		*/
        comm_buf[comm_buf_len] = 0x00;
        ret_val = RX_TMOUT_ERR;
      }
    }
    else {
      // at least one character received => so init inter-character
      // counting process again and go to the next state
      prev_time = millis(); // init tmout for inter-character space
      rx_state = RX_ALREADY_STARTED;
    }
  }

  if (rx_state == RX_ALREADY_STARTED) {
    // Reception already started
    // check new received bytes
    // only in case we have place in the buffer
    num_of_bytes = uart_available();
    // if there are some received bytes postpone the timeout
    if (num_of_bytes) prev_time = millis();

    // read all received bytes
    while (num_of_bytes) {
      num_of_bytes--;
      if (comm_buf_len < COMM_BUF_LEN) {
        // we have still place in the GSM internal comm. buffer =>
        // move available bytes from circular buffer
        // to the rx buffer
        *p_comm_buf = uart_read();

        p_comm_buf++;
        comm_buf_len++;
        comm_buf[comm_buf_len] = 0x00;  // and finish currently received characters
                                        // so after each character we have
                                        // valid string finished by the 0x00
      }
      else {
        // comm buffer is full, other incoming characters
        // will be discarded
        // but despite of we have no place for other characters
        // we still must to wait until
        // inter-character tmout is reached

        // so just readout character from circular RS232 buffer
        // to find out when communication id finished(no more characters
        // are received in inter-char timeout)
        uart_read();
      }
    }

    // finally check the inter-character timeout
	/*
	#ifdef DEBUG_GSMRX

			DebugPrint("\r\nDEBUG: intercharacter", 0);
<			Serial.print((unsigned long)(millis() - prev_time));
			DebugPrint("\r\nDEBUG: interchar_tmout\r\n", 0);
			Serial.print(interchar_tmout);


	#endif
	*/
    if ((unsigned long)(millis() - prev_time) >= interchar_tmout) {
      // timeout between received character was reached
      // reception is finished
      // ---------------------------------------------

		/*
	  	#ifdef DEBUG_GSMRX

			DebugPrint("\r\nDEBUG: OVER INTER TIMEOUT", 0);
		#endif
		*/
      comm_buf[comm_buf_len] = 0x00;  // for sure finish string again
                                      // but it is not necessary
      ret_val = RX_FINISHED;
    }
  }


  return (ret_val);
}
void RxInit(uint16_t start_comm_tmout, uint16_t max_interchar_tmout)
{
  rx_state = RX_NOT_STARTED;
  start_reception_tmout = start_comm_tmout;
  interchar_tmout = max_interchar_tmout;
  prev_time = millis();
  comm_buf[0] = 0x00; // end of string
  p_comm_buf = &comm_buf[0];
  comm_buf_len = 0;
}
char SendSMS(char *number_str, char *message_str)
{
	  char ret_val = -1;
	  uint8_t i;
	  char end[2];
	  end[0]=0x1a;
	  end[1]='\0';

	  for (i = 0; i < 1; i++) {
		  SimpleWrite("AT+CMGS=\"");
		  SimpleWrite(number_str);
		  SimpleWriteln("\"");
		 // DELAY_voidDELAY(5000);
		  if (RX_FINISHED_STR_RECV == WaitResp2(1000, 500, ">"))
		  {
		      SimpleWrite(message_str);
		      SimpleWriteln(end);
		      if (RX_FINISHED_STR_RECV == WaitResp2(7000, 5000, "+CMGS")) {
		             // SMS was send correctly
		             ret_val = 1;

		             break;
		           }
		      else continue;
		  }
		  else {
		        // try again
		        continue;
		  	  }
	  }
	  SetCommLineStatus(CLS_FREE);
	    return (ret_val);
}

//int attachGPRS(char* domain, char* dom1, char* dom2){}

//int httpGET(const char* server, int port, const char* path, char* result, int resultlength){}

//int dettachGPRS(){}

//int httpPOST(const char* server, int port, const char* path, const char* parameters, char* result, int resultlength){}
