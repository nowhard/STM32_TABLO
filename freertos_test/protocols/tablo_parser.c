#include "tablo_parser.h"
#include <stdio.h>
#include <string.h>
#include "tablo.h"



const uint8_t Sym_table[2][SYM_TAB_LEN]={{'0','1','2','3','4','5','6','7','8','9','A','b','C','d','E','F','h','I','I','J','L','O','P','r','t','U','u','.','-','_',' '},
                                         {0x7E/*0*/,0x30/*1*/,0x6D/*2*/,0x79/*3*/,0x33/*4*/,0x5B/*5*/,0x5F/*6*/,0x70/*7*/,0x7F/*8*/,0x7B/*9*/,0x77/*A*/,
                                          0x1F/*b*/,0x4E/*C*/,0x3D/*d*/,0x4F/*E*/,0x47/*F*/,0x17/*h*/,0x30/*I*/,0x10/*i*/,0x3C/*J*/,0xE/*L*/,0x7E/*O*/,
                                          0x67/*P*/,0x05/*r*/,0x0F/*t*/,0x3E/*U*/,0x1C/*u*/,0x80/*.*/,0x01/*-*/,0x08/*_*/,0x00/* */}};

extern struct tablo tab;//структура табло

/*
uint8_t str_to_ind(uint8_t *str,uint8_t ind_num)//
{
    uint8_t i=0,j=0;
    uint8_t buf_count=0;//
    uint8_t str_len=0;

    str_len=strlen(str);

    display_buf[0][ind_num]=indicators[ind_num].shutdown;
    display_buf[1][ind_num]=indicators[ind_num].display_test;
    display_buf[2][ind_num]=indicators[ind_num].scan_limit;
    display_buf[3][ind_num]=indicators[ind_num].brightness;
    display_buf[4][ind_num]=indicators[ind_num].decode_mode;

    buf_count+=5;

    for(i=0;i<str_len;i++)//
    {
        if((str[i]>=0x30)&&(str[i]<=0x39))//цифры
        {
            display_buf[buf_count][ind_num]=(Sym_table[1][(str[i]-0x30)])|(0x100*((buf_count-5)+1));
            buf_count++;

            continue;
        }

        if(str[i]=='.')
        {
            if(i>0)
            {
                display_buf[buf_count-1][ind_num]|=0x80;
            }
            continue;
        }

        for(j=10;j<SYM_TAB_LEN;j++)//
        {
           if(str[i]==Sym_table[0][j])//
           {
                display_buf[buf_count][ind_num]=(Sym_table[1][j])|(0x100*((buf_count-5)+1));//������� � �����
                buf_count++;

                break;
           }
        }
    }

    for(i=buf_count;i<INDICATOR_BUF_LEN;i++)
    {
        display_buf[i][ind_num]=0x0;
    }
    return buf_count;
}

void ln_to_ind(uint8_t *buf)//
{

}*/

void tablo_proto_parser(uint8_t *proto_buf)//
{
   uint8_t i=0,j=0,ind_state=IND_CLOSE;
   uint8_t len=0;//

   uint8_t current_indicator=0;
   uint8_t chr_counter=0;
   uint8_t num_buf[32]={0};


   if(tab.tablo_proto_buf[0]!=':')//начало кадра
   {
       //error
       return;
   }

   len=tab.tablo_proto_buf[1];

   if(len>FRAME_MAX_LEN)//
   {
       //error
       return;
   }

   for(i=2;i<len;i++)//
   {
       switch(tab.tablo_proto_buf[i])
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

                if(tab.indicators[current_indicator].type=IND_TYPE_SEGMENT)
                {
                    //str_to_ind(&num_buf,current_indicator);
                	str_to_ind(&tab.indicators[current_indicator],&num_buf);
                }
                else
                {
                    //
                }
                ind_state=IND_CLOSE;
                chr_counter=0;
           }
           break;

           default:
           {
              if((tab.tablo_proto_buf[i-1]=='[') && (ind_state==IND_OPEN))
              {
                  if(tab.tablo_proto_buf[i]=='*')//яркость
                  {
                      for(j=0;j<IND_ALL_NUM;j++)
                      {
                          tab.indicators[j].brightness=IND_BRIGHTNESS|(tab.tablo_proto_buf[i+1]&0xF);
                      }
                      i+=2;
                      ind_state=IND_CLOSE;
                  }
                  else
                  {
                      current_indicator=tab.tablo_proto_buf[i];
                      num_buf[chr_counter+1]='\0';
                      chr_counter=0;
                  }
              }
              else
              {
                  num_buf[chr_counter]=tab.tablo_proto_buf[i];
                  chr_counter++;
              }
           }
       }
   }
   return;
}

uint8_t str_to_ind(struct indicator *ind,uint8_t *str)
{
    uint8_t i=0,j=0;
    uint8_t buf_count=0;//
    uint8_t str_len=0;

    str_len=strlen(str);

    	tab.buses[ind->bus].bus_buf[0][ind->number_in_bus]=ind->shutdown;
    	tab.buses[ind->bus].bus_buf[1][ind->number_in_bus]=ind->display_test;
    	tab.buses[ind->bus].bus_buf[2][ind->number_in_bus]=ind->scan_limit;
    	tab.buses[ind->bus].bus_buf[3][ind->number_in_bus]=ind->brightness;
    	tab.buses[ind->bus].bus_buf[4][ind->number_in_bus]=ind->decode_mode;

        buf_count+=5;

        for(i=0;i<str_len;i++)//
        {
            if((str[i]>=0x30)&&(str[i]<=0x39))//цифры
            {
            	tab.buses[ind->bus].bus_buf[buf_count][ind->number_in_bus]=(Sym_table[1][(str[i]-0x30)])|(0x100*((buf_count-5)+1));
                buf_count++;

                continue;
            }

            if(str[i]=='.')
            {
                if(i>0)
                {
                	tab.buses[ind->bus].bus_buf[buf_count-1][ind->number_in_bus]|=0x80;
                }
                continue;
            }

            for(j=10;j<SYM_TAB_LEN;j++)//
            {
               if(str[i]==Sym_table[0][j])//
               {
            	   tab.buses[ind->bus].bus_buf[buf_count][ind->number_in_bus]=(Sym_table[1][j])|(0x100*((buf_count-5)+1));//
                    buf_count++;

                    break;
               }
            }
        }

        for(i=buf_count;i<IND_ALL_NUM;i++)
        {
        	tab.buses[ind->bus].bus_buf[i][ind->number_in_bus]=0x0;
        }
        return buf_count;
	//перед доступом к буферу шины критическая секция

}
