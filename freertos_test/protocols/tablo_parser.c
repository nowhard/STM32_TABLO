#include "tablo_parser.h"
#include <stdio.h>
#include <string.h>
#include "tablo.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "spi_bus.h"

extern xSemaphoreHandle xSPI_Buf_Mutex;

const uint8_t Sym_table[2][SYM_TAB_LEN]={{'0','1','2','3','4','5','6','7','8','9','A','b','C','d','E','F','h','I','I','J','L','O','P','r','t','U','u','.','-','_',' '},
                                         {0x7E/*0*/,0x30/*1*/,0x6D/*2*/,0x79/*3*/,0x33/*4*/,0x5B/*5*/,0x5F/*6*/,0x70/*7*/,0x7F/*8*/,0x7B/*9*/,0x77/*A*/,
                                          0x1F/*b*/,0x4E/*C*/,0x3D/*d*/,0x4F/*E*/,0x47/*F*/,0x17/*h*/,0x30/*I*/,0x10/*i*/,0x3C/*J*/,0xE/*L*/,0x7E/*O*/,
                                          0x67/*P*/,0x05/*r*/,0x0F/*t*/,0x3E/*U*/,0x1C/*u*/,0x80/*.*/,0x01/*-*/,0x08/*_*/,0x00/* */}};

extern struct tablo tab;

void tablo_proto_parser(uint8_t *proto_buf)//
{
   uint8_t i=0,j=0,ind_state=IND_CLOSE;
   uint8_t len=0;//

   uint8_t current_indicator=0;
   uint8_t chr_counter=0;
   uint8_t num_buf[32]={0};


   if(proto_buf[0]!=':')//
   {
       //error
       return;
   }

   len=proto_buf[1];

   if(len>FRAME_MAX_LEN)//
   {
       //error
       return;
   }

   for(i=2;i<len;i++)//
   {
       switch(proto_buf[i])
       {
           case '[':
           {
                ind_state=IND_OPEN;
           }
           break;

           case ']':
           {
                if(ind_state==IND_CLOSE)//
                {
                   //error!
                }


    			if( xSemaphoreTake( xSPI_Buf_Mutex, portMAX_DELAY ) == pdTRUE )
    			{
					if(tab.indicators[current_indicator].type==IND_TYPE_SEGMENT)
					{
						num_buf[chr_counter]='\0';
						str_to_ind(&tab.indicators[current_indicator],&num_buf);
					}
					else
					{
						ln_to_ind(&tab.indicators[current_indicator],&num_buf,chr_counter);
					}
					xSemaphoreGive( xSPI_Buf_Mutex );
    			}


                ind_state=IND_CLOSE;
                chr_counter=0;
           }
           break;

           default:
           {
              if(ind_state==IND_OPEN)
              {
				  if(proto_buf[i-1]=='[')
				  {
					  if(proto_buf[i]=='*')//
					  {
						if( xSemaphoreTake( xSPI_Buf_Mutex, portMAX_DELAY ) == pdTRUE )
						{
							  for(j=0;j<IND_ALL_NUM;j++)
							  {
								  tab.indicators[j].brightness=IND_BRIGHTNESS|(proto_buf[i+1]&0xF);
							  }
						  xSemaphoreGive( xSPI_Buf_Mutex );
						}
						  i+=2;
						  ind_state=IND_CLOSE;
					  }
					  else
					  {
						  current_indicator=proto_buf[i];

//						  if(current_indicator>=IND_ALL_NUM)///применить фильтр каналов!!!
//						  {
//							  continue;//переработать
//						  }
//
//						  num_buf[chr_counter]='\0';
						  //chr_counter=0;
					  }
				  }
				  else
				  {
					  num_buf[chr_counter]=proto_buf[i];
					  chr_counter++;
				  }
              }
           }
       }
   }
   return;
}

