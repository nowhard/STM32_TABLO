#include "proto.h"
#include "channels.h"
#include "tablo.h"
#include "tablo_parser.h"

 extern struct Channel  channels[];//Р В РЎвЂўР В Р’В±Р В РЎвЂўР В Р’В±Р РЋРІР‚В°Р В Р’ВµР В Р вЂ¦Р В Р вЂ¦Р В Р’В°Р РЋР РЏ Р РЋР С“Р РЋРІР‚С™Р РЋР вЂљР РЋРЎвЂњР В РЎвЂќР РЋРІР‚С™Р РЋРЎвЂњР РЋР вЂљР В Р’В° Р В РЎвЂќР В Р’В°Р В Р вЂ¦Р В Р’В°Р В Р’В»Р В РЎвЂўР В Р вЂ 
 extern struct tablo tab;//Р РЋР С“Р РЋРІР‚С™Р РЋР вЂљР РЋРЎвЂњР В РЎвЂќР РЋРІР‚С™Р РЋРЎвЂњР РЋР вЂљР В Р’В° Р РЋРІР‚С™Р В Р’В°Р В Р’В±Р В Р’В»Р В РЎвЂў

//typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
//-----------------------------------------------------------------------------------
uint8_t   DEV_NAME[DEVICE_NAME_LENGTH_SYM] ="<<TABLO>>"; //Р В РЎвЂ�Р В РЎпїЅР РЋР РЏ Р РЋРЎвЂњР РЋР С“Р РЋРІР‚С™Р РЋР вЂљР В РЎвЂўР В РІвЂћвЂ“Р РЋР С“Р РЋРІР‚С™Р В Р вЂ Р В Р’В°
uint8_t   NOTICE[DEVICE_DESC_MAX_LENGTH_SYM]="<-- GEOSPHERA_2013 -->";//Р В РЎвЂ”Р РЋР вЂљР В РЎвЂ�Р В РЎпїЅР В Р’ВµР РЋРІР‚РЋР В Р’В°Р В Р вЂ¦Р В РЎвЂ�Р В Р’Вµ
uint8_t   VERSION[DEVICE_VER_LENGTH_SYM] ="\x30\x30\x30\x30\x31";	// Р В Р вЂ Р В Р’ВµР РЋР вЂљР РЋР С“Р В РЎвЂ�Р РЋР РЏ Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР В РЎвЂ“Р РЋР вЂљР В Р’В°Р В РЎпїЅР В РЎпїЅР РЋРІР‚в„– Р В РЎСџР В РІР‚вЂќР В Р в‚¬	Р В Р вЂ¦Р В Р’Вµ Р В Р’В±Р В РЎвЂўР В Р’В»Р РЋР Р‰Р РЋРІвЂљВ¬Р В Р’Вµ 5 Р В Р’В±Р В Р’В°Р В РІвЂћвЂ“Р РЋРІР‚С™

uint8_t   ADRESS_DEV=0xF;

uint8_t   dev_desc_len=20;//Р В РўвЂ�Р В Р’В»Р В РЎвЂ�Р В Р вЂ¦Р В Р’В° Р В РЎвЂўР В РЎвЂ”Р В РЎвЂ�Р РЋР С“Р В Р’В°Р В Р вЂ¦Р В РЎвЂ�Р РЋР РЏ Р РЋРЎвЂњР РЋР С“Р РЋРІР‚С™Р РЋР вЂљР В РЎвЂўР В РІвЂћвЂ“Р РЋР С“Р РЋРІР‚С™Р В Р вЂ Р В Р’В°
//--------------------------------global variable------------------------------------

uint8_t   	recieve_count;//Р РЋР С“Р РЋРІР‚РЋР В Р’ВµР РЋРІР‚С™Р РЋРІР‚РЋР В РЎвЂ�Р В РЎвЂќ Р В РЎвЂ”Р РЋР вЂљР В РЎвЂ�Р В Р’ВµР В РЎпїЅР В Р вЂ¦Р В РЎвЂўР В РЎвЂ“Р В РЎвЂў Р В Р’В±Р РЋРЎвЂњР РЋРІР‚С›Р В Р’ВµР РЋР вЂљР В Р’В°
uint8_t  	transf_count;//Р РЋР С“Р РЋРІР‚РЋР В Р’ВµР РЋРІР‚С™Р РЋРІР‚РЋР В РЎвЂ�Р В РЎвЂќ Р В РЎвЂ”Р В Р’ВµР РЋР вЂљР В Р’ВµР В РўвЂ�Р В Р’В°Р В Р вЂ Р В Р’В°Р В Р’ВµР В РЎпїЅР РЋРІР‚в„–Р РЋРІР‚В¦ Р В Р’В±Р В Р’В°Р В РІвЂћвЂ“Р РЋРІР‚С™Р В РЎвЂўР В Р вЂ 
uint8_t  	buf_len;//Р В РўвЂ�Р В Р’В»Р В РЎвЂ�Р В Р вЂ¦Р В Р’В° Р В РЎвЂ”Р В Р’ВµР РЋР вЂљР В Р’ВµР В РўвЂ�Р В Р’В°Р В Р вЂ Р В Р’В°Р В Р’ВµР В РЎпїЅР В РЎвЂўР В РЎвЂ“Р В РЎвЂў Р В Р’В±Р РЋРЎвЂњР РЋРІР‚С›Р В Р’ВµР РЋР вЂљР В Р’В°

//------------------------Р РЋРІР‚С›Р В Р’В»Р В Р’В°Р В РЎвЂ“Р В РЎвЂ� Р В РЎвЂўР РЋРІвЂљВ¬Р В РЎвЂ�Р В Р’В±Р В РЎвЂўР В РЎвЂќ--------------------------------
uint8_t   crc_n_ERR;	//Р В РЎвЂўР РЋРІвЂљВ¬Р В РЎвЂ�Р В Р’В±Р В РЎвЂќР В Р’В° Р РЋР С“rc
uint8_t   COMMAND_ERR;//Р В Р вЂ¦Р В Р’ВµР В РЎвЂ”Р В РЎвЂўР В РўвЂ�Р В РўвЂ�Р В Р’ВµР РЋР вЂљР В Р’В¶Р В РЎвЂ�Р В Р вЂ Р В Р’В°Р В Р’ВµР В РЎпїЅР В Р’В°Р РЋР РЏ Р В РЎвЂќР В РЎвЂўР В РЎпїЅР В Р’В°Р В Р вЂ¦Р В РўвЂ�Р В Р’В°



uint8_t   CUT_OUT_NULL;//Р РЋРІР‚С›Р В Р’В»Р В Р’В°Р В РЎвЂ“-Р В Р вЂ Р РЋРІР‚в„–Р РЋР вЂљР В Р’ВµР В Р’В·Р В Р’В°Р В Р’ВµР В РЎпїЅ 0 Р В РЎвЂ”Р В РЎвЂўР РЋР С“Р В Р’В»Р В Р’Вµ 0xD7
uint8_t   frame_len=0;//Р В РўвЂ�Р В Р’В»Р В РЎвЂ�Р В Р вЂ¦Р В Р’В° Р В РЎвЂќР В Р’В°Р В РўвЂ�Р РЋР вЂљР В Р’В°, Р В РЎвЂќР В РЎвЂўР РЋРІР‚С™Р В РЎвЂўР РЋР вЂљР РЋРЎвЂњР РЋР вЂ№ Р В Р вЂ Р РЋРІР‚в„–Р РЋРІР‚С™Р В Р’В°Р РЋР С“Р В РЎвЂќР В РЎвЂ�Р В Р вЂ Р В Р’В°Р В Р’ВµР В РЎпїЅ Р В РЎвЂ�Р В Р’В· Р РЋРІвЂљВ¬Р В Р’ВµР РЋР С“Р РЋРІР‚С™Р В РЎвЂўР В РЎвЂ“Р В РЎвЂў Р В Р’В±Р В Р’В°Р В РІвЂћвЂ“Р РЋРІР‚С™Р В Р’В° Р В РЎвЂќР В Р’В°Р В РўвЂ�Р РЋР вЂљР В Р’В°
//--------------------------------------------------------------------
//volatile  uint8_t    RecieveBuf[MAX_LENGTH_REC_BUF]={0} ; //Р В Р’В±Р РЋРЎвЂњР РЋРІР‚С›Р В Р’ВµР РЋР вЂљ Р В РЎвЂ”Р РЋР вЂљР В РЎвЂ�Р В Р вЂ¦Р В РЎвЂ�Р В РЎпїЅР В Р’В°Р В Р’ВµР В РЎпїЅР РЋРІР‚в„–Р РЋРІР‚В¦ Р В РўвЂ�Р В Р’В°Р В Р вЂ¦Р В Р вЂ¦Р РЋРІР‚в„–Р РЋРІР‚В¦
uint8_t    *RecieveBuf;
uint8_t    *TransferBuf;

