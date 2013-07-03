#ifndef TABLO_PARSER_H
#define TABLO_PARSER_H
#include <stdint.h>

#define SYM_TAB_LEN 31


void tablo_proto_parser(uint8_t *proto_buf);//
uint8_t str_to_ind(uint8_t *str, uint8_t ind_num);//
void ln_to_ind(uint8_t *buf);//
#endif
