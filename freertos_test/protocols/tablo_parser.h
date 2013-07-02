#ifndef TABLO_PARSER_H
#define TABLO_PARSER_H
#include <stdint.h>
/*
�������� ��������� ����������� �����
 */
/*
  ������� max7219/21
  */


#define BUS_SPI_1	0		//шина индикатора
#define BUS_SPI_2	1
#define BUS_SPI_3	2

/*
  ������� ���������� ��������
 */
#define SYM_TAB_LEN 31

#define INDICATORS_NUM      20
#define INDICATOR_BUF_LEN   13


void tablo_indicator_struct_init(void);//������������� �������� ����������� �����
void tablo_proto_parser(uint8_t *proto_buf);//������� ������� ����� �����
uint8_t str_to_max(uint8_t *str, uint8_t ind_num);//������� ������ � ������ �������� ��� max7219 � ��������� ������������
void ln_to_max(uint8_t *buf);//������� �������� ������� ��������� � �������� max7219
#endif
