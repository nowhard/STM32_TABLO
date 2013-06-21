#ifndef TABLO_PARSER_H
#define TABLO_PARSER_H
#include <stdint.h>
/*
�������� ��������� ����������� �����
 */

struct indicator{
    uint16_t number;//���������� ����� ���������� �� ����
    uint16_t type;//��� ���������� -TYPE_SEGMENT=���������� TYPE_LINE=��������, ��������
    uint16_t character_num;//���������� ��������� ���������� 3-5
    uint16_t brightness;//������� ����������
    uint16_t decode_mode;//����� �������������
    uint16_t scan_limit;//���-�� ������������ ��������
    uint16_t shutdown;//���������� �����������
    uint16_t display_test;// ���� ���������

    //uint8_t *display_buf;//��������� �� ������� ����� ����������
};

/*
  ������� max7219/21
  */
#define IND_BRIGHTNESS      0xA00 //0-15
#define IND_DECODE          0x900//
    #define IND_DECODE_ON       0xFF
    #define IND_DECODE_OFF      0x0
#define IND_SCAN_LIMIT      0xB00//0-8
#define IND_SHUTDOWN        0xC00
    #define IND_SHUTDOWN_ON     0x0
    #define IND_SHUTDOWN_OFF    0x1
#define IND_DISPLAY_TEST    0xF00
    #define IND_DISPLAY_TEST_ON     0x1
    #define IND_DISPLAY_TEST_OFF    0x0
/*
  �������������� ����������
  */
#define IND_TYPE_NONE       0x0//��������� �����������
#define IND_TYPE_SEGMENT    0x1//��������������
#define IND_TYPE_LINE       0x2//�������
#define IND_TYPE_ARC        0x3//��������

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