//volatile uint8_t /*data*/   TransferBuf[MAX_LENGTH_TR_BUF] ; //Р В Р’В±Р РЋРЎвЂњР РЋРІР‚С›Р В Р’ВµР РЋР вЂљ Р В РЎвЂ”Р В Р’ВµР РЋР вЂљР В Р’ВµР В РўвЂ�Р В Р’В°Р В Р вЂ Р В Р’В°Р В Р’ВµР В РЎпїЅР РЋРІР‚в„–Р РЋРІР‚В¦ Р В РўвЂ�Р В Р’В°Р В Р вЂ¦Р В Р вЂ¦Р РЋРІР‚в„–Р РЋРІР‚В¦
//--------------------------------------------------------------------
uint8_t    STATE_BYTE=0xC0;//Р В Р’В±Р В Р’В°Р В РІвЂћвЂ“Р РЋРІР‚С™ Р РЋР С“Р В РЎвЂўР РЋР С“Р РЋРІР‚С™Р В РЎвЂўР РЋР РЏР В Р вЂ¦Р В РЎвЂ�Р РЋР РЏ Р РЋРЎвЂњР РЋР С“Р РЋРІР‚С™Р РЋР вЂљР В РЎвЂўР В РІвЂћвЂ“Р РЋР С“Р РЋРІР‚С™Р В Р вЂ Р В Р’В°



uint16_t fr_err=0;

uint8_t  symbol=0xFF;//Р В РЎвЂ”Р РЋР вЂљР В РЎвЂ�Р В Р вЂ¦Р РЋР РЏР РЋРІР‚С™Р РЋРІР‚в„–Р В РІвЂћвЂ“ Р РЋР С“Р В РЎвЂ�Р В РЎпїЅР В Р вЂ Р В РЎвЂўР В Р’В»

uint8_t	proto_type=PROTO_TYPE_NEW;//Р РЋРІР‚С™Р В РЎвЂ�Р В РЎвЂ” Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋРІР‚С™Р В РЎвЂўР В РЎвЂќР В РЎвЂўР В Р’В»Р В Р’В°

const uint8_t standby_frame[256]={0x3A,0x7C,0x5B,0x00,0x2E,0x2E,0x2E,0x5D,0x5B,0x01,0x2E,0x2E,0x2E,0x5D,0x5B,0x02,0x2E,0x2E,0x2E,0x5D,0x5B,0x03,0x2E,0x2E,0x2E,0x5D,0x5B,0x04,0x2E,0x2E,0x2E,0x5D,0x5B,0x05,0x2E,0x2E,0x2E,0x5D,0x5B,0x06,0x2E,0x2E,0x2E,0x5D,0x5B,0x07,0x2E,0x2E,0x2E,0x5D,0x5B,0x08,0x2E,0x2E,0x2E,0x2E,0x2E,0x5D,0x5B,0x0A,0x2E,0x2E,0x2E,0x2E,0x2E,0x5D,0x5B,0x0B,0x2E,0x2E,0x2E,0x5D,0x5B,0x0C,0x2E,0x2E,0x2E,0x2E,0x2E,0x5D,0x5B,0x0D,0x00,0x00,0x00,0xFF,0x5D,0x5B,0x0E,0x00,0x00,0x00,0xFF,0x5D,0x5B,0x0F,0x00,0x00,0x00,0xFF,0x5D,0x5B,0x10,0x00,0x00,0x00,0xFF,0x5D,0x5B,0x12,0x00,0x00,0x00,0xFF,0x5D,0x5B,0x13,0x00,0x00,0x00,0xFF,0x5D,0x5B,0x2A,0x07,0x5D};
//-----------------------------------------------------------------------------------
union
{
	float result_float;
	uint8_t result_char[4];
}
sym_8_to_float;

xSemaphoreHandle xProtoSemaphore;

