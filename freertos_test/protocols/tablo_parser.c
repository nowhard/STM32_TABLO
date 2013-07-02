#include "tablo_parser.h"
#include <stdio.h>
#include <string.h>

#define IND_OPEN    1//������ [ �������, �� �� �������
#define IND_CLOSE   0//������ ] �������

#define FRAME_MAX_LEN   150//������������ ����� �����

const uint8_t Sym_table[2][SYM_TAB_LEN]={{'0','1','2','3','4','5','6','7','8','9','A','b','C','d','E','F','h','I','I','J','L','O','P','r','t','U','u','.','-','_',' '},
                                         {0x7E/*0*/,0x30/*1*/,0x6D/*2*/,0x79/*3*/,0x33/*4*/,0x5B/*5*/,0x5F/*6*/,0x70/*7*/,0x7F/*8*/,0x7B/*9*/,0x77/*A*/,
                                          0x1F/*b*/,0x4E/*C*/,0x3D/*d*/,0x4F/*E*/,0x47/*F*/,0x17/*h*/,0x30/*I*/,0x10/*i*/,0x3C/*J*/,0xE/*L*/,0x7E/*O*/,
                                          0x67/*P*/,0x05/*r*/,0x0F/*t*/,0x3E/*U*/,0x1C/*u*/,0x80/*.*/,0x01/*-*/,0x08/*_*/,0x00/* */}};


struct indicator indicators[INDICATORS_NUM];//��������� �����������
uint16_t display_buf[INDICATOR_BUF_LEN][INDICATORS_NUM];//

void tablo_indicator_struct_init(void)//������������� �������� ����������� �����
{
    indicators[0].number=0;
    indicators[0].type=IND_TYPE_SEGMENT;
    indicators[0].character_num=5;
    indicators[0].brightness=IND_BRIGHTNESS|0x9;
    indicators[0].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[0].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[0].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[0].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[1].number=0;
    indicators[1].type=IND_TYPE_SEGMENT;
    indicators[1].character_num=3;
    indicators[1].brightness=IND_BRIGHTNESS|0x9;
    indicators[1].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[1].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[1].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[1].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[2].number=0;
    indicators[2].type=IND_TYPE_SEGMENT;
    indicators[2].character_num=3;
    indicators[2].brightness=IND_BRIGHTNESS|0x9;
    indicators[2].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[2].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[2].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[2].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[3].number=0;
    indicators[3].type=IND_TYPE_SEGMENT;
    indicators[3].character_num=3;
    indicators[3].brightness=IND_BRIGHTNESS|0x9;
    indicators[3].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[3].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[3].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[3].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[4].number=0;
    indicators[4].type=IND_TYPE_SEGMENT;
    indicators[4].character_num=3;
    indicators[4].brightness=IND_BRIGHTNESS|0x9;
    indicators[4].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[4].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[4].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[4].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[5].number=0;
    indicators[5].type=IND_TYPE_SEGMENT;
    indicators[5].character_num=3;
    indicators[5].brightness=IND_BRIGHTNESS|0x9;
    indicators[5].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[5].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[5].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[5].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[6].number=0;
    indicators[6].type=IND_TYPE_SEGMENT;
    indicators[6].character_num=3;
    indicators[6].brightness=IND_BRIGHTNESS|0x9;
    indicators[6].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[6].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[6].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[6].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[7].number=0;
    indicators[7].type=IND_TYPE_SEGMENT;
    indicators[7].character_num=3;
    indicators[7].brightness=IND_BRIGHTNESS|0x9;
    indicators[7].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[7].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[7].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[7].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[8].number=0;
    indicators[8].type=IND_TYPE_SEGMENT;
    indicators[8].character_num=3;
    indicators[8].brightness=IND_BRIGHTNESS|0x9;
    indicators[8].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[8].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[8].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[8].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[9].number=0;
    indicators[9].type=IND_TYPE_SEGMENT;
    indicators[9].character_num=3;
    indicators[9].brightness=IND_BRIGHTNESS|0x9;
    indicators[9].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[9].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[9].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[9].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[10].number=0;
    indicators[10].type=IND_TYPE_SEGMENT;
    indicators[10].character_num=3;
    indicators[10].brightness=IND_BRIGHTNESS|0x9;
    indicators[10].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[10].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[10].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[10].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[11].number=0;
    indicators[11].type=IND_TYPE_SEGMENT;
    indicators[11].character_num=3;
    indicators[11].brightness=IND_BRIGHTNESS|0x9;
    indicators[11].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[11].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[11].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[11].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[12].number=0;
    indicators[12].type=IND_TYPE_SEGMENT;
    indicators[12].character_num=3;
    indicators[12].brightness=IND_BRIGHTNESS|0x9;
    indicators[12].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[12].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[12].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[12].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[13].number=0;
    indicators[13].type=IND_TYPE_SEGMENT;
    indicators[13].character_num=3;
    indicators[13].brightness=IND_BRIGHTNESS|0x9;
    indicators[13].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[13].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[13].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[13].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[14].number=0;
    indicators[14].type=IND_TYPE_SEGMENT;
    indicators[14].character_num=3;
    indicators[14].brightness=IND_BRIGHTNESS|0x9;
    indicators[14].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[14].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[14].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[14].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[15].number=0;
    indicators[15].type=IND_TYPE_SEGMENT;
    indicators[15].character_num=3;
    indicators[15].brightness=IND_BRIGHTNESS|0x9;
    indicators[15].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[15].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[15].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[15].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[16].number=0;
    indicators[16].type=IND_TYPE_SEGMENT;
    indicators[16].character_num=3;
    indicators[16].brightness=IND_BRIGHTNESS|0x9;
    indicators[16].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[16].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[16].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[16].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[17].number=0;
    indicators[17].type=IND_TYPE_SEGMENT;
    indicators[17].character_num=3;
    indicators[17].brightness=IND_BRIGHTNESS|0x9;
    indicators[17].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[17].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[17].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[17].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[18].number=0;
    indicators[18].type=IND_TYPE_SEGMENT;
    indicators[18].character_num=3;
    indicators[18].brightness=IND_BRIGHTNESS|0x9;
    indicators[18].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[18].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[18].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[18].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;

    indicators[19].number=0;
    indicators[19].type=IND_TYPE_SEGMENT;
    indicators[19].character_num=3;
    indicators[19].brightness=IND_BRIGHTNESS|0x9;
    indicators[19].decode_mode=IND_DECODE|IND_DECODE_OFF;
    indicators[19].scan_limit=IND_SCAN_LIMIT|(indicators[0].character_num-1);
    indicators[19].shutdown=IND_SHUTDOWN|IND_SHUTDOWN_OFF;
    indicators[19].display_test=IND_DISPLAY_TEST|IND_DISPLAY_TEST_OFF;
}