uint8_t str_to_ind(struct indicator *ind,uint8_t *str)
{
    int8_t i=0,j=0;
    uint8_t buf_count=0;//
    uint8_t str_len=0;

    str_len=strlen(str);

    	tab.buses[ind->bus].bus_buf[0][ind->number_in_bus]=ind->shutdown;
    	tab.buses[ind->bus].bus_buf[1][ind->number_in_bus]=ind->display_test;
    	tab.buses[ind->bus].bus_buf[2][ind->number_in_bus]=ind->scan_limit;
    	tab.buses[ind->bus].bus_buf[3][ind->number_in_bus]=ind->brightness;
    	tab.buses[ind->bus].bus_buf[4][ind->number_in_bus]=ind->decode_mode;
    	tab.buses[ind->bus].bus_buf[5][ind->number_in_bus]=0x100;
    	tab.buses[ind->bus].bus_buf[6][ind->number_in_bus]=0x200;
    	tab.buses[ind->bus].bus_buf[7][ind->number_in_bus]=0x300;
    	tab.buses[ind->bus].bus_buf[8][ind->number_in_bus]=0x400;
    	tab.buses[ind->bus].bus_buf[9][ind->number_in_bus]=0x500;
    	tab.buses[ind->bus].bus_buf[10][ind->number_in_bus]=0x600;
    	tab.buses[ind->bus].bus_buf[11][ind->number_in_bus]=0x700;
    	tab.buses[ind->bus].bus_buf[12][ind->number_in_bus]=0x800;

        buf_count+=5;

        for(i=(str_len-1);i>=0;i--)//
        {
            if((str[i]>=0x30)&&(str[i]<=0x39))//
            {
               	uint8_t sym=Sym_table[1][(str[i]-0x30)];//коррекция ошибки индикатора
               	sym&=0x9F;
               	sym|=((Sym_table[1][(str[i]-0x30)]<<5)&0x60);
               	sym&=0xFC;
               	sym|=((Sym_table[1][(str[i]-0x30)]>>5)&0x3);


            	tab.buses[ind->bus].bus_buf[buf_count][ind->number_in_bus]|=(/*Sym_table[1][(str[i]-0x30)]*/sym)|(0x100*((buf_count-5)+1));
                buf_count++;

                continue;
            }

            if(str[i]=='.')
            {
             	if(i<(str_len-1))
                {
                	if(str[i+1]=='.')
                	{
                    	tab.buses[ind->bus].bus_buf[buf_count+1][ind->number_in_bus]|=0x80;
                    	buf_count++;
                	}
                	else
                	{
                		tab.buses[ind->bus].bus_buf[buf_count][ind->number_in_bus]|=0x80;
                	}
                }
             	else
             	{
             		tab.buses[ind->bus].bus_buf[buf_count][ind->number_in_bus]|=0x80;
             	}
                continue;
            }
//
            for(j=10;j<SYM_TAB_LEN;j++)//
            {
               if(str[i]==Sym_table[0][j])//
               {
                  	uint8_t sym=Sym_table[1][j];//коррекция ошибки индикатора
                  	sym&=0x9F;
                  	sym|=((Sym_table[1][j]<<5)&0x60);
                  	sym&=0xFC;
                  	sym|=((Sym_table[1][j]>>5)&0x3);

                	tab.buses[ind->bus].bus_buf[buf_count][ind->number_in_bus]|=(/*Sym_table[1][(str[i]-0x30)]*/sym)|(0x100*((buf_count-5)+1));
                    buf_count++;

                    break;
               }
            }

            if(buf_count>(ind->character_num+5))//
            {
            	break;
            }
        }

//        for(i=buf_count;i<IND_ALL_NUM;i++)
//        {
//        	tab.buses[ind->bus].bus_buf[i][ind->number_in_bus]=0x0;
//        }
        return buf_count;

}