void USART6_IRQHandler (void)
{
 	static portBASE_TYPE xHigherPriorityTaskWoken;
 	  xHigherPriorityTaskWoken = pdFALSE;

//

 	if(USART_GetITStatus(USART6, USART_IT_RXNE) != RESET)
   	{
 		USART_ClearITPendingBit(USART6, USART_IT_RXNE);

   		symbol=USART_ReceiveData (USART6);

   		if(recieve_count>MAX_LENGTH_REC_BUF)
   		{
   			recieve_count=0x0;
   			return;
   		}

switch(proto_type)
{
	case PROTO_TYPE_OLD:
	{
		if(symbol==':')
		{
			recieve_count=0x0;
		}

		tab.tablo_proto_buf[recieve_count]=symbol;
		recieve_count++;

		if(recieve_count>1)
		{
			if(tab.tablo_proto_buf[1]==(recieve_count-2))//
			{
				 USART_ITConfig(USART6, USART_IT_RXNE , DISABLE);
				xSemaphoreGiveFromISR( xProtoSemaphore, &xHigherPriorityTaskWoken );

  				 if( xHigherPriorityTaskWoken != pdFALSE )
  				 {
  					portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
  				 }
			}
		}
	}
	break;

	case PROTO_TYPE_NEW:
	{
	//--------------------------
   	    if(recieve_count<6)
   		{
   	    		switch(recieve_count)
   				{
   					case  0:   //
   					{
   	 				 	 if(symbol!=0x00)
   						 {
   	 				 		recieve_count=0;

   	 				 	fr_err++;
   							//return;
   						 }
   					}
   					break;

   					case 1:	 //
   					{
   						 if(symbol!=0xD7)
   						 {
   							recieve_count=0;

   							//return;
   						 }
   					}
   					break;

   					case 2:	 //
   					{
   					 	 if(symbol!=0x29)
   						 {
   					 		recieve_count=0;

   							//return;
   						 }
   					}
   					break;

   					case 3:	//
   					{
   						if(symbol!=ADRESS_DEV)//
   						{
   							recieve_count=0;

   							//return;
   						}
   					}
   					break;

   					default:  //
   					{
   					}
   					break;
   				}

   			RecieveBuf[recieve_count]=symbol;//
   			recieve_count++;//

   			if(recieve_count==6)
   			{
   				frame_len=RecieveBuf[recieve_count-1]; //
   			}
   		}
   //---------------------------------------------------------
   		else  //
   		{
   			switch(symbol)//
   			{
   				case 0xD7:
   				{
   					CUT_OUT_NULL=1;	//
   					RecieveBuf[recieve_count]=symbol;
   					recieve_count++;

   				}
   				break;

   				case 0x0:
   				{
   					if(!CUT_OUT_NULL)  //
   					{
   						RecieveBuf[recieve_count]=symbol;
   						recieve_count++;
   					}
   					else //
   					{
   						CUT_OUT_NULL=0;
   					}
   				}
   				break;

   				default:  //
   				{
   					CUT_OUT_NULL=0;
   					RecieveBuf[recieve_count]=symbol;
   					recieve_count++;
   				}
   				break;
   			}

   			if(recieve_count>=frame_len+6)//
   			{
   				 USART_ITConfig(USART6, USART_IT_RXNE , DISABLE);

   				 xSemaphoreGiveFromISR( xProtoSemaphore, &xHigherPriorityTaskWoken );

   				 if( xHigherPriorityTaskWoken != pdFALSE )
   				 {
   					portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
   				 }
   			}
   		}
	}
}

   	}
   //-----------------------------------------------------------------------------------------------------------------
   	if(USART_GetITStatus(USART6, USART_IT_TC) != RESET)
   	{

   		USART_ClearITPendingBit(USART6, USART_IT_TC);//Р В РЎвЂўР РЋРІР‚РЋР В РЎвЂ�Р РЋРІР‚В°Р В Р’В°Р В Р’ВµР В РЎпїЅ Р В РЎвЂ”Р РЋР вЂљР В РЎвЂ�Р В Р’В·Р В Р вЂ¦Р В Р’В°Р В РЎвЂќ Р В РЎвЂ”Р РЋР вЂљР В Р’ВµР РЋР вЂљР РЋРІР‚в„–Р В Р вЂ Р В Р’В°Р В Р вЂ¦Р В РЎвЂ�Р РЋР РЏ

   		if(transf_count<buf_len)
   		{
   			if(transf_count<3)//Р В РЎвЂ”Р В Р’ВµР РЋР вЂљР В Р’ВµР В РўвЂ�Р В Р’В°Р В Р’ВµР В РЎпїЅ Р В Р’В·Р В Р’В°Р В РЎвЂ“Р В РЎвЂўР В Р’В»Р В РЎвЂўР В Р вЂ Р В РЎвЂўР В РЎвЂќ
   			{
   				//USART_SendData(USART6,TransferBuf[transf_count]);
   				USART6->DR =TransferBuf[transf_count];
   				transf_count++;
   			}
   			else   //Р РЋРІР‚С™Р В Р’ВµР В Р’В»Р В РЎвЂў...   Р В РЎвЂ”Р В РЎвЂўР В РўвЂ�Р РЋР С“Р РЋРІР‚С™Р В Р’В°Р В Р вЂ Р В Р’В»Р РЋР РЏР В Р’ВµР В РЎпїЅ 0 Р В РЎвЂ”Р В РЎвЂўР РЋР С“Р В Р’В»Р В Р’Вµ 0xD7
   			{
   					if(CUT_OUT_NULL==0)
   					{
   						if(TransferBuf[transf_count]==(uint8_t)0xD7)//Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР В Р вЂ Р В Р’ВµР РЋР вЂљР В РЎвЂ�Р В РЎпїЅ, Р РЋР РЉР РЋРІР‚С™Р В РЎвЂў  ,0xD7 Р В РЎвЂ�Р В Р’В»Р В РЎвЂ� Р В РўвЂ�Р РЋР вЂљР РЋРЎвЂњР В РЎвЂ“Р В РЎвЂўР В Р’Вµ
   						{
   							CUT_OUT_NULL=0x1;
   						}
   						//USART_SendData(USART6,TransferBuf[transf_count]);
   						USART6->DR =TransferBuf[transf_count];
   						transf_count++;
   					}
   					else
   					{
   						//USART_SendData(USART6,(uint8_t)0x0);
   						USART6->DR =(uint8_t)0x0 ;
   						CUT_OUT_NULL=0;
   					}
   			}
   		}
   		else
   		{
   			transf_count=0;		//Р В РЎвЂўР В Р’В±Р В Р вЂ¦Р РЋРЎвЂњР В Р’В»Р РЋР РЏР В Р’ВµР В РЎпїЅ Р РЋР С“Р РЋРІР‚РЋР В Р’ВµР РЋРІР‚С™Р РЋРІР‚РЋР В РЎвЂ�Р В РЎвЂќ
   			recieve_count=0;

   			CUT_OUT_NULL=0;
   			 USART_ITConfig(USART6, USART_IT_RXNE , ENABLE);
   		}

   	}
   	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}