void tablo_proto_parser(uint8_t *proto_buf)//������� ������� ����� �����
{
   uint8_t i=0,j=0,ind_state=IND_CLOSE;
   uint8_t len=0;//����� �����

   uint8_t current_indicator=0;
   uint8_t chr_counter=0;
   uint8_t num_buf[32]={0};


   if(proto_buf[0]!=':')//������ ����� ��������
   {
       //error
       return;
   }

   len=proto_buf[1];

   if(len>FRAME_MAX_LEN)//��������� ������������ ����� �����
   {
       //error
       return;
   }

   for(i=2;i<len;i++)//������ �� ������
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
                if(ind_state==IND_CLOSE)//������ ������� ������
                {
                   //error!
                }

                if(indicators[current_indicator].type=IND_TYPE_SEGMENT)
                {
                    str_to_max(&num_buf,current_indicator);
                }
                else
                {
                    //��������� �������
                }
                ind_state=IND_CLOSE;
                chr_counter=0;
           }
           break;

           default:
           {
              if((proto_buf[i-1]=='[') && (ind_state==IND_OPEN))
              {
                  if(proto_buf[i]=='*')//����� �������
                  {
                      for(j=0;j<INDICATORS_NUM;j++)
                      {
                          indicators[j].brightness=IND_BRIGHTNESS|(proto_buf[i+1]&0xF);
                      }
                      i+=2;
                      ind_state=IND_CLOSE;
                  }
                  else
                  {
                      current_indicator=proto_buf[i];
                      num_buf[chr_counter+1]='\0';
                      chr_counter=0;
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

//   uint8_t str[]="7.E7A";
//   uint16_t buf[32];
//   uint8_t buf_len=0;
//   buf_len=str_to_max(&str,&buf);
   return;
}

uint8_t str_to_max(uint8_t *str,uint8_t ind_num)//������� ������ � ������ �������� ��� max7219 � ��������� ������������
{
    uint8_t i=0,j=0;
    uint8_t buf_count=0;//�������� �������� ����������
    uint8_t str_len=0;

    str_len=strlen(str);
  /*
    �������������� �����
    */
    display_buf[0][ind_num]=indicators[ind_num].shutdown;
    display_buf[1][ind_num]=indicators[ind_num].display_test;
    display_buf[2][ind_num]=indicators[ind_num].scan_limit;
    display_buf[3][ind_num]=indicators[ind_num].brightness;
    display_buf[4][ind_num]=indicators[ind_num].decode_mode;

    buf_count+=5;

    for(i=0;i<str_len;i++)//����� �������� � symtable
    {
        if((str[i]>=0x30)&&(str[i]<=0x39))//�������� ��������
        {
           //buf[buf_count][ind_num]=0;/*���������� �����*/
            display_buf[buf_count][ind_num]=(Sym_table[1][(str[i]-0x30)])|(0x100*((buf_count-5)+1));
            buf_count++;

            continue;
        }

        if(str[i]=='.')/*������� �����, ���� ����� ���������*/
        {
            if(i>0)
            {
                display_buf[buf_count-1][ind_num]|=0x80;//�����
            }
            continue;
        }

        for(j=10;j<SYM_TAB_LEN;j++)//���� ������ ����������, ������ ��� � symtable
        {
           if(str[i]==Sym_table[0][j])//����� ����������
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

void ln_to_max(uint8_t *buf)//������� �������� ������� ��������� � �������� max7219
{

}