//const uint8_t   LED_BAR_STAMP_RED[4]   ={8 ,128,4 ,16};
//const uint8_t   LED_BAR_STAMP_GREEN[4] ={64,2  ,32,1 };
//const uint8_t   LED_BAR_STAMP_ORANGE[4]={72,130,36,17};

const uint8_t   LED_BAR_STAMP_RED[4]   ={64 ,16,4 ,1};
const uint8_t   LED_BAR_STAMP_GREEN[4] ={32,8  ,2,128 };
const uint8_t   LED_BAR_STAMP_ORANGE[4]={96,24,6,129};

void ln_to_ind(struct indicator *ind,uint8_t *buf, uint8_t len)//
{

	uint8_t inverse=0;
	uint8_t	value=0;
	uint8_t ust1=0;//
	uint8_t	ust2=0;

	uint8_t i=0;

	inverse=buf[0];
	value=buf[1];
	ust1=buf[2];
	ust2=buf[3];

	tab.buses[ind->bus].bus_buf[0][ind->number_in_bus]=ind->shutdown;
	tab.buses[ind->bus].bus_buf[1][ind->number_in_bus]=ind->display_test;
	tab.buses[ind->bus].bus_buf[2][ind->number_in_bus]=ind->scan_limit;
	tab.buses[ind->bus].bus_buf[3][ind->number_in_bus]=ind->brightness;
	tab.buses[ind->bus].bus_buf[4][ind->number_in_bus]=ind->decode_mode;
	tab.buses[ind->bus].bus_buf[5][ind->number_in_bus]=0x100;
	tab.buses[ind->bus].bus_buf[6][ind->number_in_bus]=0x200;
	tab.buses[ind->bus].bus_buf[7][ind->number_in_bus]=0x300;
	tab.buses[ind->bus].bus_buf[8][ind->number_in_bus]=0x400;
	tab.buses[ind->bus].bus_buf[9][ind->number_in_bus]=0x500;
	tab.buses[ind->bus].bus_buf[10][ind->number_in_bus]=0x600;
	tab.buses[ind->bus].bus_buf[11][ind->number_in_bus]=0x700;
	tab.buses[ind->bus].bus_buf[12][ind->number_in_bus]=0x800;


	if(value==0xFF)//
	{
		return;
	}

	if((ust1>=0) && (ust1<=31))//
	{
		if(inverse==0x0)
		{
			tab.buses[ind->bus].bus_buf[(ust1>>2)+5][ind->number_in_bus]|=(((ust1>>2)+1)<<8)|LED_BAR_STAMP_RED[ust1%4];
		}
		else
		{
			tab.buses[ind->bus].bus_buf[(ust1>>2)+5][ind->number_in_bus]|=(((ust1>>2)+1)<<8)|LED_BAR_STAMP_GREEN[ust1%4];
		}
	}

	if((ust2>=0) && (ust2<=31))//
	{
		if(inverse==0x0)
		{
			tab.buses[ind->bus].bus_buf[(ust2>>2)+5][ind->number_in_bus]|=(((ust2>>2)+1)<<8)|LED_BAR_STAMP_RED[ust2%4];
		}
		else
		{
			tab.buses[ind->bus].bus_buf[(ust2>>2)+5][ind->number_in_bus]|=(((ust2>>2)+1)<<8)|LED_BAR_STAMP_GREEN[ust2%4];
		}
	}


	for(i=0;i<value;i++)
	{
		if(inverse==0x0)
		{
			if((i!=ust1) && (i!=ust2))
			{
				tab.buses[ind->bus].bus_buf[(i>>2)+5][ind->number_in_bus]|=(((i>>2)+1)<<8)|LED_BAR_STAMP_GREEN[i%4];
			}
		}
		else
		{
			if((i!=ust1) && (i!=ust2))
			{
				tab.buses[ind->bus].bus_buf[(i>>2)+5][ind->number_in_bus]|=(((i>>2)+1)<<8)|LED_BAR_STAMP_RED[i%4];
			}
		}
	}
}