//------------------------------------------------------------------------------
void Proto_Init(void) //
{

	  /* Enable GPIOC clock */
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	  /* Enable USART6 clock */
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	  GPIO_InitTypeDef GPIO_InitStructure;
	  /* Configure port as pushpull, 50MHz and No pull up & down  */
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	  /* Configure PC6 as alternate function  */
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);

	  /* Configure PC7 as alternate function  */
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;
	  GPIO_Init(GPIOC, &GPIO_InitStructure);

	  /* Connect PC6 to USART6_Tx*/
	  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);

	  /* Connect PC7 to USART6_Rx*/
	  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);






	USART_InitTypeDef USART_InitStructure;

		USART_DeInit(USART6);

	USART_InitStructure.USART_BaudRate = 57600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART6, &USART_InitStructure);

	USART_ClearFlag(USART6, USART_FLAG_CTS | USART_FLAG_LBD  | USART_FLAG_TC  | USART_FLAG_RXNE );

	USART_ITConfig(USART6, USART_IT_TC, ENABLE);
	USART_ITConfig(USART6, USART_IT_RXNE , ENABLE);

	USART_Cmd(USART6, ENABLE);
	NVIC_EnableIRQ(USART6_IRQn);

	//------------------------Р РЋРІР‚С›Р В Р’В»Р В Р’В°Р В РЎвЂ“Р В РЎвЂ� Р В РЎвЂўР РЋРІвЂљВ¬Р В РЎвЂ�Р В Р’В±Р В РЎвЂўР В РЎвЂќ--------------------------------

	crc_n_ERR=0x0;	//Р В РЎвЂўР РЋРІвЂљВ¬Р В РЎвЂ�Р В Р’В±Р В РЎвЂќР В Р’В° crc_n
	COMMAND_ERR=0x0;//Р В Р вЂ¦Р В Р’ВµР В РЎвЂ”Р В РЎвЂўР В РўвЂ�Р В РўвЂ�Р В Р’ВµР РЋР вЂљР В Р’В¶Р В РЎвЂ�Р В Р вЂ Р В Р’В°Р В Р’ВµР В РЎпїЅР В Р’В°Р РЋР РЏ Р В РЎвЂќР В РЎвЂўР В РЎпїЅР В Р’В°Р В Р вЂ¦Р В РўвЂ�Р В Р’В°

	//TransferBuf=&RecieveBuf[0];	 //Р В Р’В±Р РЋРЎвЂњР РЋРІР‚С›Р В Р’ВµР РЋР вЂљ Р В РЎвЂўР РЋРІР‚С™Р В Р вЂ Р В Р’ВµР РЋРІР‚С™Р В Р’В° =Р В Р’В±Р РЋРЎвЂњР РЋРІР‚С›Р В Р’ВµР РЋР вЂљ Р В Р’В·Р В Р’В°Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“Р В Р’В°
	TransferBuf=&tab.uart_buf;
	RecieveBuf= &tab.uart_buf;
	ChannelsInit();


	//Restore_Dev_Address_Desc();

	recieve_count=0x0;//Р РЋР С“Р РЋРІР‚РЋР В Р’ВµР РЋРІР‚С™Р РЋРІР‚РЋР В РЎвЂ�Р В РЎвЂќ Р В Р’В±Р РЋРЎвЂњР РЋРІР‚С›Р В Р’ВµР РЋР вЂљР В Р’В° Р В РЎвЂ”Р РЋР вЂљР В РЎвЂ�Р В Р’ВµР В РЎпїЅР В Р’В°
	transf_count=0x0;//Р РЋР С“Р РЋРІР‚РЋР В Р’ВµР РЋРІР‚С™Р РЋРІР‚РЋР В РЎвЂ�Р В РЎвЂќ Р В РЎвЂ”Р В Р’ВµР РЋР вЂљР В Р’ВµР В РўвЂ�Р В Р’В°Р В Р вЂ Р В Р’В°Р В Р’ВµР В РЎпїЅР РЋРІР‚в„–Р РЋРІР‚В¦ Р В Р’В±Р В Р’В°Р В РІвЂћвЂ“Р РЋРІР‚С™Р В РЎвЂўР В Р вЂ 
	buf_len=0x0;//Р В РўвЂ�Р В Р’В»Р В РЎвЂ�Р В Р вЂ¦Р В Р’В° Р В РЎвЂ”Р В Р’ВµР РЋР вЂљР В Р’ВµР В РўвЂ�Р В Р’В°Р В Р вЂ Р В Р’В°Р В Р’ВµР В РЎпїЅР В РЎвЂўР В РЎвЂ“Р В РЎвЂў Р В Р’В±Р РЋРЎвЂњР РЋРІР‚С›Р В Р’ВµР РЋР вЂљР В Р’В°
	//DE_RE=0;//Р В Р’В»Р В РЎвЂ�Р В Р вЂ¦Р В РЎвЂ�Р РЋР РЏ Р В Р вЂ¦Р В Р’В° Р В РЎвЂ”Р РЋР вЂљР В РЎвЂ�Р В Р’ВµР В РЎпїЅ
	CUT_OUT_NULL=0;

	 xTaskCreate(ProtoProcess,(signed char*)"PROTO",128,NULL, tskIDLE_PRIORITY + 1, NULL);

	vSemaphoreCreateBinary( xProtoSemaphore );
	return;
}
//-----------------------------------------------------------------------------
uint8_t Send_Info(void) //using 0    //Р В РЎвЂ”Р В РЎвЂўР РЋР С“Р РЋРІР‚в„–Р В Р’В»Р В РЎвЂќР В Р’В° Р В РЎвЂ�Р В Р вЂ¦Р РЋРІР‚С›Р В РЎвЂўР РЋР вЂљР В РЎпїЅР В Р’В°Р РЋРІР‚В Р В РЎвЂ�Р В РЎвЂ� Р В РЎвЂўР В Р’В± Р РЋРЎвЂњР РЋР С“Р РЋРІР‚С™Р РЋР вЂљР В РЎвЂўР В РІвЂћвЂ“Р РЋР С“Р РЋРІР‚С™Р В Р вЂ Р В Р’Вµ
{
		uint8_t    i=0;

	   //Р В Р’В·Р В Р’В°Р В РЎвЂ“Р В РЎвЂўР В Р’В»Р В РЎвЂўР В Р вЂ Р В РЎвЂўР В РЎвЂќ Р В РЎвЂќР В Р’В°Р В РўвЂ�Р РЋР вЂљР В Р’В°---
	   TransferBuf[0]=0x00;
	   TransferBuf[1]=0xD7;
	   TransferBuf[2]=0x29;
	   //------------------
	   TransferBuf[3]=ADRESS_DEV;  // Р В Р’В°Р В РўвЂ�Р РЋР вЂљР В Р’ВµР РЋР С“ Р РЋРЎвЂњР В Р’В·Р В Р’В»Р В Р’В°
	   TransferBuf[4]=GET_DEV_INFO_RESP;  // Р В РЎвЂќР В РЎвЂўР В РўвЂ� Р В РЎвЂўР В РЎвЂ”Р В Р’ВµР РЋР вЂљР В Р’В°Р РЋРІР‚В Р В РЎвЂ�Р В РЎвЂ�
	   TransferBuf[6]=STATE_BYTE;

	   for(i=0;i<20;i++)
	   {				  // Р В Р’В·Р В Р’В°Р В РЎвЂ”Р В РЎвЂ�Р РЋР С“Р РЋРІР‚в„–Р В Р вЂ Р В Р’В°Р В Р’ВµР В РЎпїЅ Р В Р вЂ¦Р В Р’В°Р В РЎвЂ�Р В РЎпїЅР В Р’ВµР В Р вЂ¦Р В РЎвЂўР В Р вЂ Р В Р’В°Р В Р вЂ¦Р В РЎвЂ�Р В Р’Вµ Р В РЎвЂ�Р В Р’В·Р В РўвЂ�Р В Р’ВµР В Р’В»Р В РЎвЂ�Р РЋР РЏ
			   if(i<DEVICE_NAME_LENGTH_SYM)
			   {
			     	TransferBuf[i+7]=DEV_NAME[i];
			   }
			   else
			   {
			   		TransferBuf[i+7]=0x00;
			   }
		}

	   for(i=0;i<5;i++)                   // Р В Р’В·Р В Р’В°Р В РЎвЂ”Р В РЎвЂ�Р РЋР С“Р РЋРІР‚в„–Р В Р вЂ Р В Р’В°Р В Р’ВµР В РЎпїЅ Р В Р вЂ Р В Р’ВµР РЋР вЂљР РЋР С“Р В РЎвЂ�Р РЋР вЂ№ Р В РЎСџР В РІР‚вЂќР В Р в‚¬
	   {
	       if(i<DEVICE_VER_LENGTH_SYM)
		   {
		    	 TransferBuf[i+27]=VERSION[i];
		   }
	   }

	   TransferBuf[32]=CHANNEL_NUMBER;		   // Р В РЎвЂќР В РЎвЂўР В Р’В»Р В РЎвЂ�Р РЋРІР‚РЋР В Р’ВµР РЋР С“Р РЋРІР‚С™Р В Р вЂ Р В РЎвЂў Р В РЎвЂќР В Р’В°Р В Р вЂ¦Р В Р’В°Р В Р’В»Р В РЎвЂўР В Р вЂ 

	   for(i=0;i<CHANNEL_NUMBER;i++)				   // Р В РўвЂ�Р В Р’В°Р В Р вЂ¦Р В Р вЂ¦Р РЋРІР‚в„–Р В Р’Вµ Р В РЎвЂ”Р В РЎвЂў Р В РЎвЂќР В Р’В°Р В Р вЂ¦Р В Р’В°Р В Р’В»Р РЋРЎвЂњ
       {
		  	TransferBuf[i*2+33]=((channels[i].settings.set.type)<<4)|channels[i].settings.set.modific; // Р В Р’В±Р В Р’В°Р В РІвЂћвЂ“Р РЋРІР‚С™ Р В РўвЂ�Р В Р’В°Р В Р вЂ¦Р В Р вЂ¦Р РЋРІР‚в„–Р РЋРІР‚В¦
		  	TransferBuf[i*2+33+1]=0x00;							// Р РЋР вЂљР В Р’ВµР В Р’В·Р В Р’ВµР РЋР вЂљР В Р вЂ  Р В Р’В±Р В Р’В°Р В РІвЂћвЂ“Р РЋРІР‚С™
	   }
	   for(i=0;i<dev_desc_len;i++)					// Р В Р’В·Р В Р’В°Р В РЎвЂ”Р В РЎвЂ�Р РЋР С“Р РЋРІР‚в„–Р В Р вЂ Р В Р’В°Р В Р’ВµР В РЎпїЅ Р В РЎвЂ”Р РЋР вЂљР В РЎвЂ�Р В РЎпїЅР В Р’ВµР РЋРІР‚РЋР В Р’В°Р В Р вЂ¦Р В РЎвЂ�Р В Р’Вµ
	   {
			 TransferBuf[i+33+CHANNEL_NUMBER*2]=NOTICE[i];
	   }

	   TransferBuf[5]=28+CHANNEL_NUMBER*2+dev_desc_len;			// Р В РЎвЂ”Р В РЎвЂўР В РўвЂ�Р РЋР С“Р РЋРІР‚РЋР В Р’ВµР РЋРІР‚С™ Р В РўвЂ�Р В Р’В»Р В РЎвЂ�Р В Р вЂ¦Р РЋРІР‚в„– Р В РўвЂ�Р В Р’В°Р В Р вЂ¦Р В Р вЂ¦Р РЋРІР‚в„–Р РЋРІР‚В¦
	   TransferBuf[33+CHANNEL_NUMBER*2+dev_desc_len]=CRC_Check(&TransferBuf[1],32+CHANNEL_NUMBER*2+dev_desc_len); // Р В РЎвЂ”Р В РЎвЂўР В РўвЂ�Р РЋР С“Р РЋРІР‚РЋР В Р’ВµР РЋРІР‚С™ Р В РЎвЂќР В РЎвЂўР В Р вЂ¦Р РЋРІР‚С™Р РЋР вЂљР В РЎвЂўР В Р’В»Р РЋР Р‰Р В Р вЂ¦Р В РЎвЂўР В РІвЂћвЂ“ Р РЋР С“Р РЋРЎвЂњР В РЎпїЅР В РЎпїЅР РЋРІР‚в„–

	return (34+CHANNEL_NUMBER*2+dev_desc_len);
}
//-----------------------------------------------------------------------------
uint8_t Node_Full_Init(void) //using 0 //Р В РЎвЂ”Р В РЎвЂўР В Р’В»Р В Р вЂ¦Р В Р’В°Р РЋР РЏ Р В РЎвЂ�Р В Р вЂ¦Р В РЎвЂ�Р РЋРІР‚В Р В РЎвЂ�Р В Р’В°Р В Р’В»Р В РЎвЂ�Р В Р’В·Р В Р’В°Р РЋРІР‚В Р В РЎвЂ�Р РЋР РЏ Р РЋРЎвЂњР В Р’В·Р В Р’В»Р В Р’В°
{
	return 0;
}
//-----------------------------------------------------------------------------
uint8_t Channel_List_Init(void) //using 0 //Р В РїС—Р…Р В Р вЂ¦Р В РЎвЂ�Р РЋРІР‚В Р В РЎвЂ�Р В Р’В°Р В Р’В»Р В РЎвЂ�Р В Р’В·Р В Р’В°Р РЋРІР‚В Р В РЎвЂ�Р РЋР РЏ Р РЋР С“Р В РЎвЂ”Р В РЎвЂ�Р РЋР С“Р В РЎвЂќР В Р’В° Р В РЎвЂќР В Р’В°Р В Р вЂ¦Р В Р’В°Р В Р’В»Р В РЎвЂўР В Р вЂ  Р РЋРЎвЂњР В Р’В·Р В Р’В»Р В Р’В° (Р В Р’В±Р В Р’ВµР В Р’В· Р В РЎвЂ”Р В РЎвЂўР РЋРІР‚С™Р В Р’ВµР РЋР вЂљР В РЎвЂ� Р В РўвЂ�Р В Р’В°Р В Р вЂ¦Р В Р вЂ¦Р РЋРІР‚в„–Р РЋРІР‚В¦);
{
	return 0;
}
//-----------------------------------------------------------------------------
uint8_t Channel_Get_Data(void) //using 0 //Р В РІР‚в„ўР РЋРІР‚в„–Р В РўвЂ�Р В Р’В°Р РЋРІР‚С™Р РЋР Р‰ Р В РўвЂ�Р В Р’В°Р В Р вЂ¦Р В Р вЂ¦Р РЋРІР‚в„–Р В Р’Вµ Р В РЎвЂ”Р В РЎвЂў Р В РЎвЂќР В Р’В°Р В Р вЂ¦Р В Р’В°Р В Р’В»Р В Р’В°Р В РЎпїЅ, Р РЋР С“Р В РЎвЂўР В РЎвЂ“Р В Р’В»Р В Р’В°Р РЋР С“Р В Р вЂ¦Р В РЎвЂў Р В Р’В°Р В Р’В±Р РЋР С“Р В РЎвЂўР В Р’В»Р РЋР вЂ№Р РЋРІР‚С™Р В Р вЂ¦Р В РЎвЂўР В РІвЂћвЂ“ Р В Р вЂ¦Р РЋРЎвЂњР В РЎпїЅР В Р’ВµР РЋР вЂљР В Р’В°Р РЋРІР‚В Р В РЎвЂ�Р В РЎвЂ�;
{
	return 0;
}
//-----------------------------------------------------------------------------
uint8_t  Channel_Set_Parameters(void) //using 0 //Р В Р в‚¬Р РЋР С“Р РЋРІР‚С™Р В Р’В°Р В Р вЂ¦Р В РЎвЂўР В Р вЂ Р В РЎвЂ�Р РЋРІР‚С™Р РЋР Р‰ Р В РЎвЂ”Р В Р’В°Р РЋР вЂљР В Р’В°Р В РЎпїЅР В Р’ВµР РЋРІР‚С™Р РЋР вЂљР РЋРІР‚в„– Р В РЎвЂ”Р В РЎвЂў Р В РЎвЂќР В Р’В°Р В Р вЂ¦Р В Р’В°Р В Р’В»Р В Р’В°Р В РЎпїЅ, Р РЋР С“Р В РЎвЂўР В РЎвЂ“Р В Р’В»Р В Р’В°Р РЋР С“Р В Р вЂ¦Р В РЎвЂў Р В Р’В°Р В Р’В±Р РЋР С“Р В РЎвЂўР В Р’В»Р РЋР вЂ№Р РЋРІР‚С™Р В Р вЂ¦Р В РЎвЂўР В РІвЂћвЂ“ Р В Р вЂ¦Р РЋРЎвЂњР В РЎпїЅР В Р’ВµР РЋР вЂљР В Р’В°Р РЋРІР‚В Р В РЎвЂ�Р В РЎвЂ�;
{
	 uint8_t   index=0, store_data=0;//i=0;
	 uint8_t len=0,i=0;

	   while(index<(RecieveBuf[5]-1))				   // Р В РўвЂ�Р В Р’В°Р В Р вЂ¦Р В Р вЂ¦Р РЋРІР‚в„–Р В Р’Вµ Р В РЎвЂ”Р В РЎвЂў Р В РЎвЂќР В Р’В°Р В Р вЂ¦Р В Р’В°Р В Р’В»Р В Р’В°Р В РЎпїЅ
	      {
			  	if(RecieveBuf[6+index]<CHANNEL_NUMBER)
			    {
					switch((RecieveBuf[6+index+1]>>4)&0xF)
					{
//					 		case CHNL_ADC://Р В РЎвЂ™Р В Р’В¦Р В РЎСџ
//							{
//								if((channels[RecieveBuf[6+index]].settings.set.modific!=RecieveBuf[6+index+1])||(channels[RecieveBuf[6+index]].settings.set.state_byte_1!=RecieveBuf[6+index+2]) || (channels[RecieveBuf[6+index]].settings.set.state_byte_2!=RecieveBuf[6+index+3]))
//								{
//									channels[RecieveBuf[6+index]].settings.set.state_byte_1=RecieveBuf[6+index+2];
//									channels[RecieveBuf[6+index]].settings.set.state_byte_2=RecieveBuf[6+index+3];
//									channels[RecieveBuf[6+index]].settings.set.modific	   =RecieveBuf[6+index+1]&0xF;
//									//debug----------------
//									//if(channels[RecieveBuf[6+index]].settings.set.modific==3)
////									{
////										GPIOC->ODR |= GPIO_Pin_8;
////									}
//									//-----------------
//									store_data=1;
//
//								}
//								index=index+1;
//							}
//							break;

//							case 0x2://Р РЋРІР‚РЋР В Р’В°Р РЋР С“Р РЋРІР‚С™Р В РЎвЂўР РЋРІР‚С™Р В РЎвЂўР В РЎпїЅР В Р’ВµР РЋР вЂљ
//							{
//							/*   if(channels[RecieveBuf[6+index]].settings.set.state_byte_1!=RecieveBuf[6+index+2])
//							   {
//							   		channels[RecieveBuf[6+index]].settings.set.state_byte_1=RecieveBuf[6+index+2];
//									store_data=1;
//							   }*/
//							}
//							break;

							case CHNL_DEV_STATE://Р РЋРЎвЂњР РЋР С“Р РЋРІР‚С™Р В Р’В°Р В Р вЂ¦Р В РЎвЂўР В Р вЂ Р В РЎвЂќР В Р’В° Р В РўвЂ�Р В РЎвЂ�Р РЋР С“Р В РЎвЂќР РЋР вЂљР В Р’ВµР РЋРІР‚С™Р В Р вЂ¦Р РЋРІР‚в„–Р РЋРІР‚В¦ Р В Р вЂ Р РЋРІР‚в„–Р В Р вЂ Р В РЎвЂўР В РўвЂ�Р В РЎвЂўР В Р вЂ 
							{
								switch((RecieveBuf[6+index+1])&0xF)
								{
									case CHNL_DEV_STATE_GET:
									{

									}
									break;

									case CHNL_DEV_STATE_SET:
									{
										tab.buz.buzzer_effect=(RecieveBuf[8+index]>>1)&0x7;
										tab.buz.buzzer_enable=RecieveBuf[8+index]&0x1;
										index+=CHNL_DEV_STATE_SET_LEN;
									}
									break;

									case CHNL_DEV_STATE_GET_SET:
									{

									}
									break;
								}
							}
							break;

							case CHNL_MEMORY://
							{
								for(i=0;i<RecieveBuf[8+index];i++)
								{
									tab.tablo_proto_buf[i]=RecieveBuf[8+index+i+1];
								}

								tablo_proto_parser(&tab.tablo_proto_buf);
								index+=RecieveBuf[6+2+index]+3;
							}
					}
				}
				else
				{
					return Request_Error(FR_UNATTENDED_CHANNEL);
				}
		  }
	   if(store_data)
	   {
	   		//Store_Channels_Data();	//Р РЋР С“Р В РЎвЂўР РЋРІР‚В¦Р РЋР вЂљР В Р’В°Р В Р вЂ¦Р В РЎвЂ�Р В РЎпїЅ Р В Р вЂ¦Р В Р’В°Р РЋР С“Р РЋРІР‚С™Р РЋР вЂљР В РЎвЂўР В РІвЂћвЂ“Р В РЎвЂќР В РЎвЂ� Р В РЎвЂќР В Р’В°Р В Р вЂ¦Р В Р’В°Р В Р’В»Р В РЎвЂўР В Р вЂ  Р В Р вЂ  Р В РЎСџР В РЎСџР В РІР‚вЂќР В Р в‚¬
		}
	   return Request_Error(FR_SUCCESFUL);
}
//-----------------------------------------------------------------------------
uint8_t Channel_Set_Order_Query(void) //using 0 //Р В РІР‚вЂќР В Р’В°Р В РўвЂ�Р В Р’В°Р РЋРІР‚С™Р РЋР Р‰ Р В РЎвЂ”Р В РЎвЂўР РЋР С“Р В Р’В»Р В Р’ВµР В РўвЂ�Р В РЎвЂўР В Р вЂ Р В Р’В°Р РЋРІР‚С™Р В Р’ВµР В Р’В»Р РЋР Р‰Р В Р вЂ¦Р В РЎвЂўР РЋР С“Р РЋРІР‚С™Р РЋР Р‰ Р В РЎвЂўР В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“Р В Р’В°;
{
	return 0;
}
//-----------------------------------------------------------------------------
uint8_t Channel_Get_Data_Order(void) //using 0 //Р В РІР‚в„ўР РЋРІР‚в„–Р В РўвЂ�Р В Р’В°Р РЋРІР‚С™Р РЋР Р‰ Р В РўвЂ�Р В Р’В°Р В Р вЂ¦Р В Р вЂ¦Р РЋРІР‚в„–Р В Р’Вµ Р В РЎвЂ”Р В РЎвЂў Р В РЎвЂќР В Р’В°Р В Р вЂ¦Р В Р’В°Р В Р’В»Р В Р’В°Р В РЎпїЅ, Р РЋР С“Р В РЎвЂўР В РЎвЂ“Р В Р’В»Р В Р’В°Р РЋР С“Р В Р вЂ¦Р В РЎвЂў Р В РЎвЂ”Р В РЎвЂўР РЋР С“Р В Р’В»Р В Р’ВµР В РўвЂ�Р В РЎвЂўР В Р вЂ Р В Р’В°Р РЋРІР‚С™Р В Р’ВµР В Р’В»Р РЋР Р‰Р В Р вЂ¦Р В РЎвЂўР РЋР С“Р РЋРІР‚С™Р В РЎвЂ� Р В РЎвЂўР В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“Р В Р’В°;
{
	return 0;
}
//-----------------------------------------------------------------------------
uint8_t Channel_Set_State(void) //using 0 //Р В Р в‚¬Р РЋР С“Р РЋРІР‚С™Р В Р’В°Р В Р вЂ¦Р В РЎвЂўР В Р вЂ Р В РЎвЂ�Р РЋРІР‚С™Р РЋР Р‰ Р РЋР С“Р В РЎвЂўР РЋР С“Р РЋРІР‚С™Р В РЎвЂўР РЋР РЏР В Р вЂ¦Р В РЎвЂ�Р РЋР РЏ Р В РЎвЂ”Р В РЎвЂў Р В РЎвЂќР В Р’В°Р В Р вЂ¦Р В Р’В°Р В Р’В»Р В Р’В°Р В РЎпїЅ, Р РЋР С“Р В РЎвЂўР В РЎвЂ“Р В Р’В»Р В Р’В°Р РЋР С“Р В Р вЂ¦Р В РЎвЂў Р В Р’В°Р В Р’В±Р РЋР С“Р В РЎвЂўР В Р’В»Р РЋР вЂ№Р РЋРІР‚С™Р В Р вЂ¦Р В РЎвЂўР В РІвЂћвЂ“ Р В Р вЂ¦Р РЋРЎвЂњР В РЎпїЅР В Р’ВµР РЋР вЂљР В Р’В°Р РЋРІР‚В Р В РЎвЂ�Р В РЎвЂ�;
{
	return 0;
}
//-----------------------------------------------------------------------------
uint8_t  Channel_Get_Data_Order_M2(void) //using 0 //Р В РІР‚в„ўР РЋРІР‚в„–Р В РўвЂ�Р В Р’В°Р РЋРІР‚С™Р РЋР Р‰ Р В РўвЂ�Р В Р’В°Р В Р вЂ¦Р В Р вЂ¦Р РЋРІР‚в„–Р В Р’Вµ Р В РЎвЂ”Р В РЎвЂў Р В РЎвЂќР В Р’В°Р В Р вЂ¦Р В Р’В°Р В Р’В»Р В Р’В°Р В РЎпїЅ, Р РЋР С“Р В РЎвЂўР В РЎвЂ“Р В Р’В»Р В Р’В°Р РЋР С“Р В Р вЂ¦Р В РЎвЂў Р В РЎвЂ”Р В РЎвЂўР РЋР С“Р В Р’В»Р В Р’ВµР В РўвЂ�Р В РЎвЂўР В Р вЂ Р В Р’В°Р РЋРІР‚С™Р В Р’ВµР В Р’В»Р РЋР Р‰Р В Р вЂ¦Р В РЎвЂўР РЋР С“Р РЋРІР‚С™Р В РЎвЂ� Р В РЎвЂўР В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“Р В Р’В°;
{
	return 0;
}
//-----------------------------------------------------------------------------
uint8_t Channel_Set_Reset_State_Flags(void) //using 0 //	Р В Р в‚¬Р РЋР С“Р РЋРІР‚С™Р В Р’В°Р В Р вЂ¦Р В РЎвЂўР В Р вЂ Р В РЎвЂќР В Р’В°/Р В Р Р‹Р В Р’В±Р РЋР вЂљР В РЎвЂўР РЋР С“ Р РЋРІР‚С›Р В Р’В»Р В Р’В°Р В РЎвЂ“Р В РЎвЂўР В Р вЂ  Р РЋР С“Р В РЎвЂўР РЋР С“Р РЋРІР‚С™Р В РЎвЂўР РЋР РЏР В Р вЂ¦Р В РЎвЂ�Р РЋР РЏ
{
	STATE_BYTE=0x40;
	return	Request_Error(FR_SUCCESFUL);//Р В РЎвЂўР РЋРІвЂљВ¬Р В РЎвЂ�Р В Р’В±Р В РЎвЂќР В РЎвЂ� Р В Р вЂ¦Р В Р’ВµР РЋРІР‚С™, Р В РЎвЂ”Р В РЎвЂўР В РўвЂ�Р РЋРІР‚С™Р В Р вЂ Р В Р’ВµР РЋР вЂљР В Р’В¶Р В РўвЂ�Р В Р’ВµР В Р вЂ¦Р В РЎвЂ�Р В Р’Вµ
}
//-----------------------------------------------------------------------------
uint8_t Channel_All_Get_Data(void) //using 0 //Р В РІР‚в„ўР РЋРІР‚в„–Р В РўвЂ�Р В Р’В°Р РЋРІР‚С™Р РЋР Р‰ Р В РЎвЂ�Р В Р вЂ¦Р РЋРІР‚С›Р В РЎвЂўР РЋР вЂљР В РЎпїЅР В Р’В°Р РЋРІР‚В Р В РЎвЂ�Р РЋР вЂ№ Р В РЎвЂ”Р В РЎвЂў Р В Р вЂ Р РЋР С“Р В Р’ВµР В РЎпїЅ Р В РЎвЂќР В Р’В°Р В Р вЂ¦Р В Р’В°Р В Р’В»Р В Р’В°Р В РЎпїЅ Р РЋРЎвЂњР В Р’В·Р В Р’В»Р В Р’В° (Р РЋР вЂљР В Р’В°Р РЋР С“Р РЋРІвЂљВ¬Р В РЎвЂ�Р РЋР вЂљР В Р’ВµР В Р вЂ¦Р В Р вЂ¦Р РЋРІР‚в„–Р В РІвЂћвЂ“ Р РЋР вЂљР В Р’ВµР В Р’В¶Р В РЎвЂ�Р В РЎпїЅ);
{
	   uint8_t  index=0,i=0;


	   TransferBuf[0]=0x00;TransferBuf[1]=0xD7;TransferBuf[2]=0x29;
	   TransferBuf[3]=ADRESS_DEV;  //
	   TransferBuf[4]=CHANNEL_ALL_GET_DATA_RESP;  //
	   TransferBuf[6]=STATE_BYTE;
	    for(i=0;i<CHANNEL_NUMBER;i++)				   //
	    {
			  TransferBuf[index+7]=i;
			  index++;
			  TransferBuf[index+7]=((channels[i].settings.set.type)<<4)|channels[i].settings.set.modific; //
			  index++;
			  switch(channels[i].settings.set.type)
			    {
					 case 0:  //
					 {
						 switch(channels[i].settings.set.modific)
		                 {
							  case 0:
							  {
							  		if(channels[i].calibrate.cal.calibrate)//
									{
									//	 if(channels[i].settings.set.modific==0x00 || channels[i].settings.set.modific==0x01)
									//	 {
										 	TransferBuf[index+7]=((channels[i].channel_data_calibrate)&0x0000FF00)>>8;
										  	index++;
				    					  	TransferBuf[index+7]=((channels[i].channel_data_calibrate)&0x00FF0000)>>16;
										  	index++;
									//	 }
									}
									else
									{
										// if(channels[i].settings.set.modific==0x00 || channels[i].settings.set.modific==0x01)		   //
									//	 {
											TransferBuf[index+7]=((channels[i].channel_data)&0x0000FF00)>>8;
										  	index++;
				    					  	TransferBuf[index+7]=((channels[i].channel_data)&0x00FF0000)>>16;
										  	index++;
										// }
									}


									  TransferBuf[index+7]=channels[i].settings.set.state_byte_1;	 //
			                          index++;
			                          TransferBuf[index+7]=channels[i].settings.set.state_byte_2;	 //
				                      index++;
							  }
							  break;

							  case 1:
							  {
							  }
							  break;

				        	  case 2:
							  {
							  }
							  break;

							  case 3:
							  {
							        if(channels[i].calibrate.cal.calibrate)//
									{
							 			// if(channels[i].settings.set.modific==0x02 || channels[i].settings.set.modific==0x03)		   //
									//	 {
										  	TransferBuf[index+7]=((channels[i].channel_data_calibrate)&0x000000FF); //
								          	index++;
										  	TransferBuf[index+7]=((channels[i].channel_data_calibrate)&0x0000FF00)>>8;
										  	index++;
				    					  	TransferBuf[index+7]=((channels[i].channel_data_calibrate)&0x00FF0000)>>16;
										  	index++;
			  						  	// }
									}
									else
									{
									//	 if(channels[i].settings.set.modific==0x02 || channels[i].settings.set.modific==0x03)		   //
										// {
										  	TransferBuf[index+7]=((channels[i].channel_data)&0x000000FF); //
								          	index++;
										  	TransferBuf[index+7]=((channels[i].channel_data)&0x0000FF00)>>8;
										  	index++;
				    					  	TransferBuf[index+7]=((channels[i].channel_data)&0x00FF0000)>>16;
										  	index++;
									//	 }
									}


									  TransferBuf[index+7]=channels[i].settings.set.state_byte_1;	 //
			                          index++;
			                          TransferBuf[index+7]=channels[i].settings.set.state_byte_2;	 //
				                      index++;
							  }
							  break;
						  }
					  }
					  break;

				 	case 1:	 //Р вЂњРІР‚С›Р вЂњР вЂ№Р вЂњРІР‚в„–
					{
						  switch(channels[i].settings.set.modific)
					      {
								  case 0:
								  {
								          TransferBuf[index+7]=((channels[i].channel_data)&0x000000FF); //
								          index++;

										  TransferBuf[index+7]=((channels[i].channel_data)&0x0000FF00)>>8;
										  index++;

								          TransferBuf[index+7]=((channels[i].channel_data)&0x00FF0000)>>16; //
								          index++;

										  TransferBuf[index+7]=((channels[i].channel_data)&0xFF000000)>>24;
										  index++;


										  TransferBuf[index+7]=channels[i].settings.set.state_byte_1;	 //
				                          index++;
								  }
								  break;
						   }
					}
					break;

					 case 2: //
					 {
						  switch(channels[i].settings.set.modific)
					      {
								  case 1:
								  {
								          TransferBuf[index+7]=((channels[i].channel_data)&0x000000FF); //
								          index++;
										  TransferBuf[index+7]=((channels[i].channel_data)&0x0000FF00)>>8;
										  index++;
										  TransferBuf[index+7]=channels[i].settings.set.state_byte_1;	 //
				                          index++;
								  }
								  break;
						   }
					  }
					  break;
			  }
		   }

		  TransferBuf[5]=index+2; 						 //
		  TransferBuf[index+7]=CRC_Check(&TransferBuf[1],(uint8_t)(index+7)-1); //
		  return (uint8_t)(7+index+1);
}

