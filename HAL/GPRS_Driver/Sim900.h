#ifndef _SIM900_
#define _SIM900_

#define  AT_RESP_ERR_NO_RESP	-1  // no response
#define  AT_RESP_ERR_DIF_RESP	 0	// response_string is different from the actual response
#define  AT_RESP_OK				 1  // response_string was included in the response
#define COMM_BUF_LEN        200

#define GSM_ON              0 // connect GSM Module turn ON to pin 77
#define GSM_RESET           1 // connect GSM Module RESET to pin 35

// some constants for the IsRxFinished() method
#define RX_NOT_STARTED      0
#define RX_ALREADY_STARTED  1

enum rx_state_enum
{
  RX_NOT_FINISHED = 0,      // not finished yet
  RX_FINISHED,              // finished, some character was received
  RX_FINISHED_STR_RECV,     // finished and expected string received
  RX_FINISHED_STR_NOT_RECV, // finished, but expected string not received
  RX_TMOUT_ERR,             // finished, no character received
                            // initial communication tmout occurred
  RX_LAST_ITEM
};
enum comm_line_status_enum
{
  // CLS like CommunicationLineStatus
  CLS_FREE,   // line is free - not used by the communication and can be used
  CLS_ATCMD,  // line is used by AT commands, includes also time for response
  CLS_DATA,   // for the future - line is used in the CSD or GPRS communication
  CLS_LAST_ITEM
};

enum GSM_st_e { ERROR, IDLE, READY, ATTACHED, TCPSERVERWAIT, TCPCONNECTEDSERVER, TCPCONNECTEDCLIENT };
uint8_t comm_buf[COMM_BUF_LEN+1];  // communication buffer +1 for 0x00 termination
int _status;
uint8_t comm_line_status;

// variables connected with communication buffer

   uint8_t *p_comm_buf;               // pointer to the communication buffer
   uint8_t comm_buf_len;              // num. of characters in the buffer
   uint8_t rx_state;                  // internal state of rx state machine
   uint16_t start_reception_tmout; // max tmout for starting reception
   uint16_t interchar_tmout;       // previous time in msec.
   unsigned long prev_time;        // previous time in msec.

extern void SetCommLineStatus(uint8_t new_status);
extern uint8_t GetCommLineStatus(void);
extern void setStatus(int status);
				

extern int begin(long baud_rate);

extern uint8_t readSMS(char* msg, int msglength, char* number, int nlength);

extern uint8_t IsStringReceived(char const *compare_string);


extern uint8_t WaitResp2(uint16_t start_comm_tmout, uint16_t max_interchar_tmout,
	char const *expected_resp_string);
	
extern uint8_t WaitResp(uint16_t start_comm_tmout, uint16_t max_interchar_tmout);

extern char SendATCmdWaitResp(char const *AT_cmd_string,
	uint16_t start_comm_tmout, uint16_t max_interchar_tmout,
	char const *response_string,
	uint8_t no_of_attempts);
	
extern void RxInit(uint16_t start_comm_tmout, uint16_t max_interchar_tmout);
extern char SendSMS(char *number_str, char *message_str);

extern int attachGPRS(char* domain, char* dom1, char* dom2);

extern void SimpleWrite(char *comm);
extern void SimpleWriteln(char *comm);
extern int read(char* result, int resultlength);

extern int httpGET(const char* server, int port, const char* path, char* result, int resultlength);

extern uint8_t IsRxFinished(void);

extern int dettachGPRS();

extern int httpPOST(const char* server, int port, const char* path, const char* parameters, char* result, int resultlength);

#endif