uint8_t Request_Error(uint8_t error_code) //using 0 //	Р В РЎвЂєР РЋРІвЂљВ¬Р В РЎвЂ�Р В Р’В±Р В РЎвЂўР РЋРІР‚РЋР В Р вЂ¦Р РЋРІР‚в„–Р В РІвЂћвЂ“ Р В Р’В·Р В Р’В°Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“/Р В РЎвЂўР РЋРІР‚С™Р В Р вЂ Р В Р’ВµР РЋРІР‚С™;
{
	TransferBuf[0]=0x00;TransferBuf[1]=0xD7;TransferBuf[2]=0x29;
    TransferBuf[3]=ADRESS_DEV;  // Р В Р’В°Р В РўвЂ�Р РЋР вЂљР В Р’ВµР РЋР С“ Р РЋРЎвЂњР В Р’В·Р В Р’В»Р В Р’В°
    TransferBuf[7]=RecieveBuf[4]; // Р В РЎвЂќР В РЎвЂўР В РўвЂ� Р РЋР С“Р В Р’В±Р В РЎвЂўР В РІвЂћвЂ“Р В Р вЂ¦Р В РЎвЂўР В РІвЂћвЂ“ Р В РЎвЂќР В РЎвЂўР В РЎпїЅР В Р’В°Р В Р вЂ¦Р В РўвЂ�Р РЋРІР‚в„–
    TransferBuf[4]=0xFF;  // Р В РЎвЂќР В РЎвЂўР В РўвЂ� Р В РЎвЂўР В РЎвЂ”Р В Р’ВµР РЋР вЂљР В Р’В°Р РЋРІР‚В Р В РЎвЂ�Р В РЎвЂ�

	TransferBuf[6]=STATE_BYTE; // Р В Р’В±Р В Р’В°Р В РІвЂћвЂ“Р РЋРІР‚С™ Р РЋР С“Р РЋРІР‚С™Р В Р’В°Р РЋРІР‚С™Р РЋРЎвЂњР РЋР С“Р В Р’В° Р РЋРЎвЂњР В Р’В·Р В Р’В»Р В Р’В°
    TransferBuf[8]=error_code;
    TransferBuf[5]=0x04;	  // Р В РўвЂ�Р В Р’В»Р В РЎвЂ�Р В Р вЂ¦Р В Р’В° Р В РўвЂ�Р В Р’В°Р В Р вЂ¦Р В Р вЂ¦Р РЋРІР‚в„–Р РЋРІР‚В¦
    TransferBuf[9]=CRC_Check(TransferBuf,9);
	return 10;
}
//-----------------------------------------------------------------------------
void ProtoBufHandling(void) //using 0 //Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋРІР‚В Р В Р’ВµР РЋР С“Р РЋР С“ Р В РЎвЂўР В Р’В±Р РЋР вЂљР В Р’В°Р В Р’В±Р В РЎвЂўР РЋРІР‚С™Р В РЎвЂќР В РЎвЂ� Р В РЎвЂ”Р РЋР вЂљР В РЎвЂ�Р В Р вЂ¦Р РЋР РЏР РЋРІР‚С™Р В РЎвЂўР В РЎвЂ“Р В РЎвЂў Р В Р’В·Р В Р’В°Р В РЎвЂ”Р РЋР вЂљР В РЎвЂўР РЋР С“Р В Р’В°
{
  switch(RecieveBuf[4])
  {
//---------------------------------------
  	case GET_DEV_INFO_REQ:
	{
		buf_len=Send_Info();
	}
	break;
//---------------------------------------
  	case NODE_FULL_INIT_REQ:
	{
		buf_len=Node_Full_Init();
	}
	break;
//---------------------------------------
  	case CHANNEL_LIST_INIT_REQ:
	{
		buf_len=Channel_List_Init();
	}
	break;
//---------------------------------------
	case CHANNEL_GET_DATA_REQ:
	{
		buf_len=Channel_Get_Data();
	}
	break;
	//-----------------------------------
	case CHANNEL_SET_PARAMETERS_REQ:
	{
		buf_len=Channel_Set_Parameters();
	}
	break;
	//-----------------------------------
	case CHANNEL_SET_ORDER_QUERY_REQ:
	{
		buf_len=Channel_Set_Order_Query();
	}
	break;
//----------------------------------------
	case CHANNEL_GET_DATA_ORDER_REQ:
	{
		 buf_len=Channel_Get_Data_Order();
	}
	break;
//----------------------------------------
	case CHANNEL_SET_STATE_REQ:
	{
		 buf_len=Channel_Set_State();
	}
	break;
//----------------------------------------
	case CHANNEL_GET_DATA_ORDER_M2_REQ:
	{
		 buf_len=Channel_Get_Data_Order_M2();
	}
	break;
//------------------------------------------
	case CHANNEL_SET_RESET_STATE_FLAGS_REQ:
	{
		buf_len=Channel_Set_Reset_State_Flags();
	}
	break;
//------------------------------------------
	case CHANNEL_ALL_GET_DATA_REQ:
	{
		 buf_len=Channel_All_Get_Data();
	}
	break;
//------------------------------------------
/*	case CHANNEL_SET_ADDRESS_DESC:
	{
		 buf_len=Channel_Set_Address_Desc();
	}
	break;
//------------------------------------------
	case CHANNEL_SET_CALIBRATE:
	{
		 buf_len=Channel_Set_Calibrate();
	}
	break;*/
//------------------------------------------
    default:
	{
       COMMAND_ERR=0x1;//Р В Р вЂ¦Р В Р’ВµР РЋР С“Р РЋРЎвЂњР РЋРІР‚В°Р В Р’ВµР РЋР С“Р РЋРІР‚С™Р В Р вЂ Р РЋРЎвЂњР РЋР вЂ№Р РЋРІР‚В°Р В Р’В°Р РЋР РЏ Р В РЎвЂќР В РЎвЂўР В РЎпїЅР В Р’В°Р В Р вЂ¦Р В РўвЂ�Р В Р’В°
	   buf_len=Request_Error(FR_COMMAND_NOT_EXIST);
    }
  }

  return;
}
//-----------------------------------------------------------------------------------
void ProtoProcess( void *pvParameters )
{
	uint8_t   crc_n;
	while(1)
	{
		if( xProtoSemaphore != NULL )
		{
			if( xSemaphoreTake( xProtoSemaphore, ( portTickType ) PROTO_STANDBY_TIME ) == pdTRUE )
			{
				switch(proto_type)
				{
					case PROTO_TYPE_OLD:
					{
						tablo_proto_parser(&tab.tablo_proto_buf);
						recieve_count=0x0;
						USART_ITConfig(USART6, USART_IT_RXNE , ENABLE);
					}
					break;

					case PROTO_TYPE_NEW:
					{
						crc_n=RecieveBuf[recieve_count-1];
						transf_count=0;
						if(CRC_Check(RecieveBuf,(recieve_count-CRC_LEN))==crc_n)
						{

							ProtoBufHandling();//

							transf_count=0;
							recieve_count=0;
							CUT_OUT_NULL=0;

							//USART_SendData(USART6,/*TransferBuf[transf_count]*/tab.uart_buf[transf_count]);
							USART6->DR =TransferBuf[transf_count];
							transf_count++;//
						}
						else
						{
							crc_n_ERR=0x1;//
							USART_ITConfig(USART6, USART_IT_RXNE , ENABLE);
						}
					}
					break;
				}
			}
			else
			{
				tablo_proto_parser(&standby_frame);//
			}
		}
	}
}
//-----------------------crc_n------------------------------------------------------------
uint8_t  CRC_Check( uint8_t  *Spool_pr,uint8_t Count_pr )
{
	uint8_t crc_n = 0;
	uint8_t  *Spool;
	uint8_t  Count ;

	Spool=Spool_pr;
	Count=Count_pr;

  		while(Count!=0x0)
        {
	        crc_n = crc_n ^ (*Spool++);//

	        crc_n = ((crc_n & 0x01) ? (uint8_t)0x80: (uint8_t)0x00) | (uint8_t)(crc_n >> 1);

	        if (crc_n & (uint8_t)0x80) crc_n = crc_n ^ (uint8_t)0x3C;
			Count--;
        }
    return crc_n;
}
 //-----------------------------------------------------------------------------------------------

